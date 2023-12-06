#include "led.h"
#include "systick.h"
#include "log.h"
#include "arm_math.h"

TaskHandle_t hLed1Task;
TaskHandle_t hLed2Task;
EventGroupHandle_t hLed1Event;
EventGroupHandle_t hLed2Event;

u16 u16LED1_PWM_Duty = 0;

static void _LED_Decode_Info(ST_LED_Info_t *pstLedInfo, u32 u32InputValue);


void Led_Init()  //LED初始化函数
{
    GPIO_InitTypeDef  GPIO_InitStruct; //结构体变量定义
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    //DEBUG_TRACE("IN\n");
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;  //LED1
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT; //推挽输出模式
    GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);  
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;  //LED2
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType=GPIO_OType_OD;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init(GPIOC,&GPIO_InitStruct);
    LED1_OFF;
    LED2_OFF;

    //DEBUG_TRACE("OK\n");
}

void Led1_Task(void * pvParameters)
{
    BaseType_t xReturn = pdFALSE;
    #define LED_PWM_SET_COMPARE(x) TIM_SetCompare2(TIM5,x)
    u8 bAutoRun = TRUE;
    float f32theta = 0;
    float f32SinVal = 0;
    float f32CosVal = 0;
    float f32FreqHz = 1;
    float f32Tcnt = 0;
    float f32Ts = 20;//unit: ms

    EventBits_t EventBitsOut = 0;
    EventWaitParams_t stEventWaitParams;
    u32 NotificationValue;

    while(pdTRUE)
    {
        //FR_OS_EventWait(hLed1Event, stEventWaitParams, &EventBitsOut);
        xReturn = xTaskNotifyWait(0, 0xFFFFFFFF, &NotificationValue, f32Ts);
#if 1
        if(xReturn == pdTRUE)
        {
            bAutoRun = FALSE;
            u16LED1_PWM_Duty = NotificationValue&0xFFFF;
            LED_PWM_SET_COMPARE(u16LED1_PWM_Duty);
        }
        if(bAutoRun)
        {
            arm_sin_cos_f32(360*f32FreqHz*f32Tcnt, &f32SinVal, &f32CosVal);
            u16LED1_PWM_Duty = (f32SinVal+1.0f)/2*LED_PWM_PERIOD;
            LED_PWM_SET_COMPARE(u16LED1_PWM_Duty);
            f32Tcnt +=f32Ts/1000;
        }
#else
        float f32Angle;
        float f32Omega;
        float f32Alpha;
        u16 u16PwmDuty = 0;
        //AS5048A_GetAngleInfo(&f32Angle, &f32Omega, &f32Alpha);
        u16PwmDuty = f32Omega/360.0f*LED_PWM_PERIOD;
        LED_PWM_SET_COMPARE(u16PwmDuty);
        FR_OS_DelayMs(20);
#endif
    }
}

ST_LED_Info_t stLed2RunInfo;

