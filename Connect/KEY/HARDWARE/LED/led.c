#include "led.h"
#include "delay.h"
#include "stm32f1xx.h"
#include "includes.h"
//==========================================================
//	�������ƣ�	LED_Init
//
//	�������ܣ�	LED�Ƴ�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================

uint8_t number0 = 1;  //��ʼ��

void LED_Init(void)
{
	
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();           	//����GPIOBʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOBʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_13|GPIO_PIN_14; 	//PB0,PB1,PB13,PB14
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull=GPIO_PULLUP;          	//����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	 	//����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_13|GPIO_PIN_14,GPIO_PIN_SET);	//PB0,PB1,PB13,PB14��1��Ĭ�ϳ�ʼ�������
    
    GPIO_Initure.Pin   = GPIO_PIN_4|GPIO_PIN_5; 	//����IO��
    GPIO_Initure.Mode  = GPIO_MODE_INPUT;  	                            //�������
    GPIO_Initure.Pull  = GPIO_PULLUP;          	                        //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	  	                    //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);

      GPIO_Initure.Pin   = GPIO_PIN_6|GPIO_PIN_7; 	//����IO��
    GPIO_Initure.Mode  = GPIO_MODE_INPUT;  	                            //�������
    GPIO_Initure.Pull  = GPIO_PULLUP;          	                        //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	  	                    //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

//==========================================================
//	�������ƣ�	LED_Config
//
//	�������ܣ�	LED����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void LED_Config(void)
{
		//  ��ˮ��	
		switch(number0)
		{
			case 1:
			{
				//��תLED1״̬
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED1_GPIO_PIN);
				delay_ms(300); 
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED1_GPIO_PIN);   
				break;
			}				
			case 2:
			{
				//��תLED2״̬
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED2_GPIO_PIN);
				delay_ms(300); 
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED2_GPIO_PIN);   
				break;
			}	
			case 3:
			{
				//��תLED3״̬
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED3_GPIO_PIN);
				delay_ms(300); 
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED3_GPIO_PIN);   
				break;
			}		
			case 4: 
			{
				//��תLED4״̬
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED4_GPIO_PIN);
				delay_ms(300); 
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED4_GPIO_PIN);   
				number0 = 0;
				break;
			}	
			
			default: break;
		}
		number0+=1;
}

uint8_t LedMod_KeyAllRead(void)
{
    uint8_t val;
    val  = READ_SW1();
    val |= READ_SW2() << 1;
    val |= READ_SW3() << 2;
    val |= READ_SW4() << 3;
    
    return ~val;
}
uint8_t kin1 = 0,kin2 = 0;
uint8_t LedMod_KeyPoll(void)
{
    uint8_t kv = 0;
    
    static  uint8_t AllSwRelease = 1;
    
    kin1 = LedMod_KeyAllRead()&0x0F;
    
    if((kin1) && (AllSwRelease == 1))
    {
        OSTimeDly(5);        
        kin2 = LedMod_KeyAllRead()&0x0F;
        if(kin1 == kin2)
        {
            printf("kin1=%02X\r\n",kin2);
            AllSwRelease = 0;
            if(kin1 & 0x01)
            {
                kv = SW1;
            }
            else if(kin1 & 0x02)
            {
                kv = SW2;
            }
            else if(kin1 & 0x04)
            {
                kv = SW3;
            }
            else if(kin1 & 0x08)
            {
                kv = SW4;
            }
        }
    }
    if((!kin1) && (!AllSwRelease))
    {
        AllSwRelease = 1;
        kv = KB_RELASE;
    }
    
    return kv;
}
