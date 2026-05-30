//
// Created by RM UI Designer
// Dynamic Edition
//

#ifndef UI_g_H
#define UI_g_H

#include "ui_interface.h"

extern ui_interface_figure_t ui_g_now_figures[2];
extern ui_interface_string_t ui_g_now_strings[8];
extern uint8_t ui_g_dirty_figure[2];
extern uint8_t ui_g_dirty_string[8];

#define ui_g_Ungroup_ShootMid ((ui_interface_round_t*)&(ui_g_now_figures[0]))
#define ui_g_Ungroup_SuperCap_Num ((ui_interface_number_t*)&(ui_g_now_figures[1]))

#define ui_g_Ungroup_Chassis_Mode (&(ui_g_now_strings[0]))
#define ui_g_Ungroup_Shoot_Mode (&(ui_g_now_strings[1]))
#define ui_g_Ungroup_Gimbal_Mode (&(ui_g_now_strings[2]))
#define ui_g_Ungroup_Mode 1 (&(ui_g_now_strings[3]))
#define ui_g_Ungroup_SuperCap (&(ui_g_now_strings[4]))
#define ui_g_Ungroup_Gimbal (&(ui_g_now_strings[5]))
#define ui_g_Ungroup_Shoot (&(ui_g_now_strings[6]))
#define ui_g_Ungroup_Chassis (&(ui_g_now_strings[7]))

#ifdef MANUAL_DIRTY
#define ui_g_Ungroup_ShootMid_dirty (ui_g_dirty_figure[0])
#define ui_g_Ungroup_SuperCap_Num_dirty (ui_g_dirty_figure[1])

#define ui_g_Ungroup_Chassis_Mode_dirty (ui_g_dirty_string[0])
#define ui_g_Ungroup_Shoot_Mode_dirty (ui_g_dirty_string[1])
#define ui_g_Ungroup_Gimbal_Mode_dirty (ui_g_dirty_string[2])
#define ui_g_Ungroup_Mode 1_dirty (ui_g_dirty_string[3])
#define ui_g_Ungroup_SuperCap_dirty (ui_g_dirty_string[4])
#define ui_g_Ungroup_Gimbal_dirty (ui_g_dirty_string[5])
#define ui_g_Ungroup_Shoot_dirty (ui_g_dirty_string[6])
#define ui_g_Ungroup_Chassis_dirty (ui_g_dirty_string[7])
#endif

void ui_init_g();
void ui_update_g();

#endif //UI_g_H
