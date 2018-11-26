/**
  * @file    GPIO.c 
  * @author  WB R&D Team - openmcu666
  * @version V0.1
  * @date    2015.6.9
  * @brief   GPIO Driver
  */
#include "stm32f4xx.h"
#include "Gpio.h"

/**
  * @brief  初始化LED管脚
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(LED_GPIO_CLK , ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(LED_GPIO_PORT,LED1_GPIO_PIN|LED2_GPIO_PIN);
}

/**
  * @brief  翻转端口电平
  * @param  选择相应LED 1-LED1 2-LED2
  * @retval None
  */
void LED_Toggle(uint8_t led)
{
  if (led == 1) {
    LED_GPIO_PORT->ODR ^= LED1_GPIO_PIN;	            //GPIOD->ODR端口输出数据寄存器
  } else if (led == 2) {
    LED_GPIO_PORT->ODR ^= LED2_GPIO_PIN; 
  }
}

/**
  * @brief  初始化蜂鸣器控制管脚PD3
  * @param  None
  * @retval None
  */
void BEEP_Init(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(BEEP_GPIO_CLK , ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;
  GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);
  GPIO_ResetBits(BEEP_GPIO_PORT,BEEP_GPIO_PIN);

}

