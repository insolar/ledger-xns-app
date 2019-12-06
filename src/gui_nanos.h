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
#include "glyphs.h"

static const ux_menu_entry_t menu_main[];

static const ux_menu_entry_t menu_about[] = {
        {
                .menu     = NULL,
                .callback = NULL,
                .userid   = 0,
                .icon     = NULL,
                .line1    = "Version",
                .line2    = APPVERSION,
                .text_x   = 0,
                .icon_x   = 0,
        },
        {menu_main, NULL, 0, &C_icon_back, "Back", NULL, 61, 40},
        UX_MENU_END,
};

static const ux_menu_entry_t menu_main[] = {
        {NULL, NULL, 0, NULL, "Waiting for", "commands...", 0, 0},
        {menu_about, NULL, 0, NULL, "About", NULL, 0, 0},
        {NULL, os_sched_exit, 0, &C_icon_dashboard, "Quit app", NULL, 50, 29},
        UX_MENU_END,
};

void ui_idle(void) {
    UX_MENU_DISPLAY(0, menu_main, NULL);
}
