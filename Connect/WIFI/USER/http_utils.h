#ifndef _HTTP_UTILS_H
#define _HTTP_UTILS_H
#include "stm32f1xx.h"
#include "string.h"
#include "Usart.h"
#include "includes.h"

#define POST_HTTP_ADD  "/api/operate"
#define HOST_ADD       "protobuf.stepiot.com"
#define CONTENT_TYPE   "application/json"
#define HTTP_TOKEN     "eyJhbGciOiJIUzI1NiJ9.eyJncm91cEJybiI6IjEzMzk0NTIzNzc3OTIwNTMyNDkifQ.P7z47ML6hWAZaYytvs-lVS-X0H_vaMdTrAGDOEU7ZAQ"
void HTTP_Protocol_Init(void);
void HTTP_SendCommand(uint8_t *act);
#endif
