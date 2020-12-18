#include "http_utils.h"
#define LOCALBUFFER_SIZE   512
static uint8_t localBuffer[LOCALBUFFER_SIZE];
static uint8_t tempbuf[256];
static uint8_t tempbuf1[64];
/*http 初始化*/
void HTTP_Protocol_Init(void)
{
    memset(&localBuffer[0],0,LOCALBUFFER_SIZE);
  
    sprintf((void*)&tempbuf[0],"POST %s HTTP/1.1\r\n",POST_HTTP_ADD);
    strcat((void*)&localBuffer[0],(const char*)&tempbuf[0]);
  
    sprintf((void*)&tempbuf[0],"Host: %s\r\n",HOST_ADD);
    strcat((void*)&localBuffer[0],(const char*)&tempbuf[0]);      
  
    sprintf((void*)&tempbuf[0],"Content-Type: %s\r\n",CONTENT_TYPE);
    strcat((void*)&localBuffer[0],(const char*)&tempbuf[0]); 
}

void HTTP_SendCommand(uint8_t *act)
{
  HTTP_Protocol_Init();
  sprintf((void*)&tempbuf[0],"\r\n{\r\n\"token\":\"%s\",\r\n\"action\":\"%s\"\r\n}",HTTP_TOKEN,act);
  sprintf((void*)&tempbuf1[0],"Content-Length: %d\r\n",strlen((const char*)tempbuf)-2); //{ 前的\r\n不要 
  
  strcat((void*)&localBuffer[0],(const char*)&tempbuf1[0]); 
  strcat((void*)&localBuffer[0],(const char*)&tempbuf[0]);   
  USART2_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
  sprintf((void*)tempbuf,"%d\r\n",strlen(localBuffer));
  USART2_Send(tempbuf,strlen((const char*)tempbuf));  
  OSTimeDly(1000);
  USART2_Send(localBuffer,strlen((const char*)localBuffer));
}