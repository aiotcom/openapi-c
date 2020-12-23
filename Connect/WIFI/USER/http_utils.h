#ifndef _HTTP_UTILS_H
#define _HTTP_UTILS_H
#include "stm32f1xx.h"
#include "string.h"
#include "Usart.h"
#include "includes.h"

#define POST_HTTP_ADD  "/api/operate"
#define HOST_ADD       "protobuf.stepiot.com"
#define CONTENT_TYPE   "application/json"
#define HTTP_TOKEN     "token字符串"
void HTTP_Protocol_Init(void);
void HTTP_SendCommand(uint8_t *act);
#endif
