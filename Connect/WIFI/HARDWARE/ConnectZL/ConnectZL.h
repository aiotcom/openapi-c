#ifndef _CONNECTZL_H
#define _CONNECTZL_H
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "timer.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"	
#include "WiFi.h"
#include "ConnectZL.h"

uint8_t CZL_GetTemp(void);
uint8_t CZL_GetHumidity(void);
void CZL_GetAllItem(void);
void CZL_Connect(void);
void CZL_ControlFan(uint8_t state);
void CZL_ZXD_2(uint8_t state);
void CZL_ZXD_1(uint8_t state);
uint16_t CZL_GetPM25(void);
void CZL_HL_1(uint8_t state);
void CZL_HL_2(uint8_t state);
void CZL_TongDeng(uint8_t state);
void CZL_TGB(uint8_t state);
float A2I_ByMark(uint8_t *PtrStart,uint8_t mark);
extern uint8_t FanCtrlJson[ ];
#endif