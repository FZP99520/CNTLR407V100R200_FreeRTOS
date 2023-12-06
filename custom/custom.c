/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

#include "led.h"
#include "adc.h"
#include "ANO_DT.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
lv_obj_t * slider_label;
lv_obj_t * led1_label;
lv_obj_t * dclock;
lv_obj_t * bar_l_y;
lv_obj_t * bar_l_x;
lv_obj_t * bar_r_y;
lv_obj_t * bar_r_x;
lv_obj_t * led_sw;
lv_obj_t * checkbox;
lv_obj_t * dropdown;
lv_obj_t * roller;


extern uint16_t u16LED1_PWM_Duty;
extern lv_indev_t * indev_keypad;
extern lv_indev_t * indev_encoder;
extern lv_ui guider_ui;
/**
 * Create a demo application
 */

 void custom_timer_cb(lv_timer_t *timer)
 {
    float *pf32AdcOutput;
    s16 as16Value[4];
    static s16 as16Value_pre[4];
    s16 s16Angle = 0;
    s16 s16TargetOmega = 0;
    s16 s16RealOmega = 0;

    
    //lv_label_set_text_fmt(led1_label, "P:%5d", u16LED1_PWM_Duty);

    pf32AdcOutput = ADC_Get_Output();
    as16Value[1] = pf32AdcOutput[0]*100/1.65f;
    as16Value[0] = -pf32AdcOutput[1]*100/1.65f;
    as16Value[2] = pf32AdcOutput[2]*100/1.65f;
    as16Value[3] = pf32AdcOutput[3]*100/1.65f;

    s16Angle = as16Value[1]*3.6f;
    s16TargetOmega = as16Value[2]*3.6f;
    s16RealOmega = as16Value[3]*3.6f;
 
 }

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    lv_group_t * g = lv_group_create();

    lv_group_set_default(g);

    lv_indev_set_group(indev_keypad, g);
    lv_indev_set_group(indev_encoder, g);

    
    //lv_timer_create(custom_timer_cb, 100, NULL);
}

void led1_pwm_cb(lv_timer_t *timer)
{
    float *pf32AdcOutput;
    s16 as16Value[4];
    static s16 as16Value_pre[4];
    //lv_label_set_text_fmt(led1_label, "P:%5d", u16LED1_PWM_Duty);

    pf32AdcOutput = ADC_Get_Output();
    as16Value[1] = pf32AdcOutput[0]*100/1.65f;
    as16Value[0] = -pf32AdcOutput[1]*100/1.65f;
    as16Value[2] = pf32AdcOutput[2]*100/1.65f;
    as16Value[3] = pf32AdcOutput[3]*100/1.65f;

    //l_y,l_x,r_y,r_x
    if(as16Value[0] != as16Value_pre[0])
    {
        lv_bar_set_value(bar_l_y, as16Value[0], LV_ANIM_OFF);
    }

    if(as16Value[1] != as16Value_pre[1])
    {
        lv_bar_set_value(bar_l_x, as16Value[1], LV_ANIM_OFF);
    }

    if(as16Value[2] != as16Value_pre[2])
    {
        lv_bar_set_value(bar_r_y, as16Value[2], LV_ANIM_OFF);
    }

    if(as16Value[3] != as16Value_pre[3])
    {
        lv_bar_set_value(bar_r_x, as16Value[3], LV_ANIM_OFF);
    }

    as16Value_pre[0] = as16Value[0];
    as16Value_pre[1] = as16Value[1];
    as16Value_pre[2] = as16Value[2];
    as16Value_pre[3] = as16Value[3];
    
}

void btn1_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);        // 获取触发事件的部件(对象)
    lv_event_code_t code = lv_event_get_code(e);    // 获取当前部件(对象)触发的事件代码

    switch(code){
        case LV_EVENT_VALUE_CHANGED:
        {
#if 1
            if(lv_obj_has_state(obj, LV_STATE_CHECKED))
            {
                LED_Send_Event_To_LED2(E_LED_EVENT_ON, 2, 50, 200);
            }
            else
            {
                LED_Send_Event_To_LED2(E_LED_EVENT_OFF, 2, 50, 200);;
            }
#else
            if(lv_obj_get_state(obj) & LV_STATE_CHECKED)
            {
                FR_OS_EventSetBits(hLed2Event, E_LED_EVENT_ON);
            }
            else
            {
                FR_OS_EventSetBits(hLed2Event, E_LED_EVENT_OFF);
            }
#endif
            //printf("LV_EVENT_VALUE_CHANGED\n");
            break;

        
}
        default:
            //printf("NONE\n");
            break;
    }
}

