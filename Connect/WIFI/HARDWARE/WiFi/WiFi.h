#ifndef __WiFi_H__
#define __WiFi_H__

#include "stm32f1xx_hal.h"
#include "Usart.h"

#define AT         	 "AT\r\n"
#define CWMODE     	 "AT+CWMODE_DEF=1\r\n"																//设置模式为AP+STA
#define RST        	 "AT+RST\r\n"																			//软重启模块
#define CIFSR        "AT+CIFSR\r\n"																		//查询IP地址
//#define CWJAP        "AT+CWJAP=\"bacheng\",\"Stepiot123\"\r\n"							//设置SID和PWD连接网络
#define CWJAP        "AT+CWJAP=\"CMCC-rpCJ\",\"fr22twkg\"\r\n"							//设置SID和PWD连接网络
#define TCP_CIPSTART "AT+CIPSTART=\"SSL\",\"protobuf.stepiot.com\",443\r\n"		//设置为TCP协议传输并指定IP和端口号
//#define TCP_CIPSTART "AT+CIPSTART=\"SSL\",\"iot.espressif.cn\",8443,1000\r\n"
#define CIPMODE      "AT+CIPMODE=1\r\n"																//透传
#define CIPSEND      "AT+CIPSEND\r\n"																	//开始传输


/**
  * @brief  初始化ESP8266,并配置路由和连接平台
  * @param  server:按照AT指令配置服务器地址和端口字符串
    * @param  ssid_pwd: 按照AT指令配置路由器的SSID和PWD
  * @retval NONE
  **/
void ESP8266_Init(void);
void WiFi_Send(uint8_t *pdata,uint16_t len);
#endif