void Led2_Task(void * pvParameters)
{
    BaseType_t xReturn = pdFALSE;
    u8 bKeep = FALSE;
    u32 u32Cnt = 0;
    
    EventBits_t EventBitsOut = 0;
    EventWaitParams_t stEventWaitParams;
    u32 NotificationValue;
    memset(&stLed2RunInfo,0,sizeof(ST_LED_Info_t));
    memset(&stEventWaitParams,0,sizeof(EventWaitParams_t));

    stEventWaitParams.bClearOnExit = pdTRUE;
    stEventWaitParams.bWaitForAllBits = pdFALSE;
    stEventWaitParams.xTicksToWait = portMAX_DELAY;
    stEventWaitParams.EventBitWaitFor = E_LED_EVENT_ON |
                                        E_LED_EVENT_OFF |
                                        E_LED_EVENT_FLASH;
    while(pdTRUE)
    {
        //xRet = xSemaphoreTake(Led2SemMutex_Handle,0);
        //FR_OS_MUTEX_LOCK(Led2SemMutex_Handle);
        //xEventGroupWaitBits(hKeyEvent,E_KEY_EVENT_LEFT_UPPER,pdTRUE,pdFALSE,portMAX_DELAY);
        //FR_OS_EventWait(hKeyEvent,stEventWaitParams, &EventBitsOut);
        //if(EventBitsOut&E_KEY_EVENT_LEFT_UPPER)
        //xRet = xTaskNotifyWait(ULONG_MAX, 0xFFFFFFFF, &NotificationValue, portMAX_DELAY);

        xReturn = xTaskNotifyWait(0, 0xFFFFFFFF, &NotificationValue, portMAX_DELAY);

task_start:
        if(xReturn == pdTRUE)
        {
            _LED_Decode_Info(&stLed2RunInfo, NotificationValue);
            if(stLed2RunInfo.u8Event&E_LED_EVENT_ON)
            {
                LED2_ON;
            }
            else if(stLed2RunInfo.u8Event&E_LED_EVENT_OFF)
            {
                LED2_OFF;
            }
            else if(stLed2RunInfo.u8Event&E_LED_EVENT_FLASH)
            {
                if(stLed2RunInfo.u8RepeatTimes == 0xFF)
                    bKeep = TRUE;
                else
                    bKeep = FALSE;

                do
                {
                    LED2_ON;
                    FR_OS_DelayMs(stLed2RunInfo.u16Period*stLed2RunInfo.u8Duty/100);
                    LED2_OFF;
                    FR_OS_DelayMs(stLed2RunInfo.u16Period*(100 - stLed2RunInfo.u8Duty)/100);
                    if(bKeep)
                    {
                        xReturn = xTaskNotifyWait(0, 0xFFFFFFFF, &NotificationValue, 0);
                        if(xReturn == pdTRUE)
                        {
                            goto task_start;
                        }
                    }
                    else
                    {
                        stLed2RunInfo.u8RepeatTimes--;
                    }
                }while(stLed2RunInfo.u8RepeatTimes>0);
            }
            else;
        }
#if 0
        FR_OS_EventWait(hLed2Event, stEventWaitParams, &EventBitsOut);
        if(EventBitsOut&E_LED_EVENT_ON)
        {
            LED2_ON;
        }
        else if(EventBitsOut&E_LED_EVENT_OFF)
        {
            LED2_OFF;
        }
        else if(EventBitsOut&E_LED_EVENT_FLASH)
        {
            LED2_ON;
            FR_OS_DelayMs(80);
            LED2_OFF;
            FR_OS_DelayMs(80);
        }
        else;
#endif
        //FR_OS_MUTEX_UNLOCK(Led2SemMutex_Handle);
        //FR_OS_DelayMs(20);
    }
}

u8 LED_Send_Event_To_LED2(u8 u8Event, u8 u8RepeatTimes, u8 u8Duty, u16 u16Period)
{
    u32 NotificationValue = 0;
    NotificationValue |= u16Period&LED_RUN_PERIOD_MASK;
    NotificationValue |= (u8Duty&0xFF)<<12;
    NotificationValue |= (u8RepeatTimes&0xFF)<<20;
    NotificationValue |= u8Event<<28;
    if(xTaskNotify(hLed2Task, NotificationValue, eSetValueWithOverwrite) == pdTRUE)
        return TRUE;
    else
        return FALSE;
}

static void _LED_Decode_Info(ST_LED_Info_t *pstLedInfo, u32 u32InputValue)
{
    pstLedInfo->u8Event       = (u32InputValue&LED_RUN_EVENT_MASK)>>28;
    pstLedInfo->u8RepeatTimes = (u32InputValue&LED_RUN_REPEAT_TIMES_MASK)>>20;
    pstLedInfo->u8Duty        = (u32InputValue&LED_RUN_DUTY_MASK)>>12;
    pstLedInfo->u16Period     = (u32InputValue&LED_RUN_PERIOD_MASK)>>0;
}

void LED_Flash(u8 times)
{
    u8 i;
    for(i=0;i<times;i++)
    {
        LED1_ON;
        LED1_ON;
        Delay_ms(200);
        LED1_OFF;
        LED1_OFF;
        Delay_ms(200);
    }
}

