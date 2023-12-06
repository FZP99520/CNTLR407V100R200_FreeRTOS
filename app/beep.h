#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f4xx.h"
#include "FR_OS.h"

#define BeepOn()   GPIO_ResetBits(GPIOC,GPIO_Pin_13)
#define BeepOff()  GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define BeepStatus() GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)


typedef enum
{
    E_BEEP_EVENT_ON     = BIT(0),
    E_BEEP_EVENT_OFF    = BIT(1),
    E_BEEP_EVENT_FLASH  = BIT(2),
}EN_BeepEvent;

extern TaskHandle_t hBeepTask;
extern EventGroupHandle_t hBeepEvent;

void Beep_Init(void);
void Beep_ms(u16 nms);
void Beep_times(u8 n);
void Beep(u8 t,u16 time_work,u16 time_stop);
void BEEP_Task(void *pvParameters);


#endif
