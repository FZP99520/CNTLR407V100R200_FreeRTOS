#include "key.h"
#include "led.h"
#include "beep.h"
//#include "log.h"

TaskHandle_t hKeyTask;
EventGroupHandle_t hKeyEvent;

ST_KeyStatus_t stKeyStatus;

//按键初始化函数
void KEY_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    //DEBUG_TRACE("IN\n");
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5; //KEY 对应引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//已经外接上拉电阻
    GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;
    GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE

    stKeyStatus.bInitDone = TRUE;

    //DEBUG_TRACE("OK\n");
} 

void Key_Task(void *pvParameters)
{
    BaseType_t xReturn = pdPASS;
    EN_KEY_FLAG eKeyFlag;
    TickType_t TickCount = 0;
    memset(&stKeyStatus,0,sizeof(ST_KeyStatus_t));

    while(pdTRUE)
    {
        stKeyStatus.u32KeyFlag = 0;
        KEY_Scan(&stKeyStatus);

        if(stKeyStatus.u32KeyFlag & E_KEY_LEFT_UPPER)
        {
            //KEY_StatusClearBit(&stKeyStatus,E_KEY_LEFT_UPPER);
            eKeyFlag = E_KEY_LEFT_UPPER;
            //xReturn = xQueueSend(Test_QueueHandle, &eKeyFlag, 0);
            //xReturn = xSemaphoreGive(KeySemBin_Handle);
            //xReturn = xSemaphoreTake(Led2SemMutex_Handle, pdTRUE);
            //FR_OS_MUTEX_LOCK(Led2SemMutex_Handle);
            //xEventGroupSetBits(hKeyEvent,E_KEY_EVENT_LEFT_UPPER);
            //FR_OS_EventSetBits(hKeyEvent, E_KEY_EVENT_LEFT_UPPER);
            //xReturn = xTaskNotify(hLed2Task, 0x02, eSetValueWithOverwrite);
            FR_OS_EventSetBits(hBeepEvent, E_BEEP_EVENT_FLASH);
        }
        if(stKeyStatus.u32KeyFlag & E_KEY_RIGHT_UPPER)
        {
            //KEY_StatusClearBit(&stKeyStatus,E_KEY_LEFT_LEFT);
            eKeyFlag = E_KEY_LEFT_LEFT;
            //xReturn = xQueueSend(Test_QueueHandle, &eKeyFlag, 0);
            //xReturn = xSemaphoreGive(KeySemBin_Handle);
            //FR_OS_MUTEX_UNLOCK(Led2SemMutex_Handle);
            //FR_OS_EventSetBits(hKeyEvent, E_KEY_EVENT_LEFT_LEFT);
            if(xReturn == pdPASS)
            {
                //LED2_ON;
                //FR_OS_DelayMs(100);
                //LED2_OFF;
            }
        }
        if(stKeyStatus.u32KeyFlag & E_KEY_LEFT_DOWN)
        {
            //KEY_StatusClearBit(&stKeyStatus,E_KEY_LEFT_DOWN);
            eKeyFlag = E_KEY_LEFT_LEFT;
            //xReturn = xQueueSend(Test_QueueHandle, &eKeyFlag, 0);
            //xReturn = xSemaphoreGive(KeySemBin_Handle);
            //FR_OS_MUTEX_UNLOCK(Led2SemMutex_Handle);
            //FR_OS_EventSetBits(hKeyEvent, E_KEY_EVENT_LEFT_DOWN);
            if(xReturn == pdPASS)
            {
                //LED2_ON;
                //FR_OS_DelayMs(100);
                //LED2_OFF;
            }
        }
        
        FR_OS_EventSetBits(hKeyEvent, stKeyStatus.u32KeyFlag);
        /*
        if(stKeyStatus.u32KeyFlag)
        {
            FR_OS_EventSetBits(hLed2Event, E_LED_EVENT_FLASH);
        }*/
        FR_OS_DelayMs(20);
    }
}

void KEY_StatusClearBit(ST_KeyStatus_t * pstKeyStatus, EN_KEY_FLAG eKeyFlag)
{
    pstKeyStatus->u32KeyFlag &= ~eKeyFlag;
}

u32 KEY_Get_Flag(void)
{
    
    return stKeyStatus.u32KeyFlag;
}

ST_KeyStatus_t* KEY_GetInfo(void)
{
    return &stKeyStatus;
}

void KEY_Scan(ST_KeyStatus_t* pstKeyStatus)
{
    if(KEY_READ_LEFT_LEFT)
    {
        pstKeyStatus->u32KeyFlag |= E_KEY_LEFT_LEFT;
    }
    if(KEY_READ_LEFT_DOWN)
    {
        pstKeyStatus->u32KeyFlag |= E_KEY_LEFT_DOWN;
    }
    if(KEY_READ_LEFT_RIGHT)
    {
        pstKeyStatus->u32KeyFlag |= E_KEY_LEFT_RIGHT;
    }
    if(KEY_READ_LEFT_UP)
    {
        pstKeyStatus->u32KeyFlag |= E_KEY_LEFT_UP;
    }
    if(KEY_READ_RIGHT_LEFT)
    {
        pstKeyStatus->u32KeyFlag |= E_KEY_RIGHT_LEFT;
    }
    if(KEY_READ_RIGHT_DOWN)
    {
        pstKeyStatus->u32KeyFlag |= E_KEY_RIGHT_DOWN;
    }
    if(KEY_READ_RIGHT_RIGHT)
    {
        pstKeyStatus->u32KeyFlag |= E_KEY_RIGHT_RIGHT;
    }
    if(KEY_READ_RIGHT_UP)
    {
        pstKeyStatus->u32KeyFlag |= E_KEY_RIGHT_UP;
    }
    if(KEY_READ_LEFT_UPPER)
    {
        pstKeyStatus->u32KeyFlag |= E_KEY_LEFT_UPPER;
    }
    if(KEY_READ_RIGHT_UPPER)
    {
        pstKeyStatus->u32KeyFlag |= E_KEY_RIGHT_UPPER;
    }
    
}

