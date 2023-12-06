#ifndef _led_H
#define _led_H

#include "stm32f4xx.h"
#include "FR_OS.h"

#define LED1_ON         GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define LED1_OFF        GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define LED1_Status     GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)
#define LED1_STA_TOGGLE LED1_Status?LED1_ON:LED1_OFF

#define LED2_ON         GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define LED2_OFF        GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define LED2_Status     GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_4)
#define LED2_STA_TOGGLE LED2_Status?LED2_ON:LED2_OFF

#define LED_PWM_PERIOD  1000



//[11:0]  12bit : u16Period
//[19:12] 8bit  : u8Duty
//[27:20] 8bit  : u8RepeatTimes
//[31:28] 4bit  :event

#define LED_RUN_PERIOD_MASK             (0x0FFF<<0)
#define LED_RUN_DUTY_MASK               (0xFF<<12)
#define LED_RUN_REPEAT_TIMES_MASK       (0xFF<<20)
#define LED_RUN_EVENT_MASK              (0x0F<<28)


typedef struct
{
    u8 u8Event;
    u8 u8RepeatTimes;
    u8  u8Duty;    //0.01%
    u16 u16Period; //ms
}ST_LED_Info_t;

typedef enum
{
    E_LED_EVENT_ON     = 1<<0,
    E_LED_EVENT_OFF    = 1<<1,
    E_LED_EVENT_FLASH  = 1<<2
}EN_LedEvent;

extern TaskHandle_t hLed1Task;
extern TaskHandle_t hLed2Task;
extern EventGroupHandle_t hLed1Event;
extern EventGroupHandle_t hLed2Event;


void LED_Flash(u8 times);
void Led_Init(void);
void Led1_Task(void * pvParameters);
void Led2_Task(void * pvParameters);
u8 LED_Send_Event_To_LED2(u8 u8Event, u8 u8RepeatTimes, u8 u8Duty, u16 u16Period);

#endif
