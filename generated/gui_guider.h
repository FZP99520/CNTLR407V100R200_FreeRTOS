/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *src_main;
	bool src_main_del;
	lv_obj_t *src_main_ddlist_lock_mode;
	lv_obj_t *src_main_slider_1;
	lv_obj_t *src_main_btn_send_data;
	lv_obj_t *src_main_btn_send_data_label;
	lv_obj_t *src_main_cb_send_enable;
	lv_obj_t *src_main_cb_receive_enable;
	lv_obj_t *src_main_bar_Iq;
	lv_obj_t *src_main_bar_voltage;
	lv_obj_t *src_main_bar_current;
	lv_obj_t *src_main_meter_angle;
	lv_meter_indicator_t *src_main_meter_angle_scale_1_arc_0;
	lv_obj_t *src_main_meter_omega;
	lv_meter_indicator_t *src_main_meter_omega_scale_1_arc_0;
	lv_meter_indicator_t *src_main_meter_omega_scale_1_arc_1;
	lv_obj_t *src_main_label_angle;
	lv_obj_t *src_main_label_omega;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_src_main(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif