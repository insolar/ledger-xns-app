#pragma once

//#include <jsmn.h>

typedef enum {
    parser_ok = 0,
    parser_no_data,
    parser_init_context_empty,
    parser_unexpected_buffer_end,
    parser_unexpected_version,
    parser_unexpected_characters,
    parser_unexpected_field,
    parser_duplicated_field,
    parser_value_out_of_range,
    parser_unexpected_chain,
    parser_query_no_results,
    /////
            parser_display_idx_out_of_range,
    parser_display_page_out_of_range,
    ////
            parser_json_zero_tokens,
    parser_json_too_many_tokens,    // "NOMEM: JSON string contains too many tokens"
    parser_json_incomplete_json,    // "JSON string is not complete";
    parser_json_contains_whitespace,
    parser_json_is_not_sorted,
    parser_json_missing_chain_id,
    parser_json_missing_sequence,
    parser_json_missing_fee,
    parser_json_missing_msgs,
    parser_json_missing_account_number,
    parser_json_missing_memo,
} parser_error_t;

typedef struct {
    int isValid;
    int numberOfTokens;
    const char *buffer;
    int bufferLen;
} parsed_json_t;

parser_error_t json_parse_transaction(parsed_json_t *parsed_transaction,
                          const char *transaction_json);

int example();


