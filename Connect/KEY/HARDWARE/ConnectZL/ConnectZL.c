#include "ConnectZL.h"
static uint8_t gB[64];
const char JSON_GetAllItem[ ]="GET  http://cloud.ziotai.com/coop/proj/getAllDevInfoByProjectId?projectId=98 HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n"                                                 
"Host:cloud.ziotai.com\r\n"                                                                  
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"Content-Type:application/json\r\n"
"\r\n";

const char JSON_GetTemp[ ]="GET  http://cloud.ziotai.com/coop/dev/getDevInfoByDeviceId?deviceId=660 HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:keep-alive\r\n"
"Content-Type:application/json\r\n\r\n";

void CZL_Connect(void)
{
    WiFi_Send(TCP_CIPSTART,strlen(TCP_CIPSTART));
}
void CZL_GetAllItem(void)
{
    uint8_t len;
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(JSON_GetAllItem));
    WiFi_Send(gB,strlen((const char*)gB));
    WiFi_Send((uint8_t*)JSON_GetAllItem,strlen(JSON_GetAllItem));
}
void CZL_GetTemp(void)
{
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(JSON_GetTemp));
    WiFi_Send(gB,strlen((const char*)gB));
    HAL_Delay(500);
    WiFi_Send((uint8_t*)JSON_GetTemp,strlen(JSON_GetTemp));
}