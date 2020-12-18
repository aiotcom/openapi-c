#include "ConnectZL.h"
#include "includes.h"
#include "math.h"
#include "stdio.h"
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

const char JSON_GetHumidity[ ]="GET  http://cloud.ziotai.com/coop/dev/getDevInfoByDeviceId?deviceId=661 HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:keep-alive\r\n"
"Content-Type:application/json\r\n\r\n";

const char JSON_GetPM25[ ]="GET  http://cloud.ziotai.com/coop/dev/getDevInfoByDeviceId?deviceId=662 HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:keep-alive\r\n"
"Content-Type:application/json\r\n\r\n";

const char JSON_FanCtrlOff[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:184\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"647\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"1\"\r\n,"
"    \"funVal\": \"false\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";
const char JSON_FanCtrlOn[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:183\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"647\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"1\"\r\n,"
"    \"funVal\": \"true\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";

const char JSON_ZXD_1_On[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:183\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"645\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"1\"\r\n,"
"    \"funVal\": \"true\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";
const char JSON_ZXD_1_Off[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:184\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"645\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"1\"\r\n,"
"    \"funVal\": \"false\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";

const char JSON_ZXD_2_On[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:183\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"646\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"1\"\r\n,"
"    \"funVal\": \"true\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";

/*‘Ï–Õµ∆*/
const char JSON_ZXD_2_Off[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:183\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"646\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"1\"\r\n,"
"    \"funVal\": \"true\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";
/*Õ≤µ∆*/
const char JSON_TongDeng_On[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:183\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"643\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"1\"\r\n,"
"    \"funVal\": \"true\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";
const char JSON_TongDeng_Off[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:184\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"643\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"1\"\r\n,"
"    \"funVal\": \"false\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";


const char JSON_HL_1_Off[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:183\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"649\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"3\"\r\n,"
"    \"funVal\": \"true\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";

const char JSON_HL_1_On[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:183\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"649\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"4\"\r\n,"
"    \"funVal\": \"true\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";


const char JSON_TGB_Off[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:184\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"648\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"1\"\r\n,"
"    \"funVal\": \"flase\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";

const char JSON_TGB_On[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:183\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"648\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"1\"\r\n,"
"    \"funVal\": \"true\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";
const char JSON_HL_2_Off[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:183\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"650\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"4\"\r\n,"
"    \"funVal\": \"true\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";

const char JSON_HL_2_On[ ]="POST  http://cloud.ziotai.com/coop/dev/operateDevByDeviceId HTTP/1.0\r\n"
"restKey:3A9A02B9474EDDEFF4882C0F6D881BED\r\n"
"token:d6cdf45a1f4b46b343e4f419e634ec32\r\n" 
"Host:cloud.ziotai.com\r\n"
"User-Agent:esp-idf/1.0 esp32\r\n"
"Connection:Keep-Alive\r\n"
"content-length:183\r\n"
"Content-Type:application/json\r\n\r\n"
"{\r\n"
"	\"deviceId\":\"650\",\r\n"
"	\"operateInfos\":  [\r\n"
"      {\r\n"
"    \"funNo\": \"3\"\r\n,"
"    \"funVal\": \"true\"\r\n,"
"    \"operateInfo\":{\r\n"
"       \"fromType\":\"press\"\r\n"
"    },\r\n"
"    \"desc\":\" \"\r\n"
"      }\r\n"
"	]\r\n"
"}\r\n";
float fpow(float in,uint8_t mi)
{
    float ret = 1;
    while(mi--)
    {
        ret = ret*in;
    }
    
    return ret;
}
uint8_t ch;    
float fDat = 0;
float A2I_ByMark(uint8_t *PtrStart,uint8_t mark)
{
    float Inc_0p1 = 0.1;
    fDat = 0;
    while(*PtrStart != mark)
    {
        if((*PtrStart) == '.')
        {
            PtrStart++;
            while(*PtrStart != mark)
            {
                fDat = fDat + (*PtrStart-0x30)*Inc_0p1;
                Inc_0p1 = Inc_0p1*0.1;
                PtrStart++;
            }
        } 
        else
        {
            fDat = fDat*10.0;
            fDat = fDat + (*PtrStart-0x30);
            PtrStart++;
        }
    }
    return fDat;    
}
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
uint8_t *pstr;
uint8_t CZL_GetTemp(void)
{
    uint8_t temp;
    CZL_Connect();
    OSTimeDly(500);
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(JSON_GetTemp));
    WiFi_Send(gB,strlen((const char*)gB));
    OSTimeDly(500);
    USART2_RX_STA = 0;
    WiFi_Send((uint8_t*)JSON_GetTemp,strlen(JSON_GetTemp));   
    OSTimeDly(300);
    if((pstr = strstr((void*)USART2_RX_BUF,"\"funVal\":\"")))
    {
        pstr = pstr + strlen("\"funVal\":\"");
        temp = ((*pstr)-0x30)*10 + ((*(pstr+1))-0x30)*1;
        //RS485PNT("temp=%d\r\n",temp);
    }
    
    return temp;
}

uint8_t CZL_GetHumidity(void)
{   
    uint8_t humidity;
    CZL_Connect();
    OSTimeDly(500);
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(JSON_GetHumidity));
    WiFi_Send(gB,strlen((const char*)gB));
    OSTimeDly(500);
    USART2_RX_STA = 0;
    WiFi_Send((uint8_t*)JSON_GetHumidity,strlen(JSON_GetHumidity));   
    OSTimeDly(300);
    if((pstr = strstr((void*)USART2_RX_BUF,"\"funVal\":\"")))
    {
        pstr = pstr + strlen("\"funVal\":\"");
        humidity = ((*pstr)-0x30)*10 + ((*(pstr+1))-0x30)*1;
        //RS485PNT("humidity=%d\r\n",temp);
    }    
    return humidity;
}

void CZL_ControlFan(uint8_t state)
{   
    uint8_t humidity;
    const char *p;
    if(state == 0)
    {
        p = JSON_FanCtrlOff;
    }
    else
    {
        p = JSON_FanCtrlOn;    
    }
    CZL_Connect();
    OSTimeDly(500);
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(p));
    WiFi_Send(gB,strlen((const char*)gB));
    OSTimeDly(500);
    USART2_RX_STA = 0;
    WiFi_Send((uint8_t*)p,strlen(p));   
    OSTimeDly(500);
}

void CZL_ZXD_1(uint8_t state)
{   
    uint8_t humidity;
    const char *p;
    if(state == 0)
    {
        p = JSON_ZXD_1_Off;
    }
    else
    {
        p = JSON_ZXD_1_On;    
    }
    CZL_Connect();
    OSTimeDly(500);
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(p));
    WiFi_Send(gB,strlen((const char*)gB));
    OSTimeDly(500);
    USART2_RX_STA = 0;
    WiFi_Send((uint8_t*)p,strlen(p));   
    OSTimeDly(500);
}

void CZL_ZXD_2(uint8_t state)
{   
    uint8_t humidity;
    const char *p;
    if(state == 0)
    {
        p = JSON_ZXD_2_Off;
    }
    else
    {
        p = JSON_ZXD_2_On;    
    }
    CZL_Connect();
    OSTimeDly(500);
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(p));
    WiFi_Send(gB,strlen((const char*)gB));
    OSTimeDly(500);
    USART2_RX_STA = 0;
    WiFi_Send((uint8_t*)p,strlen(p));   
    OSTimeDly(500);
}

uint16_t CZL_GetPM25(void)
{
    uint8_t PM25;
    CZL_Connect();
    OSTimeDly(500);
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(JSON_GetPM25));
    WiFi_Send(gB,strlen((const char*)gB));
    OSTimeDly(500);
    USART2_RX_STA = 0;
    WiFi_Send((uint8_t*)JSON_GetPM25,strlen(JSON_GetPM25));   
    OSTimeDly(300);
    if((pstr = strstr((void*)USART2_RX_BUF,"\"funVal\":\"")))
    {
        pstr = pstr + strlen("\"funVal\":\"");
        PM25 = A2I_ByMark(pstr,'\"');
        //RS485PNT("humidity=%d\r\n",temp);
    }    
    return PM25;

}
void CZL_HL_1(uint8_t state)
{   
    uint8_t humidity;
    const char *p;
    if(state == 0)
    {
        p = JSON_HL_1_Off;
    }
    else
    {
        p = JSON_HL_1_On;    
    }
    CZL_Connect();
    OSTimeDly(500);
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(p));
    WiFi_Send(gB,strlen((const char*)gB));
    OSTimeDly(500);
    USART2_RX_STA = 0;
    WiFi_Send((uint8_t*)p,strlen(p));   
    OSTimeDly(500);
}

void CZL_HL_2(uint8_t state)
{   
    uint8_t humidity;
    const char *p;
    if(state == 0)
    {
        p = JSON_HL_2_Off;
    }
    else
    {
        p = JSON_HL_2_On;    
    }
    CZL_Connect();
    OSTimeDly(500);
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(p));
    WiFi_Send(gB,strlen((const char*)gB));
    OSTimeDly(500);
    USART2_RX_STA = 0;
    WiFi_Send((uint8_t*)p,strlen(p));   
    OSTimeDly(500);
}

void CZL_TongDeng(uint8_t state)
{   
    uint8_t humidity;
    const char *p;
    if(state == 0)
    {
        p = JSON_TongDeng_Off;
    }
    else
    {
        p = JSON_TongDeng_On;    
    }
    CZL_Connect();
    OSTimeDly(500);
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(p));
    WiFi_Send(gB,strlen((const char*)gB));
    OSTimeDly(500);
    USART2_RX_STA = 0;
    WiFi_Send((uint8_t*)p,strlen(p));   
    OSTimeDly(500);
}

void CZL_TGB(uint8_t state)
{   
    uint8_t humidity;
    const char *p;
    if(state == 0)
    {
        p = JSON_TGB_Off;
    }
    else
    {
        p = JSON_TGB_On;    
    }
    CZL_Connect();
    OSTimeDly(500);
    WiFi_Send("AT+CIPSEND=",strlen((const char*)"AT+CIPSEND="));
    sprintf((void*)gB,"%d\r\n",strlen(p));
    WiFi_Send(gB,strlen((const char*)gB));
    OSTimeDly(500);
    USART2_RX_STA = 0;
    WiFi_Send((uint8_t*)p,strlen(p));   
    OSTimeDly(500);
}