void led_switch_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);        // 获取触发事件的部件(对象)
    lv_event_code_t code = lv_event_get_code(e);    // 获取当前部件(对象)触发的事件代码

    LV_LOG_USER("code=%d\n", code);

    switch(code)
    {
        case LV_EVENT_VALUE_CHANGED:
        {
#if 1
            if(lv_obj_has_state(obj, LV_STATE_CHECKED))
            {
                LV_LOG_USER("switch on\n");
                LED_Send_Event_To_LED2(E_LED_EVENT_ON, 2, 50, 200);
            }
            else
            {
                LV_LOG_USER("switch off\n");
                LED_Send_Event_To_LED2(E_LED_EVENT_OFF, 2, 50, 200);;
            }
#else
            if(lv_obj_get_state(obj) & LV_STATE_CHECKED)
            {
                FR_OS_EventSetBits(hLed2Event, E_LED_EVENT_ON);
            }
            else
            {
                FR_OS_EventSetBits(hLed2Event, E_LED_EVENT_OFF);
            }
#endif
            //printf("LV_EVENT_VALUE_CHANGED\n");
            break;

        
        }
        default:
            //printf("NONE\n");
            break;
    }
}

void ano_dt_checkbox_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);        // 获取触发事件的部件(对象)
    lv_event_code_t code = lv_event_get_code(e);    // 获取当前部件(对象)触发的事件代码

    //LV_LOG_USER("code=%d\n", code);

    switch(code)
    {
        case LV_EVENT_VALUE_CHANGED:
        {
#if 1
            if(lv_obj_has_state(obj, LV_STATE_CHECKED))
            {
                //LV_LOG_USER("switch on\n");
                //LED_Send_Event_To_LED2(E_LED_EVENT_ON, 2, 50, 200);
                ANO_DT_Slaver_Send_Enable(TRUE);
            }
            else
            {
                ///LV_LOG_USER("switch off\n");
                //LED_Send_Event_To_LED2(E_LED_EVENT_OFF, 2, 50, 200);
                ANO_DT_Slaver_Send_Enable(FALSE);
            }
#else
            if(lv_obj_get_state(obj) & LV_STATE_CHECKED)
            {
                FR_OS_EventSetBits(hLed2Event, E_LED_EVENT_ON);
            }
            else
            {
                FR_OS_EventSetBits(hLed2Event, E_LED_EVENT_OFF);
            }
#endif
            //printf("LV_EVENT_VALUE_CHANGED\n");
            break;

        
        }
        default:
            //printf("NONE\n");
            break;
    }
}


void slider_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);        // 获取触发事件的部件(对象)
    lv_event_code_t code = lv_event_get_code(e);    // 获取当前部件(对象)触发的事件代码

    int slider_value = lv_slider_get_value(obj);
    switch(code){
        case LV_EVENT_VALUE_CHANGED:
            lv_label_set_text_fmt(slider_label, "%d",slider_value);
            //xTaskNotify(hLed2Task, slider_value*10, eSetValueWithOverwrite);
            LED_Send_Event_To_LED2(E_LED_EVENT_FLASH, 0xFF, slider_value&0xFF, 200);
            LV_LOG_USER("silder value change to %d\n", slider_value);
            break;
        default:
            //printf("NONE\n");
            break;
    }
}

void digital_clock_timer(lv_timer_t *timer)
{
    static int dclock_hour_value = 0;
    static int dclock_min_value = 0;
    static int dclock_sec_value = 0;
    static char dclock_meridiem[] = "AM";
    #if 0
    clock_count_12(&dclock_hour_value, &dclock_min_value, &dclock_sec_value, dclock_meridiem);
    if (lv_obj_is_valid(dclock))
    {
        lv_dclock_set_text_fmt(dclock, "%02d:%02d:%02d %s", dclock_hour_value, dclock_min_value, dclock_sec_value, dclock_meridiem);
    }
    #else
    clock_count_24(&dclock_hour_value, &dclock_min_value, &dclock_sec_value);
    if (lv_obj_is_valid(dclock))
    {
        lv_dclock_set_text_fmt(dclock, "%02d:%02d:%02d", dclock_hour_value, dclock_min_value, dclock_sec_value);
    }
    #endif
}


