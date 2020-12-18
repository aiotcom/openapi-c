#ifndef __Rs485_H
#define __Rs485_H
#include "stm32f1xx_hal.h"
#include "slip.h"
void Rs485_SendRaw(uint8_t *pdata,uint16_t len);
extern uint8_t RS485_PNT_Buffer[ ];
#define  RS485PNT(...)   sprintf(RS485_PNT_Buffer,__VA_ARGS__); Rs485_SendRaw(RS485_PNT_Buffer,strlen(RS485_PNT_Buffer));
void Rs485_Config(uint8_t fag); //控制485操作

void Rs485_Init(void);  //初始化485
void Rs485_Send(uint16_t SrcAdr,uint16_t DstAdr,uint16_t Cmd,uint8_t Len,uint8_t *pData);
#endif

