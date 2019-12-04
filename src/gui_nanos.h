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

#include "ux.h"

static char lineBuffer[50];


static const bagl_element_t bagl_ui_idle_nanos[] = {
        // {
        //     {type, userid, x, y, width, height, stroke, radius, fill, fgcolor,
        //      bgcolor, font_id, icon_id},
        //     text,
        //     touch_area_brim,
        //     overfgcolor,
        //     overbgcolor,
        //     tap,
        //     out,
        //     over,
        // },
        {
                {BAGL_RECTANGLE, 0x00, 0, 0, 128, 32, 0, 0, BAGL_FILL, 0x000000,
                                                                         0xFFFFFF, 0, 0},
                NULL,
        },
        {
                {BAGL_LABELINE, 0x02, 0, 12, 128, 11, 0, 0, 0, 0xFFFFFF, 0x000000,
                                                                                   BAGL_FONT_OPEN_SANS_REGULAR_11px | BAGL_FONT_ALIGNMENT_CENTER, 0},
                "Waiting for message",
        },
        {
                {BAGL_ICON, 0x00, 3, 12, 7, 7, 0, 0, 0, 0xFFFFFF, 0x000000, 0,
                        BAGL_GLYPH_ICON_CROSS},
                NULL,
        },
};

static const bagl_element_t bagl_ui_approval_nanos[] = {
        // {
        //     {type, userid, x, y, width, height, stroke, radius, fill, fgcolor,
        //      bgcolor, font_id, icon_id},
        //     text,
        //     touch_area_brim,
        //     overfgcolor,
        //     overbgcolor,
        //     tap,
        //     out,
        //     over,
        // },
        {
                {BAGL_RECTANGLE, 0x00, 0, 0, 128, 32, 0, 0, BAGL_FILL, 0x000000,
                                                                         0xFFFFFF, 0, 0},
                NULL,
        },
        {
                {BAGL_LABELINE, 0x02, 0, 12, 128, 11, 0, 0, 0, 0xFFFFFF, 0x000000,
                                                                                   BAGL_FONT_OPEN_SANS_REGULAR_11px | BAGL_FONT_ALIGNMENT_CENTER, 0},
                "Sign message",
        },
        {
                {BAGL_ICON, 0x00, 3, 12, 7, 7, 0, 0, 0, 0xFFFFFF, 0x000000, 0,
                        BAGL_GLYPH_ICON_CROSS},
                NULL,
        },
        {
                {BAGL_ICON, 0x00, 117, 13, 8, 6, 0, 0, 0, 0xFFFFFF, 0x000000, 0,
                        BAGL_GLYPH_ICON_CHECK},
                NULL,
        },
};


static const bagl_element_t bagl_ui_text_review_nanos[] = {
        // {
        //     {type, userid, x, y, width, height, stroke, radius, fill, fgcolor,
        //      bgcolor, font_id, icon_id},
        //     text,
        //     touch_area_brim,
        //     overfgcolor,
        //     overbgcolor,
        //     tap,
        //     out,
        //     over,
        // },
        {
                {BAGL_RECTANGLE, 0x00, 0, 0, 128, 32, 0, 0, BAGL_FILL, 0x000000,
                                                                         0xFFFFFF, 0, 0},
                NULL,
        },
        {
                {BAGL_LABELINE, 0x02, 0, 12, 128, 11, 0, 0, 0, 0xFFFFFF, 0x000000,
                                                                                   BAGL_FONT_OPEN_SANS_REGULAR_11px | BAGL_FONT_ALIGNMENT_CENTER, 0},
                "Verify text",
        },
        {
                {BAGL_LABELINE, 0x02, 23, 26, 82, 11, 0x80 | 10, 0, 0, 0xFFFFFF,
                                                                         0x000000, BAGL_FONT_OPEN_SANS_EXTRABOLD_11px | BAGL_FONT_ALIGNMENT_CENTER, 26},
                lineBuffer,
        },
        {
                {BAGL_ICON, 0x00, 3, 12, 7, 7, 0, 0, 0, 0xFFFFFF, 0x000000, 0,
                        BAGL_GLYPH_ICON_CROSS},
                NULL,
        },
        {
                {BAGL_ICON, 0x00, 117, 13, 8, 6, 0, 0, 0, 0xFFFFFF, 0x000000, 0,
                        BAGL_GLYPH_ICON_CHECK},
                NULL,
        },
};
