#include "main.h"
#include "adc.h"
#include "mpu9250.h"
#include "ili9488.h"
#include "key.h"
#include "pwm.h"
#include "display.h"
#include "log.h"
#include "input_ctrl.h"
#include "systick.h"
#include "flash.h"
#include "arm_math.h"
#include "ANO_DT.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "FR_OS.h"

#include <stdlib.h>

//for lvgl gui
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demo_keypad_encoder.h"
#include "lv_log.h"


#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

/****************Dynamic Task*************/

TaskHandle_t hStartTask;
TaskHandle_t hLcdTask;
TaskHandle_t hDisplayTask;
MutexHandle_t hDispMutex;

void Start_Task(void *pvParameters);
void Disp_Task(void *pvParameters);
void Display_Task(void * pvParameters);

lv_ui guider_ui;

int main()
{
    unsigned int i=0;
    u8 delay=0;
    SystemClock_Init();//设置时钟
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//中断分组

#if (USART1_ENABLE == 1)
    USART1_Init(USART1_BAUDRATE);
#endif
#if (USART2_ENABLE == 1)
    USART2_Init(USART2_BAUDRATE);
#endif
#if (USART3_ENABLE == 1)
    USART3_Init(USART3_BAUDRATE);
#endif

    DEBUG_PRINT("Power On\n");
    DEBUG_PRINT("USART: %dbps\n", USART1_BAUDRATE);
    Led_Init();
    Beep_Init();
    KEY_Init();
    Adc_Init();
    TIM2_Int_Init();//for ADC1,period=20ms
    TIM5_PWM_Init(LED_PWM_PERIOD); //for LED1 used
    LCD_Init();
    //I2C1_SW_Init();
    //DAC1_Init();

    //OLED_Init();
    //FLASH_SPI_Init(); //for adc or dac
    //SPI1_Init();
    //TIM3_Int_Init();//T=5ms Only Use TIM3 
    //TIM4_Int_Init();
    lv_init();
    lv_port_disp_init();  // lvgl显示接口初始化,放在lv_init()的后面
    lv_port_indev_init(); // lvgl输入接口初始化,放在lv_init()的后面
    lv_log_register_print_cb(debug);

    //lv_demo_keypad_encoder();
    custom_init(&guider_ui);
    setup_ui(&guider_ui);
    events_init(&guider_ui);

    SysTick_Init(168);

    TaskCreateParams_t stTaskCreateParams;
    memset(&stTaskCreateParams,0,sizeof(TaskCreateParams_t));
    stTaskCreateParams.TaskCode = Start_Task;
    stTaskCreateParams.pcName = "start_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 1;
    FR_OS_TaskCreate(&hStartTask, stTaskCreateParams);

    vTaskStartScheduler();
    while(pdTRUE);
}


