/*******************************************************************************
*   (c) 2019 ZondaX GmbH
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#include <stdio.h>
#include <zxmacros.h>
#include <json/tx_validate.h>
#include <zxtypes.h>
#include "json/tx_parser.h"
#include "json/tx_display.h"
#include "lib/parser_impl.h"
#include "view_internal.h"
#include "jsmn.h"
#include "parser.h"

parser_error_t parser_parse(parser_context_t *ctx,
                            const uint8_t *data,
                            uint16_t dataLen) {
    parser_init(ctx, data, dataLen);
    return _readTx(ctx, &parser_tx_obj);
}

parser_error_t parser_validate(parser_context_t *ctx) {
    parser_error_t err = tx_validate(&parser_tx_obj.json);
    if (err != parser_ok)
        return err;

    // Iterate through all items to check that all can be shown and are valid

    uint8_t numItems = parser_getNumItems(ctx);

    char tmpKey[40];
    char tmpVal[40];

    for (uint8_t idx = 0; idx < numItems; idx++) {
        uint8_t pageCount;
        err = parser_getItem(ctx, idx, tmpKey, sizeof(tmpKey), tmpVal, sizeof(tmpVal), 0, &pageCount);
        if (err != parser_ok) {
            return err;
        }
    }

    return parser_ok;
}

uint8_t parser_getNumItems(parser_context_t *ctx) {
    return tx_display_numItems();
}

__Z_INLINE bool_t parser_areEqual(uint16_t tokenidx, char *expected) {
    if (parser_tx_obj.json.tokens[tokenidx].type != JSMN_STRING) {
        return false;
    }

    uint16_t len = parser_tx_obj.json.tokens[tokenidx].end - parser_tx_obj.json.tokens[tokenidx].start;
    if (strlen(expected) != len) {
        return false;
    }

    const char *p = parser_tx_obj.tx + parser_tx_obj.json.tokens[tokenidx].start;
    for (uint16_t i = 0; i < len; i++) {
        if (expected[i] != *(p + i)) {
            return false;
        }
    }

    return true;
}

__Z_INLINE bool_t parser_isAmount(char *key) {
    if (strcmp(parser_tx_obj.query.out_key, "callParams/amount") == 0)
        return true;

    return false;
}

__Z_INLINE parser_error_t parser_formatAmount(uint16_t amountToken,
                                              char *outVal, uint16_t outValLen,
                                              uint8_t pageIdx, uint8_t *pageCount) {

    const char *amountPtr = parser_tx_obj.tx + parser_tx_obj.json.tokens[amountToken].start;
    const uint16_t amountLen = parser_tx_obj.json.tokens[amountToken].end -
                               parser_tx_obj.json.tokens[amountToken].start;

    char bufferUI[160];
    MEMZERO(outVal, outValLen);
    MEMZERO(bufferUI, sizeof(bufferUI));

    if (amountLen > 10) {
        MEMCPY(bufferUI, amountPtr, amountLen-10);
        bufferUI[amountLen-10] = '.';
        MEMCPY(bufferUI + amountLen-9, amountPtr + amountLen-10, 10);
    } else {
        MEMCPY(bufferUI, "0.0000000000", 12);
        MEMCPY(bufferUI + 12 - amountLen, amountPtr, amountLen);
    }

    pageString(outVal, outValLen, bufferUI, pageIdx, pageCount);

    return parser_ok;
}

parser_error_t parser_getItem(parser_context_t *ctx,
                              int8_t displayIdx,
                              char *outKey, uint16_t outKeyLen,
                              char *outVal, uint16_t outValLen,
                              uint8_t pageIdx, uint8_t *pageCount) {

    MEMZERO(outKey, outKeyLen);
    MEMZERO(outVal, outValLen);
    INIT_QUERY(outKey, outKeyLen, outVal, outValLen, pageIdx)
    snprintf(outKey, outKeyLen, "?");
    snprintf(outVal, outValLen, " ");

    uint16_t displayStartToken;
    parser_error_t err = tx_display_set_query(displayIdx, &displayStartToken);
    if (err != parser_ok)
        return err;

    STRNCPY_S(parser_tx_obj.query.out_key,
              get_required_root_item(parser_tx_obj.query.item_index_root),
              parser_tx_obj.query.out_key_len)

    uint16_t ret_value_token_index;
    err = tx_traverse_find(displayStartToken, &ret_value_token_index);
    if (err != parser_ok)
        return err;

    if (parser_isAmount(parser_tx_obj.query.out_key)) {
        err = parser_formatAmount(ret_value_token_index, outVal, outValLen, pageIdx, pageCount);
    } else {
        err = tx_getToken(ret_value_token_index, outVal, outValLen, parser_tx_obj.query.chunk_index, pageCount);
    }

    tx_display_make_friendly();

    if (*pageCount > 1) {
        uint8_t keyLen = strlen(outKey);
        if (keyLen < outKeyLen) {
            snprintf(outKey + keyLen, outKeyLen - keyLen, " [%d/%d]", pageIdx + 1, *pageCount);
        }
    }

    return err;
}
