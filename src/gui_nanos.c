//
// Created by Ivan Serezhkin on 06.12.2019.
//

#include "glyphs.h"
#include "bagl.h"
#include "os.h"
#include "cx.h"

#include <string.h>
#include <stdio.h>



void os_exit(uint32_t id) {
    os_sched_exit(0);
}

const ux_menu_entry_t menu_main[] = {
        {NULL, NULL, 0, &C_icon_app, MENU_MAIN_APP_LINE1, MENU_MAIN_APP_LINE2, 33, 12},
        {NULL, NULL, 0, NULL, "v"APPVERSION, NULL, 0, 0},
        {NULL, os_exit, 0, &C_icon_dashboard, "Quit", NULL, 50, 29},
        UX_MENU_END
};



void gui_init(void) {
    UX_INIT();
}

void gui_idle_show(unsigned int ignored) {
    UX_MENU_DISPLAY(0, menu_main, NULL);
}