# Copyright 2022 NXP
# SPDX-License-Identifier: MIT
# The auto-generated can only be used on NXP devices

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=480,h=320)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(480*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 480
disp_drv.ver_res = 320
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)


src_main = lv.obj()
src_main.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_src_main_main_main_default
style_src_main_main_main_default = lv.style_t()
style_src_main_main_main_default.init()
style_src_main_main_main_default.set_bg_color(lv.color_make(0xf7,0xf7,0xf7))
style_src_main_main_main_default.set_bg_opa(128)

# add style for src_main
src_main.add_style(style_src_main_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

src_main_ddlist_lock_mode = lv.dropdown(src_main)
src_main_ddlist_lock_mode.set_pos(int(332),int(243))
src_main_ddlist_lock_mode.set_size(93,28)
src_main_ddlist_lock_mode.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_ddlist_lock_mode.set_options("Lock Angle\nLock Omega\nLock Touqre")

src_main_ddlist_lock_mode_list = src_main_ddlist_lock_mode.get_list()
# create style style_src_main_ddlist_lock_mode_extra_list_selected_checked
style_src_main_ddlist_lock_mode_extra_list_selected_checked = lv.style_t()
style_src_main_ddlist_lock_mode_extra_list_selected_checked.init()
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_radius(3)
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_bg_color(lv.color_make(0x00,0xa1,0xb5))
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_bg_grad_color(lv.color_make(0x00,0xa1,0xb5))
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_bg_opa(255)
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_border_color(lv.color_make(0xe1,0xe6,0xee))
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_border_width(1)
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_border_opa(255)
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_text_font(lv.font_montserrat_16)
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_pad_left(6)
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_pad_right(6)
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_pad_top(6)
style_src_main_ddlist_lock_mode_extra_list_selected_checked.set_pad_bottom(6)

# add style for src_main_ddlist_lock_mode_list
src_main_ddlist_lock_mode_list.add_style(style_src_main_ddlist_lock_mode_extra_list_selected_checked, lv.PART.SELECTED|lv.STATE.CHECKED)

# create style style_src_main_ddlist_lock_mode_extra_list_main_default
style_src_main_ddlist_lock_mode_extra_list_main_default = lv.style_t()
style_src_main_ddlist_lock_mode_extra_list_main_default.init()
style_src_main_ddlist_lock_mode_extra_list_main_default.set_radius(3)
style_src_main_ddlist_lock_mode_extra_list_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_src_main_ddlist_lock_mode_extra_list_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_src_main_ddlist_lock_mode_extra_list_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_ddlist_lock_mode_extra_list_main_default.set_bg_opa(255)
style_src_main_ddlist_lock_mode_extra_list_main_default.set_border_color(lv.color_make(0xe1,0xe6,0xee))
style_src_main_ddlist_lock_mode_extra_list_main_default.set_border_width(1)
style_src_main_ddlist_lock_mode_extra_list_main_default.set_border_opa(255)
style_src_main_ddlist_lock_mode_extra_list_main_default.set_text_color(lv.color_make(0x0D,0x30,0x55))
try:
    style_src_main_ddlist_lock_mode_extra_list_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_ddlist_lock_mode_extra_list_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_ddlist_lock_mode_extra_list_main_default.set_text_font(lv.font_montserrat_16)
style_src_main_ddlist_lock_mode_extra_list_main_default.set_pad_left(6)
style_src_main_ddlist_lock_mode_extra_list_main_default.set_pad_right(6)
style_src_main_ddlist_lock_mode_extra_list_main_default.set_pad_top(6)
style_src_main_ddlist_lock_mode_extra_list_main_default.set_pad_bottom(6)
style_src_main_ddlist_lock_mode_extra_list_main_default.set_max_height(90)

# add style for src_main_ddlist_lock_mode_list
src_main_ddlist_lock_mode_list.add_style(style_src_main_ddlist_lock_mode_extra_list_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_src_main_ddlist_lock_mode_extra_list_scrollbar_default
style_src_main_ddlist_lock_mode_extra_list_scrollbar_default = lv.style_t()
style_src_main_ddlist_lock_mode_extra_list_scrollbar_default.init()
style_src_main_ddlist_lock_mode_extra_list_scrollbar_default.set_radius(3)
style_src_main_ddlist_lock_mode_extra_list_scrollbar_default.set_bg_color(lv.color_make(0x00,0xff,0x00))
style_src_main_ddlist_lock_mode_extra_list_scrollbar_default.set_bg_opa(255)
style_src_main_ddlist_lock_mode_extra_list_scrollbar_default.set_pad_left(6)
style_src_main_ddlist_lock_mode_extra_list_scrollbar_default.set_pad_right(6)
style_src_main_ddlist_lock_mode_extra_list_scrollbar_default.set_pad_top(6)
style_src_main_ddlist_lock_mode_extra_list_scrollbar_default.set_pad_bottom(6)

# add style for src_main_ddlist_lock_mode_list
src_main_ddlist_lock_mode_list.add_style(style_src_main_ddlist_lock_mode_extra_list_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# create style style_src_main_ddlist_lock_mode_main_main_default
style_src_main_ddlist_lock_mode_main_main_default = lv.style_t()
style_src_main_ddlist_lock_mode_main_main_default.init()
style_src_main_ddlist_lock_mode_main_main_default.set_radius(3)
style_src_main_ddlist_lock_mode_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_src_main_ddlist_lock_mode_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_src_main_ddlist_lock_mode_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_ddlist_lock_mode_main_main_default.set_bg_opa(255)
style_src_main_ddlist_lock_mode_main_main_default.set_border_color(lv.color_make(0xe1,0xe6,0xee))
style_src_main_ddlist_lock_mode_main_main_default.set_border_width(1)
style_src_main_ddlist_lock_mode_main_main_default.set_border_opa(255)
style_src_main_ddlist_lock_mode_main_main_default.set_text_color(lv.color_make(0x0D,0x30,0x55))
try:
    style_src_main_ddlist_lock_mode_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_ddlist_lock_mode_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_ddlist_lock_mode_main_main_default.set_text_font(lv.font_montserrat_16)
style_src_main_ddlist_lock_mode_main_main_default.set_pad_left(6)
style_src_main_ddlist_lock_mode_main_main_default.set_pad_right(6)
style_src_main_ddlist_lock_mode_main_main_default.set_pad_top(8)

# add style for src_main_ddlist_lock_mode
src_main_ddlist_lock_mode.add_style(style_src_main_ddlist_lock_mode_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_src_main_ddlist_lock_mode_main_main_focused
style_src_main_ddlist_lock_mode_main_main_focused = lv.style_t()
style_src_main_ddlist_lock_mode_main_main_focused.init()
style_src_main_ddlist_lock_mode_main_main_focused.set_radius(3)
style_src_main_ddlist_lock_mode_main_main_focused.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_src_main_ddlist_lock_mode_main_main_focused.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_src_main_ddlist_lock_mode_main_main_focused.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_ddlist_lock_mode_main_main_focused.set_bg_opa(255)
style_src_main_ddlist_lock_mode_main_main_focused.set_border_color(lv.color_make(0xe1,0xe6,0xee))
style_src_main_ddlist_lock_mode_main_main_focused.set_border_width(1)
style_src_main_ddlist_lock_mode_main_main_focused.set_border_opa(255)
style_src_main_ddlist_lock_mode_main_main_focused.set_text_color(lv.color_make(0x0D,0x30,0x55))
try:
    style_src_main_ddlist_lock_mode_main_main_focused.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_ddlist_lock_mode_main_main_focused.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_ddlist_lock_mode_main_main_focused.set_text_font(lv.font_montserrat_16)
style_src_main_ddlist_lock_mode_main_main_focused.set_pad_left(6)
style_src_main_ddlist_lock_mode_main_main_focused.set_pad_right(6)
style_src_main_ddlist_lock_mode_main_main_focused.set_pad_top(8)

# add style for src_main_ddlist_lock_mode
src_main_ddlist_lock_mode.add_style(style_src_main_ddlist_lock_mode_main_main_focused, lv.PART.MAIN|lv.STATE.FOCUSED)

src_main_slider_1 = lv.slider(src_main)
src_main_slider_1.set_pos(int(17),int(67))
src_main_slider_1.set_size(10,160)
src_main_slider_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_slider_1.set_range(0, 100)
src_main_slider_1.set_value(50, False)

# create style style_src_main_slider_1_main_main_default
style_src_main_slider_1_main_main_default = lv.style_t()
style_src_main_slider_1_main_main_default.init()
style_src_main_slider_1_main_main_default.set_radius(50)
style_src_main_slider_1_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_slider_1_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_slider_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_slider_1_main_main_default.set_bg_opa(60)
style_src_main_slider_1_main_main_default.set_outline_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_slider_1_main_main_default.set_outline_width(0)
style_src_main_slider_1_main_main_default.set_outline_opa(0)

# add style for src_main_slider_1
src_main_slider_1.add_style(style_src_main_slider_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_src_main_slider_1_main_indicator_default
style_src_main_slider_1_main_indicator_default = lv.style_t()
style_src_main_slider_1_main_indicator_default.init()
style_src_main_slider_1_main_indicator_default.set_radius(50)
style_src_main_slider_1_main_indicator_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_slider_1_main_indicator_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_slider_1_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_slider_1_main_indicator_default.set_bg_opa(255)

# add style for src_main_slider_1
src_main_slider_1.add_style(style_src_main_slider_1_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_src_main_slider_1_main_knob_default
style_src_main_slider_1_main_knob_default = lv.style_t()
style_src_main_slider_1_main_knob_default.init()
style_src_main_slider_1_main_knob_default.set_radius(50)
style_src_main_slider_1_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_slider_1_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_slider_1_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_slider_1_main_knob_default.set_bg_opa(255)

# add style for src_main_slider_1
src_main_slider_1.add_style(style_src_main_slider_1_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

src_main_btn_send_data = lv.btn(src_main)
src_main_btn_send_data.set_pos(int(16),int(260))
src_main_btn_send_data.set_size(100,25)
src_main_btn_send_data.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_btn_send_data_label = lv.label(src_main_btn_send_data)
src_main_btn_send_data_label.set_text("Send Data")
src_main_btn_send_data.set_style_pad_all(0, lv.STATE.DEFAULT)
src_main_btn_send_data_label.align(lv.ALIGN.CENTER,0,0)
# create style style_src_main_btn_send_data_main_main_default
style_src_main_btn_send_data_main_main_default = lv.style_t()
style_src_main_btn_send_data_main_main_default.init()
style_src_main_btn_send_data_main_main_default.set_radius(5)
style_src_main_btn_send_data_main_main_default.set_bg_color(lv.color_make(0x08,0x93,0xf7))
style_src_main_btn_send_data_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_btn_send_data_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_btn_send_data_main_main_default.set_bg_opa(255)
style_src_main_btn_send_data_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_btn_send_data_main_main_default.set_border_width(0)
style_src_main_btn_send_data_main_main_default.set_border_opa(255)
style_src_main_btn_send_data_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_src_main_btn_send_data_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_btn_send_data_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_btn_send_data_main_main_default.set_text_font(lv.font_montserrat_16)
style_src_main_btn_send_data_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for src_main_btn_send_data
src_main_btn_send_data.add_style(style_src_main_btn_send_data_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

src_main_cb_send_enable = lv.checkbox(src_main)
src_main_cb_send_enable.set_pos(int(160),int(271))
src_main_cb_send_enable.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_cb_send_enable.set_text("send enable")
# create style style_src_main_cb_send_enable_main_main_default
style_src_main_cb_send_enable_main_main_default = lv.style_t()
style_src_main_cb_send_enable_main_main_default.init()
style_src_main_cb_send_enable_main_main_default.set_radius(6)
style_src_main_cb_send_enable_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_src_main_cb_send_enable_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_src_main_cb_send_enable_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_cb_send_enable_main_main_default.set_bg_opa(0)
style_src_main_cb_send_enable_main_main_default.set_text_color(lv.color_make(0x0D,0x30,0x55))
try:
    style_src_main_cb_send_enable_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_cb_send_enable_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_cb_send_enable_main_main_default.set_text_font(lv.font_montserrat_16)
style_src_main_cb_send_enable_main_main_default.set_text_letter_space(2)

# add style for src_main_cb_send_enable
src_main_cb_send_enable.add_style(style_src_main_cb_send_enable_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_src_main_cb_send_enable_main_indicator_default
style_src_main_cb_send_enable_main_indicator_default = lv.style_t()
style_src_main_cb_send_enable_main_indicator_default.init()
style_src_main_cb_send_enable_main_indicator_default.set_radius(6)
style_src_main_cb_send_enable_main_indicator_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_src_main_cb_send_enable_main_indicator_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_src_main_cb_send_enable_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_cb_send_enable_main_indicator_default.set_bg_opa(255)
style_src_main_cb_send_enable_main_indicator_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_cb_send_enable_main_indicator_default.set_border_width(2)
style_src_main_cb_send_enable_main_indicator_default.set_border_opa(255)

# add style for src_main_cb_send_enable
src_main_cb_send_enable.add_style(style_src_main_cb_send_enable_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

src_main_cb_receive_enable = lv.checkbox(src_main)
src_main_cb_receive_enable.set_pos(int(169),int(243))
src_main_cb_receive_enable.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_cb_receive_enable.set_text("receive enable")
# create style style_src_main_cb_receive_enable_main_main_default
style_src_main_cb_receive_enable_main_main_default = lv.style_t()
style_src_main_cb_receive_enable_main_main_default.init()
style_src_main_cb_receive_enable_main_main_default.set_radius(6)
style_src_main_cb_receive_enable_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_src_main_cb_receive_enable_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_src_main_cb_receive_enable_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_cb_receive_enable_main_main_default.set_bg_opa(0)
style_src_main_cb_receive_enable_main_main_default.set_text_color(lv.color_make(0x0D,0x30,0x55))
try:
    style_src_main_cb_receive_enable_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_cb_receive_enable_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_cb_receive_enable_main_main_default.set_text_font(lv.font_montserrat_16)
style_src_main_cb_receive_enable_main_main_default.set_text_letter_space(2)

# add style for src_main_cb_receive_enable
src_main_cb_receive_enable.add_style(style_src_main_cb_receive_enable_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_src_main_cb_receive_enable_main_indicator_default
style_src_main_cb_receive_enable_main_indicator_default = lv.style_t()
style_src_main_cb_receive_enable_main_indicator_default.init()
style_src_main_cb_receive_enable_main_indicator_default.set_radius(6)
style_src_main_cb_receive_enable_main_indicator_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_src_main_cb_receive_enable_main_indicator_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_src_main_cb_receive_enable_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_cb_receive_enable_main_indicator_default.set_bg_opa(255)
style_src_main_cb_receive_enable_main_indicator_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_cb_receive_enable_main_indicator_default.set_border_width(2)
style_src_main_cb_receive_enable_main_indicator_default.set_border_opa(255)

# add style for src_main_cb_receive_enable
src_main_cb_receive_enable.add_style(style_src_main_cb_receive_enable_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

src_main_bar_Iq = lv.bar(src_main)
src_main_bar_Iq.set_pos(int(452),int(53))
src_main_bar_Iq.set_size(12,132)
src_main_bar_Iq.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_bar_Iq.set_style_anim_time(1000, 0)
src_main_bar_Iq.set_mode(lv.bar.MODE.NORMAL)
src_main_bar_Iq.set_value(50, lv.ANIM.OFF)
# create style style_src_main_bar_iq_main_main_default
style_src_main_bar_iq_main_main_default = lv.style_t()
style_src_main_bar_iq_main_main_default.init()
style_src_main_bar_iq_main_main_default.set_radius(10)
style_src_main_bar_iq_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_iq_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_iq_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_bar_iq_main_main_default.set_bg_opa(60)

# add style for src_main_bar_Iq
src_main_bar_Iq.add_style(style_src_main_bar_iq_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_src_main_bar_iq_main_indicator_default
style_src_main_bar_iq_main_indicator_default = lv.style_t()
style_src_main_bar_iq_main_indicator_default.init()
style_src_main_bar_iq_main_indicator_default.set_radius(10)
style_src_main_bar_iq_main_indicator_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_iq_main_indicator_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_iq_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_bar_iq_main_indicator_default.set_bg_opa(255)

# add style for src_main_bar_Iq
src_main_bar_Iq.add_style(style_src_main_bar_iq_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

src_main_bar_voltage = lv.bar(src_main)
src_main_bar_voltage.set_pos(int(6),int(10))
src_main_bar_voltage.set_size(121,8)
src_main_bar_voltage.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_bar_voltage.set_style_anim_time(1000, 0)
src_main_bar_voltage.set_mode(lv.bar.MODE.NORMAL)
src_main_bar_voltage.set_value(50, lv.ANIM.OFF)
# create style style_src_main_bar_voltage_main_main_default
style_src_main_bar_voltage_main_main_default = lv.style_t()
style_src_main_bar_voltage_main_main_default.init()
style_src_main_bar_voltage_main_main_default.set_radius(10)
style_src_main_bar_voltage_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_voltage_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_voltage_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_bar_voltage_main_main_default.set_bg_opa(60)

# add style for src_main_bar_voltage
src_main_bar_voltage.add_style(style_src_main_bar_voltage_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_src_main_bar_voltage_main_indicator_default
style_src_main_bar_voltage_main_indicator_default = lv.style_t()
style_src_main_bar_voltage_main_indicator_default.init()
style_src_main_bar_voltage_main_indicator_default.set_radius(10)
style_src_main_bar_voltage_main_indicator_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_voltage_main_indicator_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_voltage_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_bar_voltage_main_indicator_default.set_bg_opa(255)

# add style for src_main_bar_voltage
src_main_bar_voltage.add_style(style_src_main_bar_voltage_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

src_main_bar_current = lv.bar(src_main)
src_main_bar_current.set_pos(int(6),int(24))
src_main_bar_current.set_size(121,8)
src_main_bar_current.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_bar_current.set_style_anim_time(1000, 0)
src_main_bar_current.set_mode(lv.bar.MODE.NORMAL)
src_main_bar_current.set_value(50, lv.ANIM.OFF)
# create style style_src_main_bar_current_main_main_default
style_src_main_bar_current_main_main_default = lv.style_t()
style_src_main_bar_current_main_main_default.init()
style_src_main_bar_current_main_main_default.set_radius(10)
style_src_main_bar_current_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_current_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_current_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_bar_current_main_main_default.set_bg_opa(60)

# add style for src_main_bar_current
src_main_bar_current.add_style(style_src_main_bar_current_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_src_main_bar_current_main_indicator_default
style_src_main_bar_current_main_indicator_default = lv.style_t()
style_src_main_bar_current_main_indicator_default.init()
style_src_main_bar_current_main_indicator_default.set_radius(10)
style_src_main_bar_current_main_indicator_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_current_main_indicator_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_bar_current_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_bar_current_main_indicator_default.set_bg_opa(255)

# add style for src_main_bar_current
src_main_bar_current.add_style(style_src_main_bar_current_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

src_main_meter_angle = lv.meter(src_main)
src_main_meter_angle.set_pos(int(42),int(67))
src_main_meter_angle.set_size(160,160)
src_main_meter_angle.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_meter_angle_scale_1 = src_main_meter_angle.add_scale()
src_main_meter_angle.set_scale_ticks(src_main_meter_angle_scale_1, 61, 3, 3,
    lv.color_make(0xff, 0x00, 0x00))
src_main_meter_angle.set_scale_range(src_main_meter_angle_scale_1, 0, 360, 360, 0)
src_main_meter_angle_scale_1_arc_0 = src_main_meter_angle.add_arc(src_main_meter_angle_scale_1, 14, lv.color_make(0x8a, 0x41, 0x0a), 5)
src_main_meter_angle.set_indicator_start_value(src_main_meter_angle_scale_1_arc_0, 10)
src_main_meter_angle.set_indicator_end_value(src_main_meter_angle_scale_1_arc_0, 20)
src_main_meter_angle_scale_2 = src_main_meter_angle.add_scale()
src_main_meter_angle.set_scale_ticks(src_main_meter_angle_scale_2, 12, 0, 0,
    lv.color_make(0xff, 0x00, 0x00))
src_main_meter_angle.set_scale_major_ticks(src_main_meter_angle_scale_2, 1, 5, 9,
	lv.color_make(0x00, 0x40, 0xff), 10)
src_main_meter_angle.set_scale_range(src_main_meter_angle_scale_2, 0, 330, 330, 0)
# create style style_src_main_meter_angle_main_main_default
style_src_main_meter_angle_main_main_default = lv.style_t()
style_src_main_meter_angle_main_main_default.init()
style_src_main_meter_angle_main_main_default.set_radius(200)
style_src_main_meter_angle_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_src_main_meter_angle_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_src_main_meter_angle_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_meter_angle_main_main_default.set_bg_opa(255)
style_src_main_meter_angle_main_main_default.set_shadow_width(5)
style_src_main_meter_angle_main_main_default.set_shadow_color(lv.color_make(0x19,0x0c,0xcf))
style_src_main_meter_angle_main_main_default.set_shadow_opa(158)
style_src_main_meter_angle_main_main_default.set_shadow_spread(4)
style_src_main_meter_angle_main_main_default.set_shadow_ofs_x(0)
style_src_main_meter_angle_main_main_default.set_shadow_ofs_y(0)
style_src_main_meter_angle_main_main_default.set_border_color(lv.color_make(0x22,0x86,0xd8))
style_src_main_meter_angle_main_main_default.set_border_width(0)
style_src_main_meter_angle_main_main_default.set_border_opa(255)

# add style for src_main_meter_angle
src_main_meter_angle.add_style(style_src_main_meter_angle_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_src_main_meter_angle_main_ticks_default
style_src_main_meter_angle_main_ticks_default = lv.style_t()
style_src_main_meter_angle_main_ticks_default.init()
style_src_main_meter_angle_main_ticks_default.set_text_color(lv.color_make(0xff,0x00,0x00))
try:
    style_src_main_meter_angle_main_ticks_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_meter_angle_main_ticks_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_meter_angle_main_ticks_default.set_text_font(lv.font_montserrat_16)

# add style for src_main_meter_angle
src_main_meter_angle.add_style(style_src_main_meter_angle_main_ticks_default, lv.PART.TICKS|lv.STATE.DEFAULT)

# create style style_src_main_meter_angle_main_ticks_focused
style_src_main_meter_angle_main_ticks_focused = lv.style_t()
style_src_main_meter_angle_main_ticks_focused.init()
style_src_main_meter_angle_main_ticks_focused.set_text_color(lv.color_make(0xff,0x00,0x00))
try:
    style_src_main_meter_angle_main_ticks_focused.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_meter_angle_main_ticks_focused.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_meter_angle_main_ticks_focused.set_text_font(lv.font_montserrat_16)

# add style for src_main_meter_angle
src_main_meter_angle.add_style(style_src_main_meter_angle_main_ticks_focused, lv.PART.TICKS|lv.STATE.FOCUSED)

src_main_meter_omega = lv.meter(src_main)
src_main_meter_omega.set_pos(int(265),int(67))
src_main_meter_omega.set_size(160,160)
src_main_meter_omega.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_meter_omega_scale_1 = src_main_meter_omega.add_scale()
src_main_meter_omega.set_scale_ticks(src_main_meter_omega_scale_1, 41, 2, 12,
    lv.color_make(0xaa, 0xc5, 0x26))
src_main_meter_omega.set_scale_major_ticks(src_main_meter_omega_scale_1, 8, 3, 16,
	lv.color_make(0x00, 0x04, 0xf5), 10)
src_main_meter_omega.set_scale_range(src_main_meter_omega_scale_1, 0, 900, 270, 135)
src_main_meter_omega_scale_1_arc_0 = src_main_meter_omega.add_arc(src_main_meter_omega_scale_1, 12, lv.color_make(0x4c, 0x00, 0xff), 0)
src_main_meter_omega.set_indicator_start_value(src_main_meter_omega_scale_1_arc_0, 0)
src_main_meter_omega.set_indicator_end_value(src_main_meter_omega_scale_1_arc_0, 360)
src_main_meter_omega_scale_1_arc_1 = src_main_meter_omega.add_arc(src_main_meter_omega_scale_1, 6, lv.color_make(0xff, 0x00, 0x00), 8)
src_main_meter_omega.set_indicator_start_value(src_main_meter_omega_scale_1_arc_1, 0)
src_main_meter_omega.set_indicator_end_value(src_main_meter_omega_scale_1_arc_1, 540)
src_main_meter_omega_scale_1_scaleLine_0 = src_main_meter_omega.add_scale_lines(src_main_meter_omega_scale_1,
    lv.color_make(0x00, 0xf0, 0x30),
    lv.color_make(0x00, 0xf0, 0x68),
    False, 0)
src_main_meter_omega.set_indicator_start_value(src_main_meter_omega_scale_1_scaleLine_0, 0)
src_main_meter_omega.set_indicator_end_value(src_main_meter_omega_scale_1_scaleLine_0, 180)
src_main_meter_omega_scale_1_scaleLine_1 = src_main_meter_omega.add_scale_lines(src_main_meter_omega_scale_1,
    lv.color_make(0xff, 0x00, 0x19),
    lv.color_make(0xfe, 0x06, 0x06),
    False, 0)
src_main_meter_omega.set_indicator_start_value(src_main_meter_omega_scale_1_scaleLine_1, 720)
src_main_meter_omega.set_indicator_end_value(src_main_meter_omega_scale_1_scaleLine_1, 900)
# create style style_src_main_meter_omega_main_main_default
style_src_main_meter_omega_main_main_default = lv.style_t()
style_src_main_meter_omega_main_main_default.init()
style_src_main_meter_omega_main_main_default.set_radius(200)
style_src_main_meter_omega_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_src_main_meter_omega_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_src_main_meter_omega_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_meter_omega_main_main_default.set_bg_opa(255)
style_src_main_meter_omega_main_main_default.set_shadow_width(4)
style_src_main_meter_omega_main_main_default.set_shadow_color(lv.color_make(0x71,0x9d,0xc1))
style_src_main_meter_omega_main_main_default.set_shadow_opa(255)
style_src_main_meter_omega_main_main_default.set_shadow_spread(5)
style_src_main_meter_omega_main_main_default.set_shadow_ofs_x(0)
style_src_main_meter_omega_main_main_default.set_shadow_ofs_y(0)
style_src_main_meter_omega_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_meter_omega_main_main_default.set_border_width(0)
style_src_main_meter_omega_main_main_default.set_border_opa(255)

# add style for src_main_meter_omega
src_main_meter_omega.add_style(style_src_main_meter_omega_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_src_main_meter_omega_main_ticks_default
style_src_main_meter_omega_main_ticks_default = lv.style_t()
style_src_main_meter_omega_main_ticks_default.init()
style_src_main_meter_omega_main_ticks_default.set_text_color(lv.color_make(0xff,0x00,0x00))
try:
    style_src_main_meter_omega_main_ticks_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_meter_omega_main_ticks_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_meter_omega_main_ticks_default.set_text_font(lv.font_montserrat_16)

# add style for src_main_meter_omega
src_main_meter_omega.add_style(style_src_main_meter_omega_main_ticks_default, lv.PART.TICKS|lv.STATE.DEFAULT)

src_main_label_angle = lv.label(src_main)
src_main_label_angle.set_pos(int(72),int(162))
src_main_label_angle.set_size(100,16)
src_main_label_angle.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_label_angle.set_text("180/300")
src_main_label_angle.set_long_mode(lv.label.LONG.WRAP)
# create style style_src_main_label_angle_main_main_default
style_src_main_label_angle_main_main_default = lv.style_t()
style_src_main_label_angle_main_main_default.init()
style_src_main_label_angle_main_main_default.set_radius(0)
style_src_main_label_angle_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_label_angle_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_label_angle_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_label_angle_main_main_default.set_bg_opa(0)
style_src_main_label_angle_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_src_main_label_angle_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_label_angle_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_label_angle_main_main_default.set_text_font(lv.font_montserrat_16)
style_src_main_label_angle_main_main_default.set_text_letter_space(2)
style_src_main_label_angle_main_main_default.set_text_line_space(0)
style_src_main_label_angle_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_src_main_label_angle_main_main_default.set_pad_left(0)
style_src_main_label_angle_main_main_default.set_pad_right(0)
style_src_main_label_angle_main_main_default.set_pad_top(0)
style_src_main_label_angle_main_main_default.set_pad_bottom(0)

# add style for src_main_label_angle
src_main_label_angle.add_style(style_src_main_label_angle_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

src_main_label_omega = lv.label(src_main)
src_main_label_omega.set_pos(int(295),int(199))
src_main_label_omega.set_size(100,20)
src_main_label_omega.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
src_main_label_omega.set_text("120/120")
src_main_label_omega.set_long_mode(lv.label.LONG.WRAP)
# create style style_src_main_label_omega_main_main_default
style_src_main_label_omega_main_main_default = lv.style_t()
style_src_main_label_omega_main_main_default.init()
style_src_main_label_omega_main_main_default.set_radius(0)
style_src_main_label_omega_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_label_omega_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_src_main_label_omega_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_src_main_label_omega_main_main_default.set_bg_opa(0)
style_src_main_label_omega_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_src_main_label_omega_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_src_main_label_omega_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_src_main_label_omega_main_main_default.set_text_font(lv.font_montserrat_16)
style_src_main_label_omega_main_main_default.set_text_letter_space(2)
style_src_main_label_omega_main_main_default.set_text_line_space(0)
style_src_main_label_omega_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_src_main_label_omega_main_main_default.set_pad_left(0)
style_src_main_label_omega_main_main_default.set_pad_right(0)
style_src_main_label_omega_main_main_default.set_pad_top(0)
style_src_main_label_omega_main_main_default.set_pad_bottom(0)

# add style for src_main_label_omega
src_main_label_omega.add_style(style_src_main_label_omega_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)




# content from custom.py

# Load the default screen
lv.scr_load(src_main)

while SDL.check():
    time.sleep_ms(5)
