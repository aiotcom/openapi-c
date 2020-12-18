#include "Rs485.h"	
#include "usart.h"
#include "slip.h"

/*		ģʽ����		*/ 
#define RS485_TX_EN()		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_SET)		//485����ģʽ
#define RS485_RX_EN()		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_RESET)	//485����ģʽ

uint8_t RS485_PNT_Buffer[128];
//==========================================================
//	�������ƣ�	Rs485_Init
//
//	�������ܣ�	��ʼ��485
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rs485_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��

    GPIO_Initure.Pin = GPIO_PIN_8|GPIO_PIN_5;		//PA8
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;//�������
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; //����
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);	//PA8��0   ��ʼ���ȴ�ģʽ
    RS485_RX_EN();
    
    GPIOA->BRR = GPIO_PIN_5;
    HAL_Delay(100);
    GPIOA->BSRR = GPIO_PIN_5;
}

static void delay_us(unsigned int nus)
{		
	unsigned int j = 0;
	while(nus--)
	{
        j = 2;
		while(j--)
		{;}
	}
}

static uint8_t SendBuffer[128],sbidx=0,seq=0;
static uint8_t SlipBuffer[128];
void Rs485_Send(uint16_t SrcAdr,uint16_t DstAdr,uint16_t Cmd,uint8_t Len,uint8_t *pData)
{			
    uint8_t SendLenght;
    sbidx = 0;
    SendBuffer[sbidx++] = seq++;
    SendBuffer[sbidx++] = Cmd;
    SendBuffer[sbidx++] = SrcAdr;
    SendBuffer[sbidx++] = DstAdr;
    SendBuffer[sbidx++] = Len;
    if(Len)
    {
        memcpy((void*)&SendBuffer[sbidx],pData,Len);
        sbidx = sbidx + Len;
    }
    slip_pack(SendBuffer,sbidx,SlipBuffer,&SendLenght);
    
	RS485_TX_EN();		//����485����
    delay_us(10);
	//HAL_UART_Transmit(&UART1_Handler,SlipBuffer,SendLenght,10);//485��������
    USART1_Send(SlipBuffer,SendLenght);
    delay_us(20);
	RS485_RX_EN();		//����485����
}

void Rs485_SendRaw(uint8_t *pdata,uint16_t len)
{
	RS485_TX_EN();		//����485����
    delay_us(10);
	USART1_Send(pdata,len);//485��������
    delay_us(10);
	RS485_RX_EN();		//����485����
}