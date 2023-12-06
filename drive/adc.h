#ifndef _ADC_H
#define _ADC_H

#include "stm32f4xx.h"
#include "input_ctrl.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "FR_OS.h"

#define OffsetNum 100
#define ADC_CHANNEL_INUSE_NUM  (4)

typedef struct
{
    u8  u8ValLen;
    u16 *pu16AdcConvVal;
    u16 *pu16AdcConvValOffset;
    float *pf32AdcOutput;
}ST_ADC_Conv_t;

#define Max_Size_Wind 100
typedef struct
{
    float Num_Wind;
    uint8_t Index;
    float Sum;
    float Wind[Max_Size_Wind];
}MoveAvarageFilter_TypeDef;//»¬¶¯Æ½¾ùÂË²¨

extern TaskHandle_t hAdcAcquireTask;
extern QueueHandle_t hAdcConv_Queue;
extern ST_ADC_Conv_t stAdcConv;

void Adc_Init(void);
//void GetThro_Data(void);
//u8 GetThro_Offset(void);
void ADC_Data_Handle(void);
float *ADC_Get_Output(void);

void Adc_Acquire_Task(void *pvParameters);


#endif
