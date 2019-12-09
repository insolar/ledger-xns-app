//
// Copyright 2019 Insolar Technologies GmbH
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <stdint.h>
#include <stdbool.h>
#include <os_io_seproxyhal.h>

#include "os.h"
#include "cx.h"

#include <string.h>

#include "gui_nanos.h"

unsigned char G_io_seproxyhal_spi_buffer[IO_SEPROXYHAL_BUFFER_SIZE_B];

#define OFFSET_CLA   0x00
#define OFFSET_INS   0x01
#define OFFSET_P1    0x02
#define OFFSET_P2    0x03
#define OFFSET_LC    0x04
#define OFFSET_CDATA 0x05

#define CLA 0x80
#define INS_GET_VERSION 0x00
#define INS_GET_PUBLIC_KEY 0x01
#define INS_SIGN 0x02
#define INS_ELEMENT_COUNT 0x03
#define P1_LAST 0x80
#define P1_MORE 0x00

#define SW_DEVELOPER_ERR 0x6B00
#define SW_INVALID_PARAM 0x6B01
#define SW_IMPROPER_INIT 0x6B02
#define SW_USER_REJECTED 0x6985
#define SW_OK            0x9000


void io_exchange_with_code(uint16_t code, uint16_t tx) {
    G_io_apdu_buffer[tx++] = code >> 8;
    G_io_apdu_buffer[tx++] = code & 0xFF;
    io_exchange(CHANNEL_APDU | IO_RETURN_AFTER_TX, tx);
}


typedef void handler_fn_t(uint8_t p1, uint8_t p2, uint8_t*dataBuffer, uint16_t dataLength,
        volatile unsigned int *flags, volatile unsigned int *tx);


static void handleGetVersion(uint8_t p1, uint8_t p2, uint8_t*dataBuffer, uint16_t dataLength,
                             volatile unsigned int *flags, volatile unsigned int *tx) {
G_io_apdu_buffer[0] = APPVERSION[0] - '0';
G_io_apdu_buffer[1] = APPVERSION[2] - '0';
G_io_apdu_buffer[2] = APPVERSION[4] - '0';
io_exchange_with_code(SW_OK, 3);
}


static handler_fn_t* getEnumeratedHandler(unsigned char ins) {
    switch (ins) {
        case INS_GET_VERSION:    return handleGetVersion;
//        case INS_GET_PUBLIC_KEY: return handleGetPublicKey;
//        case INS_SIGN_HASH:      return handleSignHash;
//        case INS_GET_TXN_HASH:   return handleCalcTxnHash;
        default:                 return NULL;
    }
}


//////////////////

void app_init() {
    io_seproxyhal_init();
    USB_power(0);
    USB_power(1);
    gui_idle_show(0);
}


__attribute__((section(".boot"))) int
main(void) {
    // exit critical section
    __asm volatile("cpsie i");

    gui_init();
    os_boot();

    BEGIN_TRY
        {
            TRY
                {
                    app_init();
                    app_main();
                }
            CATCH_OTHER(e)
                {}
            FINALLY
            {}
        }
    END_TRY;
}

