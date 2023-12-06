/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_src_main(lv_ui *ui){

	//Write codes src_main
	ui->src_main = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->src_main, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_src_main_main_main_default
	static lv_style_t style_src_main_main_main_default;
	if (style_src_main_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_main_main_default);
	else
		lv_style_init(&style_src_main_main_main_default);
	lv_style_set_bg_color(&style_src_main_main_main_default, lv_color_make(0xf7, 0xf7, 0xf7));
	lv_style_set_bg_opa(&style_src_main_main_main_default, 128);
	lv_obj_add_style(ui->src_main, &style_src_main_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes src_main_ddlist_lock_mode
	ui->src_main_ddlist_lock_mode = lv_dropdown_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_ddlist_lock_mode, 332, 243);
	lv_obj_set_size(ui->src_main_ddlist_lock_mode, 93, 28);
	lv_obj_set_scrollbar_mode(ui->src_main_ddlist_lock_mode, LV_SCROLLBAR_MODE_OFF);
	lv_dropdown_set_options(ui->src_main_ddlist_lock_mode, "Lock Angle\nLock Omega\nLock Touqre");

	//Write style state: LV_STATE_DEFAULT for style_src_main_ddlist_lock_mode_main_main_default
	static lv_style_t style_src_main_ddlist_lock_mode_main_main_default;
	if (style_src_main_ddlist_lock_mode_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_ddlist_lock_mode_main_main_default);
	else
		lv_style_init(&style_src_main_ddlist_lock_mode_main_main_default);
	lv_style_set_radius(&style_src_main_ddlist_lock_mode_main_main_default, 3);
	lv_style_set_bg_color(&style_src_main_ddlist_lock_mode_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_src_main_ddlist_lock_mode_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_src_main_ddlist_lock_mode_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_ddlist_lock_mode_main_main_default, 255);
	lv_style_set_border_color(&style_src_main_ddlist_lock_mode_main_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_src_main_ddlist_lock_mode_main_main_default, 1);
	lv_style_set_border_opa(&style_src_main_ddlist_lock_mode_main_main_default, 255);
	lv_style_set_text_color(&style_src_main_ddlist_lock_mode_main_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_src_main_ddlist_lock_mode_main_main_default, &lv_font_simsun_12);
	lv_style_set_pad_left(&style_src_main_ddlist_lock_mode_main_main_default, 6);
	lv_style_set_pad_right(&style_src_main_ddlist_lock_mode_main_main_default, 6);
	lv_style_set_pad_top(&style_src_main_ddlist_lock_mode_main_main_default, 8);
	lv_obj_add_style(ui->src_main_ddlist_lock_mode, &style_src_main_ddlist_lock_mode_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_FOCUSED for style_src_main_ddlist_lock_mode_main_main_focused
	static lv_style_t style_src_main_ddlist_lock_mode_main_main_focused;
	if (style_src_main_ddlist_lock_mode_main_main_focused.prop_cnt > 1)
		lv_style_reset(&style_src_main_ddlist_lock_mode_main_main_focused);
	else
		lv_style_init(&style_src_main_ddlist_lock_mode_main_main_focused);
	lv_style_set_radius(&style_src_main_ddlist_lock_mode_main_main_focused, 3);
	lv_style_set_bg_color(&style_src_main_ddlist_lock_mode_main_main_focused, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_src_main_ddlist_lock_mode_main_main_focused, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_src_main_ddlist_lock_mode_main_main_focused, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_ddlist_lock_mode_main_main_focused, 255);
	lv_style_set_border_color(&style_src_main_ddlist_lock_mode_main_main_focused, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_src_main_ddlist_lock_mode_main_main_focused, 1);
	lv_style_set_border_opa(&style_src_main_ddlist_lock_mode_main_main_focused, 255);
	lv_style_set_text_color(&style_src_main_ddlist_lock_mode_main_main_focused, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_src_main_ddlist_lock_mode_main_main_focused, &lv_font_simsun_12);
	lv_style_set_pad_left(&style_src_main_ddlist_lock_mode_main_main_focused, 6);
	lv_style_set_pad_right(&style_src_main_ddlist_lock_mode_main_main_focused, 6);
	lv_style_set_pad_top(&style_src_main_ddlist_lock_mode_main_main_focused, 8);
	lv_obj_add_style(ui->src_main_ddlist_lock_mode, &style_src_main_ddlist_lock_mode_main_main_focused, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Write style state: LV_STATE_CHECKED for style_src_main_ddlist_lock_mode_extra_list_selected_checked
	static lv_style_t style_src_main_ddlist_lock_mode_extra_list_selected_checked;
	if (style_src_main_ddlist_lock_mode_extra_list_selected_checked.prop_cnt > 1)
		lv_style_reset(&style_src_main_ddlist_lock_mode_extra_list_selected_checked);
	else
		lv_style_init(&style_src_main_ddlist_lock_mode_extra_list_selected_checked);
	lv_style_set_radius(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, 255);
	lv_style_set_text_color(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, &lv_font_simsun_12);
	lv_style_set_pad_left(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, 6);
	lv_style_set_pad_right(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, 6);
	lv_style_set_pad_top(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, 6);
	lv_style_set_pad_bottom(&style_src_main_ddlist_lock_mode_extra_list_selected_checked, 6);
	lv_obj_add_style(lv_dropdown_get_list(ui->src_main_ddlist_lock_mode), &style_src_main_ddlist_lock_mode_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for style_src_main_ddlist_lock_mode_extra_list_main_default
	static lv_style_t style_src_main_ddlist_lock_mode_extra_list_main_default;
	if (style_src_main_ddlist_lock_mode_extra_list_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_ddlist_lock_mode_extra_list_main_default);
	else
		lv_style_init(&style_src_main_ddlist_lock_mode_extra_list_main_default);
	lv_style_set_radius(&style_src_main_ddlist_lock_mode_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_src_main_ddlist_lock_mode_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_src_main_ddlist_lock_mode_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_src_main_ddlist_lock_mode_extra_list_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_ddlist_lock_mode_extra_list_main_default, 255);
	lv_style_set_border_color(&style_src_main_ddlist_lock_mode_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_src_main_ddlist_lock_mode_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_src_main_ddlist_lock_mode_extra_list_main_default, 255);
	lv_style_set_text_color(&style_src_main_ddlist_lock_mode_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_src_main_ddlist_lock_mode_extra_list_main_default, &lv_font_simsun_12);
	lv_style_set_pad_left(&style_src_main_ddlist_lock_mode_extra_list_main_default, 6);
	lv_style_set_pad_right(&style_src_main_ddlist_lock_mode_extra_list_main_default, 6);
	lv_style_set_pad_top(&style_src_main_ddlist_lock_mode_extra_list_main_default, 6);
	lv_style_set_pad_bottom(&style_src_main_ddlist_lock_mode_extra_list_main_default, 6);
	lv_style_set_max_height(&style_src_main_ddlist_lock_mode_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(ui->src_main_ddlist_lock_mode), &style_src_main_ddlist_lock_mode_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_src_main_ddlist_lock_mode_extra_list_scrollbar_default
	static lv_style_t style_src_main_ddlist_lock_mode_extra_list_scrollbar_default;
	if (style_src_main_ddlist_lock_mode_extra_list_scrollbar_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_ddlist_lock_mode_extra_list_scrollbar_default);
	else
		lv_style_init(&style_src_main_ddlist_lock_mode_extra_list_scrollbar_default);
	lv_style_set_radius(&style_src_main_ddlist_lock_mode_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_src_main_ddlist_lock_mode_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_opa(&style_src_main_ddlist_lock_mode_extra_list_scrollbar_default, 255);
	lv_style_set_pad_left(&style_src_main_ddlist_lock_mode_extra_list_scrollbar_default, 6);
	lv_style_set_pad_right(&style_src_main_ddlist_lock_mode_extra_list_scrollbar_default, 6);
	lv_style_set_pad_top(&style_src_main_ddlist_lock_mode_extra_list_scrollbar_default, 6);
	lv_style_set_pad_bottom(&style_src_main_ddlist_lock_mode_extra_list_scrollbar_default, 6);
	lv_obj_add_style(lv_dropdown_get_list(ui->src_main_ddlist_lock_mode), &style_src_main_ddlist_lock_mode_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes src_main_slider_1
	ui->src_main_slider_1 = lv_slider_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_slider_1, 17, 67);
	lv_obj_set_size(ui->src_main_slider_1, 10, 160);
	lv_obj_set_scrollbar_mode(ui->src_main_slider_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_src_main_slider_1_main_main_default
	static lv_style_t style_src_main_slider_1_main_main_default;
	if (style_src_main_slider_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_slider_1_main_main_default);
	else
		lv_style_init(&style_src_main_slider_1_main_main_default);
	lv_style_set_radius(&style_src_main_slider_1_main_main_default, 50);
	lv_style_set_bg_color(&style_src_main_slider_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_slider_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_slider_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_slider_1_main_main_default, 60);
	lv_style_set_outline_color(&style_src_main_slider_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_outline_width(&style_src_main_slider_1_main_main_default, 0);
	lv_style_set_outline_opa(&style_src_main_slider_1_main_main_default, 0);
	lv_obj_add_style(ui->src_main_slider_1, &style_src_main_slider_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_src_main_slider_1_main_indicator_default
	static lv_style_t style_src_main_slider_1_main_indicator_default;
	if (style_src_main_slider_1_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_slider_1_main_indicator_default);
	else
		lv_style_init(&style_src_main_slider_1_main_indicator_default);
	lv_style_set_radius(&style_src_main_slider_1_main_indicator_default, 50);
	lv_style_set_bg_color(&style_src_main_slider_1_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_slider_1_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_slider_1_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_slider_1_main_indicator_default, 255);
	lv_obj_add_style(ui->src_main_slider_1, &style_src_main_slider_1_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_src_main_slider_1_main_knob_default
	static lv_style_t style_src_main_slider_1_main_knob_default;
	if (style_src_main_slider_1_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_slider_1_main_knob_default);
	else
		lv_style_init(&style_src_main_slider_1_main_knob_default);
	lv_style_set_radius(&style_src_main_slider_1_main_knob_default, 50);
	lv_style_set_bg_color(&style_src_main_slider_1_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_slider_1_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_slider_1_main_knob_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_slider_1_main_knob_default, 255);
	lv_obj_add_style(ui->src_main_slider_1, &style_src_main_slider_1_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_slider_set_range(ui->src_main_slider_1,0, 100);
	lv_slider_set_value(ui->src_main_slider_1,50,false);

	//Write codes src_main_btn_send_data
	ui->src_main_btn_send_data = lv_btn_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_btn_send_data, 16, 260);
	lv_obj_set_size(ui->src_main_btn_send_data, 100, 25);
	lv_obj_set_scrollbar_mode(ui->src_main_btn_send_data, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_src_main_btn_send_data_main_main_default
	static lv_style_t style_src_main_btn_send_data_main_main_default;
	if (style_src_main_btn_send_data_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_btn_send_data_main_main_default);
	else
		lv_style_init(&style_src_main_btn_send_data_main_main_default);
	lv_style_set_radius(&style_src_main_btn_send_data_main_main_default, 5);
	lv_style_set_bg_color(&style_src_main_btn_send_data_main_main_default, lv_color_make(0x08, 0x93, 0xf7));
	lv_style_set_bg_grad_color(&style_src_main_btn_send_data_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_btn_send_data_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_btn_send_data_main_main_default, 255);
	lv_style_set_border_color(&style_src_main_btn_send_data_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_src_main_btn_send_data_main_main_default, 0);
	lv_style_set_border_opa(&style_src_main_btn_send_data_main_main_default, 255);
	lv_style_set_text_color(&style_src_main_btn_send_data_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_src_main_btn_send_data_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_src_main_btn_send_data_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->src_main_btn_send_data, &style_src_main_btn_send_data_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->src_main_btn_send_data_label = lv_label_create(ui->src_main_btn_send_data);
	lv_label_set_text(ui->src_main_btn_send_data_label, "Send Data");
	lv_obj_set_style_pad_all(ui->src_main_btn_send_data, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->src_main_btn_send_data_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes src_main_cb_send_enable
	ui->src_main_cb_send_enable = lv_checkbox_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_cb_send_enable, 160, 271);
	lv_obj_set_scrollbar_mode(ui->src_main_cb_send_enable, LV_SCROLLBAR_MODE_OFF);
	lv_checkbox_set_text(ui->src_main_cb_send_enable, "send enable");

	//Write style state: LV_STATE_DEFAULT for style_src_main_cb_send_enable_main_main_default
	static lv_style_t style_src_main_cb_send_enable_main_main_default;
	if (style_src_main_cb_send_enable_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_cb_send_enable_main_main_default);
	else
		lv_style_init(&style_src_main_cb_send_enable_main_main_default);
	lv_style_set_radius(&style_src_main_cb_send_enable_main_main_default, 6);
	lv_style_set_bg_color(&style_src_main_cb_send_enable_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_src_main_cb_send_enable_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_src_main_cb_send_enable_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_cb_send_enable_main_main_default, 0);
	lv_style_set_text_color(&style_src_main_cb_send_enable_main_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_src_main_cb_send_enable_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_src_main_cb_send_enable_main_main_default, 2);
	lv_obj_add_style(ui->src_main_cb_send_enable, &style_src_main_cb_send_enable_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_src_main_cb_send_enable_main_indicator_default
	static lv_style_t style_src_main_cb_send_enable_main_indicator_default;
	if (style_src_main_cb_send_enable_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_cb_send_enable_main_indicator_default);
	else
		lv_style_init(&style_src_main_cb_send_enable_main_indicator_default);
	lv_style_set_radius(&style_src_main_cb_send_enable_main_indicator_default, 6);
	lv_style_set_bg_color(&style_src_main_cb_send_enable_main_indicator_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_src_main_cb_send_enable_main_indicator_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_src_main_cb_send_enable_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_cb_send_enable_main_indicator_default, 255);
	lv_style_set_border_color(&style_src_main_cb_send_enable_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_src_main_cb_send_enable_main_indicator_default, 2);
	lv_style_set_border_opa(&style_src_main_cb_send_enable_main_indicator_default, 255);
	lv_obj_add_style(ui->src_main_cb_send_enable, &style_src_main_cb_send_enable_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes src_main_cb_receive_enable
	ui->src_main_cb_receive_enable = lv_checkbox_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_cb_receive_enable, 169, 243);
	lv_obj_set_scrollbar_mode(ui->src_main_cb_receive_enable, LV_SCROLLBAR_MODE_OFF);
	lv_checkbox_set_text(ui->src_main_cb_receive_enable, "receive enable");

	//Write style state: LV_STATE_DEFAULT for style_src_main_cb_receive_enable_main_main_default
	static lv_style_t style_src_main_cb_receive_enable_main_main_default;
	if (style_src_main_cb_receive_enable_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_cb_receive_enable_main_main_default);
	else
		lv_style_init(&style_src_main_cb_receive_enable_main_main_default);
	lv_style_set_radius(&style_src_main_cb_receive_enable_main_main_default, 6);
	lv_style_set_bg_color(&style_src_main_cb_receive_enable_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_src_main_cb_receive_enable_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_src_main_cb_receive_enable_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_cb_receive_enable_main_main_default, 0);
	lv_style_set_text_color(&style_src_main_cb_receive_enable_main_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_src_main_cb_receive_enable_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_src_main_cb_receive_enable_main_main_default, 2);
	lv_obj_add_style(ui->src_main_cb_receive_enable, &style_src_main_cb_receive_enable_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_src_main_cb_receive_enable_main_indicator_default
	static lv_style_t style_src_main_cb_receive_enable_main_indicator_default;
	if (style_src_main_cb_receive_enable_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_cb_receive_enable_main_indicator_default);
	else
		lv_style_init(&style_src_main_cb_receive_enable_main_indicator_default);
	lv_style_set_radius(&style_src_main_cb_receive_enable_main_indicator_default, 6);
	lv_style_set_bg_color(&style_src_main_cb_receive_enable_main_indicator_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_src_main_cb_receive_enable_main_indicator_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_src_main_cb_receive_enable_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_cb_receive_enable_main_indicator_default, 255);
	lv_style_set_border_color(&style_src_main_cb_receive_enable_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_src_main_cb_receive_enable_main_indicator_default, 2);
	lv_style_set_border_opa(&style_src_main_cb_receive_enable_main_indicator_default, 255);
	lv_obj_add_style(ui->src_main_cb_receive_enable, &style_src_main_cb_receive_enable_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes src_main_bar_Iq
	ui->src_main_bar_Iq = lv_bar_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_bar_Iq, 452, 53);
	lv_obj_set_size(ui->src_main_bar_Iq, 12, 132);
	lv_obj_set_scrollbar_mode(ui->src_main_bar_Iq, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_src_main_bar_iq_main_main_default
	static lv_style_t style_src_main_bar_iq_main_main_default;
	if (style_src_main_bar_iq_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_bar_iq_main_main_default);
	else
		lv_style_init(&style_src_main_bar_iq_main_main_default);
	lv_style_set_radius(&style_src_main_bar_iq_main_main_default, 10);
	lv_style_set_bg_color(&style_src_main_bar_iq_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_bar_iq_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_bar_iq_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_bar_iq_main_main_default, 60);
	lv_obj_add_style(ui->src_main_bar_Iq, &style_src_main_bar_iq_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_src_main_bar_iq_main_indicator_default
	static lv_style_t style_src_main_bar_iq_main_indicator_default;
	if (style_src_main_bar_iq_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_bar_iq_main_indicator_default);
	else
		lv_style_init(&style_src_main_bar_iq_main_indicator_default);
	lv_style_set_radius(&style_src_main_bar_iq_main_indicator_default, 10);
	lv_style_set_bg_color(&style_src_main_bar_iq_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_bar_iq_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_bar_iq_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_bar_iq_main_indicator_default, 255);
	lv_obj_add_style(ui->src_main_bar_Iq, &style_src_main_bar_iq_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_anim_time(ui->src_main_bar_Iq, 1000, 0);
	lv_bar_set_mode(ui->src_main_bar_Iq, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->src_main_bar_Iq, 50, LV_ANIM_OFF);

	//Write codes src_main_bar_voltage
	ui->src_main_bar_voltage = lv_bar_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_bar_voltage, 6, 10);
	lv_obj_set_size(ui->src_main_bar_voltage, 121, 8);
	lv_obj_set_scrollbar_mode(ui->src_main_bar_voltage, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_src_main_bar_voltage_main_main_default
	static lv_style_t style_src_main_bar_voltage_main_main_default;
	if (style_src_main_bar_voltage_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_bar_voltage_main_main_default);
	else
		lv_style_init(&style_src_main_bar_voltage_main_main_default);
	lv_style_set_radius(&style_src_main_bar_voltage_main_main_default, 10);
	lv_style_set_bg_color(&style_src_main_bar_voltage_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_bar_voltage_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_bar_voltage_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_bar_voltage_main_main_default, 60);
	lv_obj_add_style(ui->src_main_bar_voltage, &style_src_main_bar_voltage_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_src_main_bar_voltage_main_indicator_default
	static lv_style_t style_src_main_bar_voltage_main_indicator_default;
	if (style_src_main_bar_voltage_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_bar_voltage_main_indicator_default);
	else
		lv_style_init(&style_src_main_bar_voltage_main_indicator_default);
	lv_style_set_radius(&style_src_main_bar_voltage_main_indicator_default, 10);
	lv_style_set_bg_color(&style_src_main_bar_voltage_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_bar_voltage_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_bar_voltage_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_bar_voltage_main_indicator_default, 255);
	lv_obj_add_style(ui->src_main_bar_voltage, &style_src_main_bar_voltage_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_anim_time(ui->src_main_bar_voltage, 1000, 0);
	lv_bar_set_mode(ui->src_main_bar_voltage, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->src_main_bar_voltage, 50, LV_ANIM_OFF);

	//Write codes src_main_bar_current
	ui->src_main_bar_current = lv_bar_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_bar_current, 6, 24);
	lv_obj_set_size(ui->src_main_bar_current, 121, 8);
	lv_obj_set_scrollbar_mode(ui->src_main_bar_current, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_src_main_bar_current_main_main_default
	static lv_style_t style_src_main_bar_current_main_main_default;
	if (style_src_main_bar_current_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_bar_current_main_main_default);
	else
		lv_style_init(&style_src_main_bar_current_main_main_default);
	lv_style_set_radius(&style_src_main_bar_current_main_main_default, 10);
	lv_style_set_bg_color(&style_src_main_bar_current_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_bar_current_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_bar_current_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_bar_current_main_main_default, 60);
	lv_obj_add_style(ui->src_main_bar_current, &style_src_main_bar_current_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_src_main_bar_current_main_indicator_default
	static lv_style_t style_src_main_bar_current_main_indicator_default;
	if (style_src_main_bar_current_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_bar_current_main_indicator_default);
	else
		lv_style_init(&style_src_main_bar_current_main_indicator_default);
	lv_style_set_radius(&style_src_main_bar_current_main_indicator_default, 10);
	lv_style_set_bg_color(&style_src_main_bar_current_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_bar_current_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_bar_current_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_bar_current_main_indicator_default, 255);
	lv_obj_add_style(ui->src_main_bar_current, &style_src_main_bar_current_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_anim_time(ui->src_main_bar_current, 1000, 0);
	lv_bar_set_mode(ui->src_main_bar_current, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->src_main_bar_current, 50, LV_ANIM_OFF);

	//Write codes src_main_meter_angle
	ui->src_main_meter_angle = lv_meter_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_meter_angle, 42, 67);
	lv_obj_set_size(ui->src_main_meter_angle, 160, 160);
	lv_obj_set_scrollbar_mode(ui->src_main_meter_angle, LV_SCROLLBAR_MODE_OFF);

	//add scale src_main_meter_angle_scale_1
	lv_meter_scale_t *src_main_meter_angle_scale_1 = lv_meter_add_scale(ui->src_main_meter_angle);
	lv_meter_set_scale_ticks(ui->src_main_meter_angle, src_main_meter_angle_scale_1, 61, 3, 3, lv_color_make(0xff, 0x00, 0x00));
	lv_meter_set_scale_range(ui->src_main_meter_angle, src_main_meter_angle_scale_1, 0, 360, 360, 0);

	//add arc for src_main_meter_angle_scale_1
	//lv_meter_indicator_t *src_main_meter_angle_scale_1_arc_0;
	ui->src_main_meter_angle_scale_1_arc_0 = lv_meter_add_arc(ui->src_main_meter_angle, src_main_meter_angle_scale_1, 12, lv_color_make(0x8a, 0x41, 0x0a), 15);
	lv_meter_set_indicator_start_value(ui->src_main_meter_angle, ui->src_main_meter_angle_scale_1_arc_0, 10);
	lv_meter_set_indicator_end_value(ui->src_main_meter_angle, ui->src_main_meter_angle_scale_1_arc_0, 20);

	//add scale src_main_meter_angle_scale_2
	lv_meter_scale_t *src_main_meter_angle_scale_2 = lv_meter_add_scale(ui->src_main_meter_angle);
	lv_meter_set_scale_ticks(ui->src_main_meter_angle, src_main_meter_angle_scale_2, 12, 0, 0, lv_color_make(0xff, 0x00, 0x00));
	lv_meter_set_scale_major_ticks(ui->src_main_meter_angle, src_main_meter_angle_scale_2, 1, 5, 9, lv_color_make(0x00, 0x40, 0xff), 10);
	lv_meter_set_scale_range(ui->src_main_meter_angle, src_main_meter_angle_scale_2, 0, 330, 330, 0);

	//Write style state: LV_STATE_DEFAULT for style_src_main_meter_angle_main_main_default
	static lv_style_t style_src_main_meter_angle_main_main_default;
	if (style_src_main_meter_angle_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_meter_angle_main_main_default);
	else
		lv_style_init(&style_src_main_meter_angle_main_main_default);
	lv_style_set_radius(&style_src_main_meter_angle_main_main_default, 200);
	lv_style_set_bg_color(&style_src_main_meter_angle_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_src_main_meter_angle_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_src_main_meter_angle_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_meter_angle_main_main_default, 255);
	lv_style_set_shadow_width(&style_src_main_meter_angle_main_main_default, 5);
	lv_style_set_shadow_color(&style_src_main_meter_angle_main_main_default, lv_color_make(0x19, 0x0c, 0xcf));
	lv_style_set_shadow_opa(&style_src_main_meter_angle_main_main_default, 158);
	lv_style_set_shadow_spread(&style_src_main_meter_angle_main_main_default, 4);
	lv_style_set_shadow_ofs_x(&style_src_main_meter_angle_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_src_main_meter_angle_main_main_default, 0);
	lv_style_set_border_color(&style_src_main_meter_angle_main_main_default, lv_color_make(0x22, 0x86, 0xd8));
	lv_style_set_border_width(&style_src_main_meter_angle_main_main_default, 0);
	lv_style_set_border_opa(&style_src_main_meter_angle_main_main_default, 255);
	lv_obj_add_style(ui->src_main_meter_angle, &style_src_main_meter_angle_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_src_main_meter_angle_main_ticks_default
	static lv_style_t style_src_main_meter_angle_main_ticks_default;
	if (style_src_main_meter_angle_main_ticks_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_meter_angle_main_ticks_default);
	else
		lv_style_init(&style_src_main_meter_angle_main_ticks_default);
	lv_style_set_text_color(&style_src_main_meter_angle_main_ticks_default, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&style_src_main_meter_angle_main_ticks_default, &lv_font_simsun_12);
	lv_obj_add_style(ui->src_main_meter_angle, &style_src_main_meter_angle_main_ticks_default, LV_PART_TICKS|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_FOCUSED for style_src_main_meter_angle_main_ticks_focused
	static lv_style_t style_src_main_meter_angle_main_ticks_focused;
	if (style_src_main_meter_angle_main_ticks_focused.prop_cnt > 1)
		lv_style_reset(&style_src_main_meter_angle_main_ticks_focused);
	else
		lv_style_init(&style_src_main_meter_angle_main_ticks_focused);
	lv_style_set_text_color(&style_src_main_meter_angle_main_ticks_focused, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&style_src_main_meter_angle_main_ticks_focused, &lv_font_simsun_12);
	lv_obj_add_style(ui->src_main_meter_angle, &style_src_main_meter_angle_main_ticks_focused, LV_PART_TICKS|LV_STATE_FOCUSED);

	//Write codes src_main_meter_omega
	ui->src_main_meter_omega = lv_meter_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_meter_omega, 265, 67);
	lv_obj_set_size(ui->src_main_meter_omega, 160, 160);
	lv_obj_set_scrollbar_mode(ui->src_main_meter_omega, LV_SCROLLBAR_MODE_OFF);

	//add scale src_main_meter_omega_scale_1
	lv_meter_scale_t *src_main_meter_omega_scale_1 = lv_meter_add_scale(ui->src_main_meter_omega);
	lv_meter_set_scale_ticks(ui->src_main_meter_omega, src_main_meter_omega_scale_1, 41, 2, 12, lv_color_make(0xaa, 0xc5, 0x26));
	lv_meter_set_scale_major_ticks(ui->src_main_meter_omega, src_main_meter_omega_scale_1, 8, 3, 16, lv_color_make(0x00, 0x04, 0xf5), 10);
	lv_meter_set_scale_range(ui->src_main_meter_omega, src_main_meter_omega_scale_1, 0, 900, 270, 135);

	//add arc for src_main_meter_omega_scale_1
	//lv_meter_indicator_t *src_main_meter_omega_scale_1_arc_0;
	ui->src_main_meter_omega_scale_1_arc_0 = lv_meter_add_arc(ui->src_main_meter_omega, src_main_meter_omega_scale_1, 12, lv_color_make(0x4c, 0x00, 0xff), 0);
	lv_meter_set_indicator_start_value(ui->src_main_meter_omega, ui->src_main_meter_omega_scale_1_arc_0, 0);
	lv_meter_set_indicator_end_value(ui->src_main_meter_omega, ui->src_main_meter_omega_scale_1_arc_0, 360);

	//add arc for src_main_meter_omega_scale_1
	//lv_meter_indicator_t *src_main_meter_omega_scale_1_arc_1;
	ui->src_main_meter_omega_scale_1_arc_1 = lv_meter_add_arc(ui->src_main_meter_omega, src_main_meter_omega_scale_1, 6, lv_color_make(0xff, 0x00, 0x00), 8);
	lv_meter_set_indicator_start_value(ui->src_main_meter_omega, ui->src_main_meter_omega_scale_1_arc_1, 0);
	lv_meter_set_indicator_end_value(ui->src_main_meter_omega, ui->src_main_meter_omega_scale_1_arc_1, 540);

	//add scale line for src_main_meter_omega_scale_1
	lv_meter_indicator_t *src_main_meter_omega_scale_1_scaleline_0;
	src_main_meter_omega_scale_1_scaleline_0 = lv_meter_add_scale_lines(ui->src_main_meter_omega, src_main_meter_omega_scale_1, lv_color_make(0x00, 0xf0, 0x30), lv_color_make(0x00, 0xf0, 0x68), false, 0);
	lv_meter_set_indicator_start_value(ui->src_main_meter_omega, src_main_meter_omega_scale_1_scaleline_0, 0);
	lv_meter_set_indicator_end_value(ui->src_main_meter_omega, src_main_meter_omega_scale_1_scaleline_0, 180);

	//add scale line for src_main_meter_omega_scale_1
	lv_meter_indicator_t *src_main_meter_omega_scale_1_scaleline_1;
	src_main_meter_omega_scale_1_scaleline_1 = lv_meter_add_scale_lines(ui->src_main_meter_omega, src_main_meter_omega_scale_1, lv_color_make(0xff, 0x00, 0x19), lv_color_make(0xfe, 0x06, 0x06), false, 0);
	lv_meter_set_indicator_start_value(ui->src_main_meter_omega, src_main_meter_omega_scale_1_scaleline_1, 720);
	lv_meter_set_indicator_end_value(ui->src_main_meter_omega, src_main_meter_omega_scale_1_scaleline_1, 900);

	//Write style state: LV_STATE_DEFAULT for style_src_main_meter_omega_main_main_default
	static lv_style_t style_src_main_meter_omega_main_main_default;
	if (style_src_main_meter_omega_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_meter_omega_main_main_default);
	else
		lv_style_init(&style_src_main_meter_omega_main_main_default);
	lv_style_set_radius(&style_src_main_meter_omega_main_main_default, 200);
	lv_style_set_bg_color(&style_src_main_meter_omega_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_src_main_meter_omega_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_src_main_meter_omega_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_meter_omega_main_main_default, 255);
	lv_style_set_shadow_width(&style_src_main_meter_omega_main_main_default, 4);
	lv_style_set_shadow_color(&style_src_main_meter_omega_main_main_default, lv_color_make(0x71, 0x9d, 0xc1));
	lv_style_set_shadow_opa(&style_src_main_meter_omega_main_main_default, 255);
	lv_style_set_shadow_spread(&style_src_main_meter_omega_main_main_default, 5);
	lv_style_set_shadow_ofs_x(&style_src_main_meter_omega_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_src_main_meter_omega_main_main_default, 0);
	lv_style_set_border_color(&style_src_main_meter_omega_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_src_main_meter_omega_main_main_default, 0);
	lv_style_set_border_opa(&style_src_main_meter_omega_main_main_default, 255);
	lv_obj_add_style(ui->src_main_meter_omega, &style_src_main_meter_omega_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_src_main_meter_omega_main_ticks_default
	static lv_style_t style_src_main_meter_omega_main_ticks_default;
	if (style_src_main_meter_omega_main_ticks_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_meter_omega_main_ticks_default);
	else
		lv_style_init(&style_src_main_meter_omega_main_ticks_default);
	lv_style_set_text_color(&style_src_main_meter_omega_main_ticks_default, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&style_src_main_meter_omega_main_ticks_default, &lv_font_simsun_12);
	lv_obj_add_style(ui->src_main_meter_omega, &style_src_main_meter_omega_main_ticks_default, LV_PART_TICKS|LV_STATE_DEFAULT);

	//Write codes src_main_label_angle
	ui->src_main_label_angle = lv_label_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_label_angle, 72, 162);
	lv_obj_set_size(ui->src_main_label_angle, 100, 16);
	lv_obj_set_scrollbar_mode(ui->src_main_label_angle, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->src_main_label_angle, "180/300");
	lv_label_set_long_mode(ui->src_main_label_angle, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_src_main_label_angle_main_main_default
	static lv_style_t style_src_main_label_angle_main_main_default;
	if (style_src_main_label_angle_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_label_angle_main_main_default);
	else
		lv_style_init(&style_src_main_label_angle_main_main_default);
	lv_style_set_radius(&style_src_main_label_angle_main_main_default, 0);
	lv_style_set_bg_color(&style_src_main_label_angle_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_label_angle_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_label_angle_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_label_angle_main_main_default, 0);
	lv_style_set_text_color(&style_src_main_label_angle_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_src_main_label_angle_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_src_main_label_angle_main_main_default, 2);
	lv_style_set_text_line_space(&style_src_main_label_angle_main_main_default, 0);
	lv_style_set_text_align(&style_src_main_label_angle_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_src_main_label_angle_main_main_default, 0);
	lv_style_set_pad_right(&style_src_main_label_angle_main_main_default, 0);
	lv_style_set_pad_top(&style_src_main_label_angle_main_main_default, 0);
	lv_style_set_pad_bottom(&style_src_main_label_angle_main_main_default, 0);
	lv_obj_add_style(ui->src_main_label_angle, &style_src_main_label_angle_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes src_main_label_omega
	ui->src_main_label_omega = lv_label_create(ui->src_main);
	lv_obj_set_pos(ui->src_main_label_omega, 295, 199);
	lv_obj_set_size(ui->src_main_label_omega, 100, 20);
	lv_obj_set_scrollbar_mode(ui->src_main_label_omega, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->src_main_label_omega, "120/120");
	lv_label_set_long_mode(ui->src_main_label_omega, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_src_main_label_omega_main_main_default
	static lv_style_t style_src_main_label_omega_main_main_default;
	if (style_src_main_label_omega_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_src_main_label_omega_main_main_default);
	else
		lv_style_init(&style_src_main_label_omega_main_main_default);
	lv_style_set_radius(&style_src_main_label_omega_main_main_default, 0);
	lv_style_set_bg_color(&style_src_main_label_omega_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_src_main_label_omega_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_src_main_label_omega_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_src_main_label_omega_main_main_default, 0);
	lv_style_set_text_color(&style_src_main_label_omega_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_src_main_label_omega_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_src_main_label_omega_main_main_default, 2);
	lv_style_set_text_line_space(&style_src_main_label_omega_main_main_default, 0);
	lv_style_set_text_align(&style_src_main_label_omega_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_src_main_label_omega_main_main_default, 0);
	lv_style_set_pad_right(&style_src_main_label_omega_main_main_default, 0);
	lv_style_set_pad_top(&style_src_main_label_omega_main_main_default, 0);
	lv_style_set_pad_bottom(&style_src_main_label_omega_main_main_default, 0);
	lv_obj_add_style(ui->src_main_label_omega, &style_src_main_label_omega_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}