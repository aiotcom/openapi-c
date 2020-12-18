#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "timer.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"	
#include "WiFi.h"
#include "includes.h"
#include "ConnectZL.h"
#include "http_utils.h"
/***************************UCOSII 任务设置***************************/

#define START_TASK_PRIO      			6  //设置任务优先级
#define START_STK_SIZE  				64 //设置任务堆栈大小
OS_STK START_TASK_STK[START_STK_SIZE];     //任务堆栈	
void Start_Task(void *pdata);	           //任务函数
 			   
//同步任务
#define SYNC_TASK_PRIO       			4 //设置任务优先级
#define SYNC_STK_SIZE  		    		512 //设置任务堆栈大小
OS_STK SYNC_TASK_STK[SYNC_STK_SIZE];       //任务堆栈	
void Sync_Task(void *pdata);               //任务函数

//数据采集、控制任务
#define CC_TASK_PRIO       			5 //设置任务优先级
#define CC_STK_SIZE  		    		64 //设置任务堆栈大小
OS_STK CC_TASK_STK[CC_STK_SIZE];       //任务堆栈	
void CC_Task(void *pdata);               //任务函数

OS_EVENT SemRecvSync;
uint8_t SendWiFiMutex = 0;
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
const uint8_t LocalDeviceId = WIFI_ID;
const uint8_t DeviceIdList[ ]={WIFI_ID,KEY_ID};
const uint8_t NumOfDevice = sizeof(DeviceIdList);
uint8_t SensorData[3]={0,0},SendSensorData = 0;
uint8_t LinghtState = 0,LockState = 0,CurtainsState = 0,ZXD_1_State = 1,ZXD_2_State = 1;
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
uint16_t clen;
uint8_t sample[ ]="1234.56\"";
float retfloat;
int main(void)
{
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
    UART1_Init(115200);								//初始化串口1
    UART2_Init(115200);								//初始化串口2
    UART3_Init(115200);
    printf("this usart3 printf\r\n");
    Rs485_Init();   									//初始化485
    TIM3_Init(1000-1,64-1);						//初始化定时器3
    slip_init(&RSLIP);
         
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
    uint8_t temp,SensorSwitch = 0;
    pdata = pdata;
    ESP8266_Init();	//初始化ESP8266 
    
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);	
    printf("connce target\r\n");
    while(1)
    {
        OSTimeDly(5000);  
//连接 云              
//连接 云        
    }
}
/*
同步任务 
*/
void Sync_Task(void *pdata)
{
    INT8U err,i = 0;
    uint8_t Count100Hz;
    pdata = pdata;
    while(1)
    {
        OSTimeDly(1);
        if((++Count100Hz)>=100)
        {
            Count100Hz = 0;
            Rs485_Send(LocalDeviceId,KEY_ID,CID_POLL,0,(void*)0);  
        }
//获取数据485总线数据 
        if((RSLIP.flg == 1)&&(RSLIP.rid == LocalDeviceId))
        {
            RSLIP.flg = 0;
            if(RSLIP.data[0])
            {
                printf("get cmd=%d\r\n",RSLIP.data[0]);
                if(RSLIP.data[0] == 0x01)
                {
                   LinghtState = 1 - LinghtState;
                  if(LinghtState){
                      HTTP_SendCommand("turnOnLight"); 
                  }
                  else if(LinghtState == 0){
                      HTTP_SendCommand("turnOffLight");                   
                  }
                }
                else if(RSLIP.data[0] == 0x02)
                {
                   LockState = 1 - LockState;
                  if(LockState){
                      HTTP_SendCommand("openDoorLock"); 
                  }
                  else if(LockState == 0){
                      HTTP_SendCommand("closeDoorLock");                   
                  }
                }
                else if(RSLIP.data[0] == 0x03)
                {
                   CurtainsState = 1 - CurtainsState;
                  if(CurtainsState){
                      HTTP_SendCommand("openCurtain"); 
                  }
                  else if(CurtainsState == 0){
                      HTTP_SendCommand("closeCurtain");                   
                  }
                }                
            }
#if 0           
            if(RSLIP.data[0])
            {
                RSLIP.flg = 0;
                printf("%d,%d,%d,%d,%d\r\n",RSLIP.seq,RSLIP.cid,RSLIP.tid,RSLIP.rid,RSLIP.dl);
                i = RSLIP.dl;
                for(i=0;i<RSLIP.dl;i++)
                {
                    printf("%02x ",RSLIP.data[i]);
                }
            }
#endif     
            if(USART2_RX_STA){
                OSTimeDly(5);
                USART2_RX_STA = 0;
                printf("Receive:=%s\r\n",USART2_RX_BUF);
                memset((void*)USART2_RX_BUF,0,USART2_REC_LEN);
            }
        }  
//获取数据485总线数据           
    }
}
void DoPoll(void)
{
}