void Start_Task(void * pvParameters)
{
    taskENTER_CRITICAL();
    /*Create Queue...*/
#if (USART1_ENABLE == 1)
    hUSART1_TX_Queue    = FR_OS_QueueCreate(3, sizeof(ST_USART_DATA));
    hUSART1_RX_Queue    = FR_OS_QueueCreate(3, sizeof(ST_USART_DATA));
    hUSART1_TxSemBinary = FR_OS_SemBinaryCreate();
    FR_OS_SemBinaryGive(hUSART1_TxSemBinary);
#endif
    
#if (USART2_ENABLE == 1)
    hUSART2_TX_Queue    = FR_OS_QueueCreate(3, sizeof(ST_USART_DATA));
    hUSART2_RX_Queue    = FR_OS_QueueCreate(3, sizeof(ST_USART_DATA));
    hUSART2_TxSemBinary = FR_OS_SemBinaryCreate();
    FR_OS_SemBinaryGive(hUSART2_TxSemBinary);
#endif
    
#if (USART3_ENABLE == 1)
    hUSART3_TX_Queue    = FR_OS_QueueCreate(3, sizeof(ST_USART_DATA));
    hUSART3_RX_Queue    = FR_OS_QueueCreate(3, sizeof(ST_USART_DATA));
    hUSART3_TxSemBinary = FR_OS_SemBinaryCreate();
    FR_OS_SemBinaryGive(hUSART3_TxSemBinary);
#endif


    hI2C1_Queue         = FR_OS_QueueCreate(3, sizeof(ST_I2C_Params_t));
    /*Create Semaphore */
    hI2C1_Mutex      = FR_OS_MutexCreate();
    //hAdcConv_Queue = FR_OS_QueueCreate(1, sizeof(ST_ADC_Conv_t));
    
    //Led2SemMutex_Handle = xSemaphoreCreateMutex();
    hDispMutex = FR_OS_MutexCreate();

    /*Create Event*/
    hKeyEvent  = FR_OS_EventCreate();
    hLed2Event = FR_OS_EventCreate();
    hBeepEvent = FR_OS_EventCreate();

    /*Create Task*/
    TaskCreateParams_t stTaskCreateParams;
    memset(&stTaskCreateParams,0,sizeof(TaskCreateParams_t));

    stTaskCreateParams.TaskCode = Led1_Task;
    stTaskCreateParams.pcName = "led1_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hLed1Task, stTaskCreateParams);

    stTaskCreateParams.TaskCode = Led2_Task;
    stTaskCreateParams.pcName = "led2_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 2;
    FR_OS_TaskCreate(&hLed2Task, stTaskCreateParams);

    stTaskCreateParams.TaskCode = Key_Task;
    stTaskCreateParams.pcName = "key_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hKeyTask, stTaskCreateParams);

    stTaskCreateParams.TaskCode = Disp_Task;
    stTaskCreateParams.pcName = "lcd_task";
    stTaskCreateParams.usStackDepth = 512; //size should be big enough
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 3;
    FR_OS_TaskCreate(&hLcdTask, stTaskCreateParams);
    
    stTaskCreateParams.TaskCode = BEEP_Task;
    stTaskCreateParams.pcName = "beep_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 3;
    FR_OS_TaskCreate(&hBeepTask, stTaskCreateParams);

#if (USART1_ENABLE == 1)
    stTaskCreateParams.TaskCode = USART1_Send_Data_Task;
    stTaskCreateParams.pcName = "usart1_send_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hUSART1_TX_Task, stTaskCreateParams);

    stTaskCreateParams.TaskCode = USART1_Receive_Data_Task;
    stTaskCreateParams.pcName = "usart1_receive_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hUSART1_RX_Task, stTaskCreateParams);
#endif

#if (USART2_ENABLE == 1)
    stTaskCreateParams.TaskCode = USART2_Send_Data_Task;
    stTaskCreateParams.pcName = "usart2_send_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hUSART2_TX_Task, stTaskCreateParams);

    stTaskCreateParams.TaskCode = USART2_Receive_Data_Task;
    stTaskCreateParams.pcName = "usart2_receive_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hUSART2_RX_Task, stTaskCreateParams);
#endif

#if (USART3_ENABLE == 1)
    stTaskCreateParams.TaskCode = USART3_Send_Data_Task;
    stTaskCreateParams.pcName = "usart3_send_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hUSART3_TX_Task, stTaskCreateParams);

    stTaskCreateParams.TaskCode = USART3_Receive_Data_Task;
    stTaskCreateParams.pcName = "usart3_receive_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hUSART3_RX_Task, stTaskCreateParams);
#endif

    stTaskCreateParams.TaskCode = Adc_Acquire_Task;
    stTaskCreateParams.pcName = "AdcAcquire_task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hAdcAcquireTask, stTaskCreateParams);

    stTaskCreateParams.TaskCode = ANO_DT_Start_Task;
    stTaskCreateParams.pcName = "ANO_DT_Start_Task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hAnoDtStartTask, stTaskCreateParams);

    stTaskCreateParams.TaskCode = Display_Task;
    stTaskCreateParams.pcName = "Display_Task";
    stTaskCreateParams.usStackDepth = 128;
    stTaskCreateParams.pvParameters = NULL;
    stTaskCreateParams.uxPriority = 4;
    FR_OS_TaskCreate(&hDisplayTask, stTaskCreateParams);

//    stTaskCreateParams.TaskCode = I2C1_DataHandle_Task;
//    stTaskCreateParams.pcName = "i2c1_task";
//    stTaskCreateParams.usStackDepth = 128;
//    stTaskCreateParams.pvParameters = NULL;
//    stTaskCreateParams.uxPriority = 4;
//    FR_OS_TaskCreate(&hI2C1_Task, stTaskCreateParams);

    vTaskDelete(hStartTask);
    taskEXIT_CRITICAL();
}