#if 1
void Custom_UI_Demo(void)
{
    #if 0
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj, LV_PCT(40), LV_PCT(20));
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * label = lv_label_create(obj);
    lv_obj_set_size(label, 100, 30);
    lv_obj_set_style_text_color(label, lv_color_black(), 0);
    lv_label_set_recolor(label, true);
    lv_label_set_text_fmt(label, LV_SYMBOL_HOME"Hello, LVGL!!! #00ff00 Version:%d.%d.%d# Author:Zipeng.Feng", \
        lv_version_major(), lv_version_minor(), lv_version_patch());
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    #endif
    
    // ?????,?????????????????????(??)????,???????????
    // ????????????,????????????????????(??)????? lv_group_add_obj()
    lv_group_t * g = lv_group_create();

    // ?????????????
    // ?????????(??),?????????????????????,?????
    lv_group_set_default(g);

    // ?????????(???????????????)
    
    lv_indev_set_group(indev_keypad, g);     // ??
    lv_indev_set_group(indev_encoder, g);      // ??????(???)

    static lv_style_t style_btn;
 
    lv_style_init( &style_btn );
    lv_style_set_radius( &style_btn, 0 );
    lv_style_set_bg_opa( &style_btn, LV_OPA_COVER );
    lv_style_set_bg_color( &style_btn, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_bg_grad_color( &style_btn, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_dir( &style_btn, LV_GRAD_DIR_HOR);
    lv_style_set_bg_main_stop( &style_btn, 0);
    lv_style_set_bg_grad_stop( &style_btn, 255);
    lv_style_set_pad_all(&style_btn, 2);

    /* ????btn??(??) */
    lv_obj_t * btn1 = lv_btn_create(lv_scr_act());       // ????btn??(??),????????????
    lv_obj_set_size(btn1, 50, 25);
    lv_obj_align(btn1, LV_ALIGN_TOP_MID, -28, 0);
    //lv_obj_set_style_bg_color(btn1, lv_color_hex(0x1e1e1e), LV_PART_MAIN|LV_STATE_PRESSED);
    //lv_obj_add_event_cb(btn1, btn1_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_flag(btn1, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_style(btn1, &style_btn, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn1, 5, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t * btn2 = lv_btn_create(lv_scr_act());       // ????btn??(??),????????????
    lv_obj_set_size(btn2, 50, 25);
    lv_obj_align(btn2, LV_ALIGN_TOP_MID, 28, 0);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_style_bg_color(btn2, lv_color_hex(0x1e1e1e), LV_PART_MAIN|LV_STATE_PRESSED);

    lv_obj_t * btn3 = lv_btn_create(lv_scr_act());       // ????btn??(??),????????????
    lv_obj_set_size(btn3, 50, 25);
    lv_obj_align_to(btn3, btn1, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_add_flag(btn3, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_style_bg_color(btn3, lv_color_hex(0x1e1e1e), LV_PART_MAIN|LV_STATE_PRESSED);

    lv_obj_t * btn4 = lv_btn_create(lv_scr_act());       // ????btn??(??),????????????
    lv_obj_set_size(btn4, 50, 25);
    lv_obj_align_to(btn4, btn2, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_add_flag(btn4, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_style_bg_color(btn4, lv_color_hex(0x1e1e1e), LV_PART_MAIN|LV_STATE_PRESSED);

    lv_obj_t * slider = lv_slider_create(lv_scr_act());
    lv_obj_set_size(slider, 200, 10);
    //lv_obj_align_to(slider, btn3, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, -90);
    lv_obj_add_event_cb(slider, slider_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_slider_set_value(slider, 50, LV_ANIM_OFF);
    //lv_obj_set_style_pad_all(slider, 2, LV_PART_MAIN);

    slider_label = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(slider_label, "%d", 0);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_label_set_text_fmt(slider_label, "%d", 50);

//bar start
    static lv_style_t style_bar_main;
    lv_style_init( &style_bar_main);
    lv_style_set_radius( &style_bar_main, 3);
    lv_style_set_bg_opa( &style_bar_main, LV_OPA_30);
    lv_style_set_bg_color( &style_bar_main, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_pad_top(&style_bar_main, 1);
    lv_style_set_pad_bottom(&style_bar_main, 1);

    static lv_style_t style_bar_indicator;
    lv_style_init( &style_bar_indicator );
    lv_style_set_radius( &style_bar_indicator, 3);
    lv_style_set_bg_opa( &style_bar_indicator, LV_OPA_COVER );
    lv_style_set_bg_color( &style_bar_indicator, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_bg_grad_color( &style_bar_indicator, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_dir( &style_bar_indicator, LV_GRAD_DIR_HOR);
    lv_style_set_bg_main_stop( &style_bar_indicator, 0);
    lv_style_set_bg_grad_stop( &style_bar_indicator, 255);

    bar_l_y = lv_bar_create(lv_scr_act());
    //lv_obj_align_to(bar, led1_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    
    lv_obj_set_pos(bar_l_y, 0, 30);
    lv_obj_set_size(bar_l_y, 100, 10);
    lv_bar_set_mode(bar_l_y, LV_BAR_MODE_SYMMETRICAL);
    lv_bar_set_range(bar_l_y, -100, 100);
    lv_bar_set_value(bar_l_y, 0, LV_ANIM_ON);
    lv_bar_set_start_value(bar_l_y, 0, LV_ANIM_ON);
    lv_obj_add_style(bar_l_y, &style_bar_main, LV_PART_MAIN);
    lv_obj_add_style(bar_l_y, &style_bar_indicator, LV_PART_INDICATOR);

    bar_l_x = lv_bar_create(lv_scr_act());
    lv_obj_set_size(bar_l_x, 100, 10);
    lv_obj_align_to(bar_l_x, bar_l_y, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 2);
    lv_bar_set_mode(bar_l_x, LV_BAR_MODE_SYMMETRICAL);
    lv_bar_set_range(bar_l_x, -100, 100);
    lv_bar_set_value(bar_l_x, 0, LV_ANIM_ON);
    lv_bar_set_start_value(bar_l_x, 0, LV_ANIM_ON);
    lv_obj_add_style(bar_l_x, &style_bar_main, LV_PART_MAIN);
    lv_obj_add_style(bar_l_x, &style_bar_indicator, LV_PART_INDICATOR);

    bar_r_y = lv_bar_create(lv_scr_act());
    lv_obj_set_size(bar_r_y, 100, 10);
    lv_obj_align_to(bar_r_y, bar_l_x, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 2);
    lv_bar_set_mode(bar_r_y, LV_BAR_MODE_SYMMETRICAL);
    lv_bar_set_range(bar_r_y, -100, 100);
    lv_bar_set_value(bar_r_y, 0, LV_ANIM_ON);
    lv_bar_set_start_value(bar_r_y, 0, LV_ANIM_ON);
    lv_obj_add_style(bar_r_y, &style_bar_main, LV_PART_MAIN);
    lv_obj_add_style(bar_r_y, &style_bar_indicator, LV_PART_INDICATOR);

    bar_r_x = lv_bar_create(lv_scr_act());
    lv_obj_set_size(bar_r_x, 100, 10);
    lv_obj_align_to(bar_r_x, bar_r_y, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 2);
    lv_bar_set_mode(bar_r_x, LV_BAR_MODE_SYMMETRICAL);
    lv_bar_set_range(bar_r_x, -100, 100);
    lv_bar_set_value(bar_r_x, 0, LV_ANIM_ON);
    lv_bar_set_start_value(bar_r_x, 0, LV_ANIM_ON);
    lv_obj_add_style(bar_r_x, &style_btn, LV_PART_INDICATOR);
    lv_obj_add_style(bar_r_x, &style_bar_main, LV_PART_MAIN);
    lv_obj_add_style(bar_r_x, &style_bar_indicator, LV_PART_INDICATOR);
//bar end
    

    // ???(??)????,????????,??????
    //lv_group_add_obj(g, btn1);
    //lv_group_add_obj(g, btn2);
    //lv_group_add_obj(g, btn3);
    //lv_group_add_obj(g, btn4);
    //lv_group_add_obj(g, slider);

//dclock create start
    unsigned char clock_1_timer_enabled = 0;
    dclock = lv_dclock_create(lv_scr_act(),"--:--:--");
    lv_obj_set_style_text_align(dclock, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(dclock, 0, 0);
    //lv_obj_set_size(dclock, 118, 42);

    //create timer
    if (!clock_1_timer_enabled) {
        lv_timer_create(digital_clock_timer, 1000, NULL);
        clock_1_timer_enabled = true;
    }
#if 1
    static lv_style_t style_dclock;
    if (style_dclock.prop_cnt > 1)
        lv_style_reset(&style_dclock);
    else
        lv_style_init(&style_dclock);
    lv_style_set_radius(&style_dclock, 0);
    lv_style_set_bg_color(&style_dclock, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_color(&style_dclock, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&style_dclock, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&style_dclock, 174);
    lv_style_set_text_color(&style_dclock, lv_color_make(0x10, 0x10, 0x0f));
    //lv_style_set_text_font(&style_dclock, &lv_font_simsun_12);
    lv_style_set_text_letter_space(&style_dclock, 0);
    lv_style_set_pad_left(&style_dclock, 0);
    lv_style_set_pad_right(&style_dclock, 0);
    lv_style_set_pad_top(&style_dclock, 0);
    lv_style_set_pad_bottom(&style_dclock, 0);
    lv_obj_add_style(dclock, &style_dclock, LV_PART_MAIN|LV_STATE_DEFAULT);
#endif
//dclock create end

    led1_label = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(led1_label, "%d", 0);
    lv_obj_align_to(led1_label, dclock, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_timer_create(led1_pwm_cb, 20, NULL);

//create switch start
    led_sw = lv_switch_create(lv_scr_act());
    lv_obj_set_size(led_sw, 50, 25);
    lv_obj_align(led_sw, LV_ALIGN_LEFT_MID, 0, -60);
    lv_obj_add_event_cb(led_sw, led_switch_cb, LV_EVENT_VALUE_CHANGED, NULL);
//create switch end

    checkbox = lv_checkbox_create(lv_scr_act());
    //lv_obj_set_size(checkbox, 60, 25);
    lv_obj_align_to(checkbox, led_sw,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 8);
    lv_obj_add_event_cb(checkbox, ano_dt_checkbox_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_checkbox_set_text(checkbox, "ANO_DT EN");

    dropdown = lv_dropdown_create(lv_scr_act());
    lv_obj_align_to(dropdown, checkbox,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 8);
    lv_dropdown_set_options(dropdown, "One\nTwo\nThree\n");

    roller = lv_roller_create(lv_scr_act());
    lv_obj_align_to(roller, dropdown,LV_ALIGN_OUT_RIGHT_MID, 0, 8);
    lv_roller_set_options(roller, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10", LV_ROLLER_MODE_NORMAL);

    //lv_obj_t * arc = lv_arc_create(lv_scr_act());
    //lv_obj_set_size(arc, 60, 60);
    //lv_obj_remove_style(arc, NULL, LV_PART_INDICATOR);
    //lv_obj_center(arc);

    //lv_group_add_obj(g, arc);
#if 1
    lv_obj_t * meter = lv_meter_create(lv_scr_act());
    lv_obj_set_size(meter, 240, 240);
    lv_meter_scale_t * meter_scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, meter_scale, 61, 8, 3, lv_color_make(0xff, 0x00, 0x00));
    lv_meter_set_scale_major_ticks(meter, meter_scale, 5, 4, 9, lv_color_make(0x00, 0xff, 0x00), 12);
    lv_meter_set_scale_range(meter, meter_scale, 0, 360, 360, 0);

    lv_meter_indicator_t * indic1 = lv_meter_add_arc(meter, meter_scale, 10, lv_palette_main(LV_PALETTE_RED), -20);
    lv_meter_set_indicator_start_value(meter, indic1, 0);
    lv_meter_set_indicator_value(meter, indic1, 90);
    lv_meter_set_indicator_end_value(meter, indic1, 270);

    lv_meter_indicator_t * indic = lv_meter_add_scale_lines(meter, meter_scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_BLUE), false, 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 270);

    //indic = lv_meter_add_scale_lines(meter, meter_scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
    //lv_meter_set_indicator_start_value(meter, indic, 80);
    //lv_meter_set_indicator_end_value(meter, indic, 100);
    //lv_obj_center(meter);
    
#endif


    //lv_obj_set_style_arc_opa(struct _lv_obj_t * obj, lv_opa_t value, lv_style_selector_t selector)

}

void Customer_Top_Layer(void)
{
    lv_obj_t * label = lv_label_create(lv_layer_top());
    lv_label_set_recolor(label, TRUE);
    lv_obj_set_style_text_color(label, lv_color_hex(0x7f7f7f), LV_PART_MAIN);
    lv_label_set_text_fmt(label,  LV_SYMBOL_POWER "#0000ff %s #", "Hello");
    lv_obj_align(label, LV_ALIGN_TOP_RIGHT, 0, 0);
}

#else
static lv_obj_t * meter;

static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(meter, indic, u16LED1_PWM_Duty/10);
}

static void set_temp(void * bar, int32_t temp)
{
    lv_bar_set_value(bar, temp, LV_ANIM_ON);
}


void Custom_UI_Demo(void)
{
    static lv_style_t style_indic;

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);

    lv_obj_t * bar = lv_bar_create(lv_scr_act());
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
    //lv_obj_set_size(bar, 20, 200);
    lv_obj_center(bar);
    lv_bar_set_range(bar, -20, 40);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_temp);
    lv_anim_set_time(&a, 3000);
    lv_anim_set_playback_time(&a, 3000);
    lv_anim_set_var(&a, bar);
    lv_anim_set_values(&a, -20, 40);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}
#endif


