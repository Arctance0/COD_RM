//
// Created by RM UI Designer
// Dynamic Edition
//

#include "string.h"
#include "ui_interface.h"
#include "ui_g.h"

#define TOTAL_FIGURE 2
#define TOTAL_STRING 8

ui_interface_figure_t ui_g_now_figures[TOTAL_FIGURE];
ui_interface_string_t ui_g_now_strings[TOTAL_STRING];
uint8_t ui_g_dirty_figure[TOTAL_FIGURE];
uint8_t ui_g_dirty_string[TOTAL_STRING];
#ifndef MANUAL_DIRTY
ui_interface_figure_t ui_g_last_figures[TOTAL_FIGURE];
ui_interface_string_t ui_g_last_strings[TOTAL_STRING];
#endif

void ui_init_g() {
    ui_g_Ungroup_ShootMid->figure_tpye = 2;
    ui_g_Ungroup_ShootMid->layer = 0;
    ui_g_Ungroup_ShootMid->r = 53;
    ui_g_Ungroup_ShootMid->start_x = 1068;
    ui_g_Ungroup_ShootMid->start_y = 466;
    ui_g_Ungroup_ShootMid->color = 0;
    ui_g_Ungroup_ShootMid->width = 4;

    ui_g_Ungroup_SuperCap_Num->figure_tpye = 6;
    ui_g_Ungroup_SuperCap_Num->layer = 0;
    ui_g_Ungroup_SuperCap_Num->font_size = 25;
    ui_g_Ungroup_SuperCap_Num->start_x = 774;
    ui_g_Ungroup_SuperCap_Num->start_y = 152;
    ui_g_Ungroup_SuperCap_Num->color = 1;
    ui_g_Ungroup_SuperCap_Num->number = 100;
    ui_g_Ungroup_SuperCap_Num->width = 3;

    ui_g_Ungroup_Chassis_Mode->figure_tpye = 7;
    ui_g_Ungroup_Chassis_Mode->layer = 0;
    ui_g_Ungroup_Chassis_Mode->font_size = 30;
    ui_g_Ungroup_Chassis_Mode->start_x = 100;
    ui_g_Ungroup_Chassis_Mode->start_y = 804;
    ui_g_Ungroup_Chassis_Mode->color = 5;
    ui_g_Ungroup_Chassis_Mode->str_length = 7;
    ui_g_Ungroup_Chassis_Mode->width = 3;
    strcpy(ui_g_Ungroup_Chassis_Mode->string, "Chassis");

    ui_g_Ungroup_Shoot_Mode->figure_tpye = 7;
    ui_g_Ungroup_Shoot_Mode->layer = 0;
    ui_g_Ungroup_Shoot_Mode->font_size = 30;
    ui_g_Ungroup_Shoot_Mode->start_x = 100;
    ui_g_Ungroup_Shoot_Mode->start_y = 643;
    ui_g_Ungroup_Shoot_Mode->color = 5;
    ui_g_Ungroup_Shoot_Mode->str_length = 5;
    ui_g_Ungroup_Shoot_Mode->width = 3;
    strcpy(ui_g_Ungroup_Shoot_Mode->string, "Shoot");

    ui_g_Ungroup_Gimbal_Mode->figure_tpye = 7;
    ui_g_Ungroup_Gimbal_Mode->layer = 0;
    ui_g_Ungroup_Gimbal_Mode->font_size = 30;
    ui_g_Ungroup_Gimbal_Mode->start_x = 102;
    ui_g_Ungroup_Gimbal_Mode->start_y = 726;
    ui_g_Ungroup_Gimbal_Mode->color = 5;
    ui_g_Ungroup_Gimbal_Mode->str_length = 6;
    ui_g_Ungroup_Gimbal_Mode->width = 3;
    strcpy(ui_g_Ungroup_Gimbal_Mode->string, "Gimbal");


    ui_g_Ungroup_SuperCap->figure_tpye = 7;
    ui_g_Ungroup_SuperCap->layer = 0;
    ui_g_Ungroup_SuperCap->font_size = 25;
    ui_g_Ungroup_SuperCap->start_x = 526;
    ui_g_Ungroup_SuperCap->start_y = 150;
    ui_g_Ungroup_SuperCap->color = 1;
    ui_g_Ungroup_SuperCap->str_length = 8;
    ui_g_Ungroup_SuperCap->width = 3;
    strcpy(ui_g_Ungroup_SuperCap->string, "SuperCap");

    ui_g_Ungroup_Gimbal->figure_tpye = 7;
    ui_g_Ungroup_Gimbal->layer = 0;
    ui_g_Ungroup_Gimbal->font_size = 30;
    ui_g_Ungroup_Gimbal->start_x = 374;
    ui_g_Ungroup_Gimbal->start_y = 730;
    ui_g_Ungroup_Gimbal->color = 0;
    ui_g_Ungroup_Gimbal->str_length = 2;
    ui_g_Ungroup_Gimbal->width = 3;
    strcpy(ui_g_Ungroup_Gimbal->string, "On");

    ui_g_Ungroup_Shoot->figure_tpye = 7;
    ui_g_Ungroup_Shoot->layer = 0;
    ui_g_Ungroup_Shoot->font_size = 30;
    ui_g_Ungroup_Shoot->start_x = 374;
    ui_g_Ungroup_Shoot->start_y = 643;
    ui_g_Ungroup_Shoot->color = 0;
    ui_g_Ungroup_Shoot->str_length = 6;
    ui_g_Ungroup_Shoot->width = 3;
    strcpy(ui_g_Ungroup_Shoot->string, "Repeat");

    ui_g_Ungroup_Chassis->figure_tpye = 7;
    ui_g_Ungroup_Chassis->layer = 0;
    ui_g_Ungroup_Chassis->font_size = 30;
    ui_g_Ungroup_Chassis->start_x = 367;
    ui_g_Ungroup_Chassis->start_y = 804;
    ui_g_Ungroup_Chassis->color = 0;
    ui_g_Ungroup_Chassis->str_length = 4;
    ui_g_Ungroup_Chassis->width = 3;
    strcpy(ui_g_Ungroup_Chassis->string, "Spin");


    uint32_t idx = 0;
    for (int i = 0; i < TOTAL_FIGURE; i++) {
        ui_g_now_figures[i].figure_name[2] = idx & 0xFF;
        ui_g_now_figures[i].figure_name[1] = (idx >> 8) & 0xFF;
        ui_g_now_figures[i].figure_name[0] = (idx >> 16) & 0xFF;
        ui_g_now_figures[i].operate_tpyel = 1;
#ifndef MANUAL_DIRTY
        ui_g_last_figures[i] = ui_g_now_figures[i];
#endif
        ui_g_dirty_figure[i] = 1;
        idx++;
    }
    for (int i = 0; i < TOTAL_STRING; i++) {
        ui_g_now_strings[i].figure_name[2] = idx & 0xFF;
        ui_g_now_strings[i].figure_name[1] = (idx >> 8) & 0xFF;
        ui_g_now_strings[i].figure_name[0] = (idx >> 16) & 0xFF;
        ui_g_now_strings[i].operate_tpyel = 1;
#ifndef MANUAL_DIRTY
        ui_g_last_strings[i] = ui_g_now_strings[i];
#endif
        ui_g_dirty_string[i] = 1;
        idx++;
    }

    ui_scan_and_send(ui_g_now_figures, ui_g_dirty_figure, ui_g_now_strings, ui_g_dirty_string, TOTAL_FIGURE, TOTAL_STRING);

    for (int i = 0; i < TOTAL_FIGURE; i++) {
        ui_g_now_figures[i].operate_tpyel = 2;
    }
    for (int i = 0; i < TOTAL_STRING; i++) {
        ui_g_now_strings[i].operate_tpyel = 2;
    }
}

void ui_update_g() {
#ifndef MANUAL_DIRTY
    for (int i = 0; i < TOTAL_FIGURE; i++) {
        if (memcmp(&ui_g_now_figures[i], &ui_g_last_figures[i], sizeof(ui_g_now_figures[i])) != 0) {
            ui_g_dirty_figure[i] = 1;
            ui_g_last_figures[i] = ui_g_now_figures[i];
        }
    }
    for (int i = 0; i < TOTAL_STRING; i++) {
        if (memcmp(&ui_g_now_strings[i], &ui_g_last_strings[i], sizeof(ui_g_now_strings[i])) != 0) {
            ui_g_dirty_string[i] = 1;
            ui_g_last_strings[i] = ui_g_now_strings[i];
        }
    }
#endif
    ui_scan_and_send(ui_g_now_figures, ui_g_dirty_figure, ui_g_now_strings, ui_g_dirty_string, TOTAL_FIGURE, TOTAL_STRING);
}
