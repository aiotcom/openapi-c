#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "timer.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"	
#include "WiFi.h"
#include "ConnectZL.h"
#include "led.h"
#include "includes.h"
/***************************UCOSII 任务设置***************************/

#define START_TASK_PRIO      			6  //设置任务优先级
#define START_STK_SIZE  				64 //设置任务堆栈大小
OS_STK START_TASK_STK[START_STK_SIZE];     //任务堆栈	
void Start_Task(void *pdata);	           //任务函数
 			   
//同步任务
#define SYNC_TASK_PRIO       			4 //设置任务优先级
#define SYNC_STK_SIZE  		    		64 //设置任务堆栈大小
OS_STK SYNC_TASK_STK[SYNC_STK_SIZE];       //任务堆栈	
void Sync_Task(void *pdata);               //任务函数

//数据采集、控制任务
#define CC_TASK_PRIO       			5 //设置任务优先级
#define CC_STK_SIZE  		    		64 //设置任务堆栈大小
OS_STK CC_TASK_STK[CC_STK_SIZE];       //任务堆栈	
void CC_Task(void *pdata);               //任务函数

OS_EVENT SemRecvSync;
uint8_t kv=0;
/***************************UCOSII 任务设置***************************/
enum{
    WIFI_ID = 0x01,
    KEY_ID,
    LCD_ID
};

enum{
    CID_POLL = 0x01,
    CID_KEY,
    CID_SENSORS_TEMP
};
_SLIP RSLIP;
const uint8_t LocalDeviceId = KEY_ID;
const uint8_t DeviceIdList[ ]={WIFI_ID,KEY_ID,LCD_ID};
const uint8_t NumOfDevice = sizeof(DeviceIdList);

void DoPoll(void);
/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2018-01-01
*
*	版本： 		V1.0
*
*	说明： 		WIFI库函数操作实验-HAL库版本
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/
uint32_t PollCount = 0;
uint8_t PollDelay(uint32_t *count,uint32_t timeout)
{
    uint8_t ret = 0;
    if(HAL_GetTick()>=(*count))
    {
        *count = HAL_GetTick() + timeout;
        ret = 1;
    }
    
    return ret;
}
uint8_t Regist_buf[18] ={0x55,0xAA,0x00,0x00,0x00,0x00,0x0A,0x01,0x02,0x03,0x04,0x05,0x06,0x00,0x00,0x00,0x00,0xF2},bt = 0;
int main(void)
{ 
    uint8_t i = 0;

    OS_CPU_SysTickInit();
	OSInit();   
 	OSTaskCreate(Start_Task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();	    
}

/*
start 任务
*/
void Start_Task(void *pdata)
{
    pdata = pdata;
    UART1_Init(115200);								//初始化串口1
    UART2_Init(115200);								//初始化串口2
    UART3_Init(115200);								//初始化串口3  
    printf("this is usart3 printf\r\n");
    Rs485_Init();   									//初始化485
    TIM3_Init(1000-1,64-1);						//初始化定时器3
    slip_init(&RSLIP);
    LED_Init();    
   // RS485PNT("this is rs485 print\r\n");
    
    SemRecvSync = *OSSemCreate (0);
    
    OSTaskCreate(Sync_Task,(void *)0,(OS_STK *)&SYNC_TASK_STK[SYNC_STK_SIZE-1],SYNC_TASK_PRIO);//创建起始任务
    OSTaskCreate(CC_Task,(void *)0,(OS_STK *)&CC_TASK_STK[CC_STK_SIZE-1],CC_TASK_PRIO);//创建起始任务  
    OSTaskDel(START_TASK_PRIO);    
}
/*
数据采集与控制任务
*/
void CC_Task(void *pdata)
{
    uint8_t temp;
    pdata = pdata;
    while(1)
    {
        OSTimeDly(1);
        temp = LedMod_KeyPoll(); 
        if((kv==0)&&(temp)){
            kv = temp;        
        }        
    }
}
/*
同步任务 
*/
void Sync_Task(void *pdata)
{
    INT8U err,i;
    pdata = pdata;
    while(1)
    {
        OSSemPend(&SemRecvSync,0,&err);    
        if(RSLIP.flg == 1)
        {
            RSLIP.flg = 0;  
            printf("get req1\r\n");
            if((kv)&&(RSLIP.cid == CID_POLL)&&(RSLIP.rid == LocalDeviceId))
            {
                printf("get req2\r\n");
                Rs485_Send(LocalDeviceId,WIFI_ID,CID_KEY,1,&kv);
                kv = 0;
            }
#if 0            
            RSLIP.flg = 0;
            RS485PNT("%d,%d,%d,%d,%d\r\n",RSLIP.seq,RSLIP.cid,RSLIP.tid,RSLIP.rid,RSLIP.dl);
            i = RSLIP.dl;
            for(i=0;i<RSLIP.dl;i++)
            {
                RS485PNT("%02x ",RSLIP.data[i]);
            }
#endif            
        }        
    }
}
void DoPoll(void)
{
    static uint8_t i = 0;
    if(PollDelay(&PollCount,10))
    {        
        if(DeviceIdList[i] == LocalDeviceId)
        {
        
        }
        else
        {
            Rs485_Send(LocalDeviceId,DeviceIdList[i],CID_POLL,0,(void*)0);
        }  
        i = (i>=NumOfDevice)?0:(++i);      
    }
}