void Disp_Task(void * pvParameters)
{
    u32 u32Cnt = 0;
    LCD_Clear();
    BaseType_t xRet = pdFAIL;

    FR_OS_MUTEX_LOCK(hDispMutex);
    //Custom_UI_Demo();
    //Customer_Top_Layer();
    //setup_scr_src_main(&guider_ui);
    FR_OS_MUTEX_UNLOCK(hDispMutex);
    
    while(pdTRUE)
    {
        FR_OS_MUTEX_LOCK(hDispMutex);
        lv_task_handler();
        FR_OS_MUTEX_UNLOCK(hDispMutex);
        FR_OS_DelayMs(1);
    }
}

void Display_Task(void * pvParameters)
{
    float *pf32AdcOutput;
    s16 as16Value[4];
    static s16 as16Value_pre[4];
    s16 s16Angle = 0;
    s16 s16TargetOmega = 0;
    s16 s16RealOmega = 0;

    //lv_label_set_text_fmt(led1_label, "P:%5d", u16LED1_PWM_Duty);

    while(pdTRUE)
    {
        pf32AdcOutput = ADC_Get_Output();
        as16Value[1] = pf32AdcOutput[0]*100/1.65f;
        as16Value[0] = -pf32AdcOutput[1]*100/1.65f;
        as16Value[2] = pf32AdcOutput[2]*100/1.65f;
        as16Value[3] = pf32AdcOutput[3]*100/1.65f;

        s16Angle = as16Value[1]*3.6f;
        s16TargetOmega = as16Value[2]*3.6f;
        s16RealOmega = as16Value[3]*3.6f;

        FR_OS_MUTEX_LOCK(hDispMutex);
        lv_meter_set_indicator_start_value(guider_ui.src_main_meter_angle, guider_ui.src_main_meter_angle_scale_1_arc_0, s16Angle - 10);
        lv_meter_set_indicator_end_value(guider_ui.src_main_meter_angle, guider_ui.src_main_meter_angle_scale_1_arc_0, s16Angle);
        FR_OS_MUTEX_UNLOCK(hDispMutex);
        FR_OS_DelayMs(20);
//        
//        FR_OS_MUTEX_LOCK(hDispMutex);
//        lv_meter_set_indicator_value(guider_ui.src_main_meter_omega, guider_ui.src_main_meter_omega_scale_1_ndline_0, s16RealOmega);
//        FR_OS_MUTEX_UNLOCK(hDispMutex);
//        FR_OS_DelayMs(20);

        FR_OS_MUTEX_LOCK(hDispMutex);
        lv_meter_set_indicator_end_value(guider_ui.src_main_meter_omega, guider_ui.src_main_meter_omega_scale_1_arc_0, s16RealOmega);
//        FR_OS_MUTEX_UNLOCK(hDispMutex);
//        FR_OS_DelayMs(20);
//
//        FR_OS_MUTEX_LOCK(hDispMutex);
        lv_meter_set_indicator_end_value(guider_ui.src_main_meter_omega, guider_ui.src_main_meter_omega_scale_1_arc_1, s16TargetOmega);
        FR_OS_MUTEX_UNLOCK(hDispMutex);
        FR_OS_DelayMs(20);

//        FR_OS_MUTEX_LOCK(hDispMutex);
//        lv_label_set_text_fmt(guider_ui.src_main_label_angle,"%d", s16Angle);
//        lv_label_set_text_fmt(guider_ui.src_main_label_omega,"%d/%d", s16TargetOmega, s16RealOmega);
//        FR_OS_MUTEX_UNLOCK(hDispMutex);
//        FR_OS_DelayMs(20);
    }
}

void vApplicationTickHook(void)
{
    lv_tick_inc(1);
}

