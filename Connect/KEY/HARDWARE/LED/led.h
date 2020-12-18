#ifndef _LED_H
#define _LED_H

#include "stm32f1xx_hal.h"

#define  LED_GPIO_PORT  GPIOB

#define  LED1_GPIO_PIN  GPIO_PIN_0
#define  LED2_GPIO_PIN  GPIO_PIN_1
#define  LED3_GPIO_PIN  GPIO_PIN_13
#define  LED4_GPIO_PIN  GPIO_PIN_14

#define LED1_ON()     LED_GPIO_PORT->BRR   = LED1_GPIO_PIN
#define LED1_OFF()     LED_GPIO_PORT->BSRR = LED1_GPIO_PIN

#define LED2_ON()     LED_GPIO_PORT->BRR   = LED2_GPIO_PIN
#define LED2_OFF()     LED_GPIO_PORT->BSRR = LED2_GPIO_PIN

#define LED3_ON()     LED_GPIO_PORT->BRR   = LED3_GPIO_PIN
#define LED3_OFF()     LED_GPIO_PORT->BSRR = LED3_GPIO_PIN

#define LED4_ON()     LED_GPIO_PORT->BRR   = LED4_GPIO_PIN
#define LED4_OFF()    LED_GPIO_PORT->BSRR = LED4_GPIO_PIN


#define LED_1ON_234OFF()   LED1_ON();LED2_OFF();LED3_OFF();LED4_OFF();
#define LED_2ON_134OFF()   LED1_OFF();LED2_ON();LED3_OFF();LED4_OFF();
#define LED_3ON_124OFF()   LED1_OFF();LED2_OFF();LED3_ON();LED4_OFF();
#define LED_4ON_123OFF()   LED1_OFF();LED2_OFF();LED3_OFF();LED4_ON();

#define LED_ALL_OFF()      LED1_OFF();LED2_OFF();LED3_OFF();LED4_OFF(); 
#define LED_ALL_ON()       LED1_ON();LED2_ON();LED3_ON();LED4_ON(); 

#define SW_PRESS     0
#define SW_RELASE    1

enum
{    
    SW1 = 1,
    SW2,
    SW3,
    SW4,
    KB_RELASE = 0,
};
#define READ_SW1()   ((GPIOA->IDR&GPIO_PIN_5)?SW_RELASE:SW_PRESS)
#define READ_SW2()   ((GPIOA->IDR&GPIO_PIN_4)?SW_RELASE:SW_PRESS)
#define READ_SW3()   ((GPIOB->IDR&GPIO_PIN_7)?SW_RELASE:SW_PRESS)
#define READ_SW4()   ((GPIOB->IDR&GPIO_PIN_6)?SW_RELASE:SW_PRESS)

uint8_t LedMod_KeyPoll(void);
extern uint8_t number0;

void LED_Init(void);

void LED_Config(void);



#endif
