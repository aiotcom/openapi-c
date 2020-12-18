#ifndef __WiFi_H__
#define __WiFi_H__

#include "stm32f1xx_hal.h"
#include "Usart.h"

#define AT         	 "AT\r\n"
#define CWMODE     	 "AT+CWMODE_DEF=1\r\n"																//����ģʽΪAP+STA
#define RST        	 "AT+RST\r\n"																			//������ģ��
#define CIFSR        "AT+CIFSR\r\n"																		//��ѯIP��ַ
//#define CWJAP        "AT+CWJAP=\"bacheng\",\"Stepiot123\"\r\n"							//����SID��PWD��������
#define CWJAP        "AT+CWJAP=\"CMCC-rpCJ\",\"fr22twkg\"\r\n"							//����SID��PWD��������
#define TCP_CIPSTART "AT+CIPSTART=\"SSL\",\"protobuf.stepiot.com\",443\r\n"		//����ΪTCPЭ�鴫�䲢ָ��IP�Ͷ˿ں�
//#define TCP_CIPSTART "AT+CIPSTART=\"SSL\",\"iot.espressif.cn\",8443,1000\r\n"
#define CIPMODE      "AT+CIPMODE=1\r\n"																//͸��
#define CIPSEND      "AT+CIPSEND\r\n"																	//��ʼ����


/**
  * @brief  ��ʼ��ESP8266,������·�ɺ�����ƽ̨
  * @param  server:����ATָ�����÷�������ַ�Ͷ˿��ַ���
    * @param  ssid_pwd: ����ATָ������·������SSID��PWD
  * @retval NONE
  **/
void ESP8266_Init(void);
void WiFi_Send(uint8_t *pdata,uint16_t len);
#endif


