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

void CZL_GetTemp(void);
void CZL_GetAllItem(void);
void CZL_Connect(void);
#endif