/*
 * led.c
 *
 *  Created on: Jan 19, 2018
 *      Author: p
 */

#include "led.h"
uint32_t led_Init(LEDColorType LED)
{
	uint32_t retVal = 0;
	GPIO_TypeDef* GPIOx;
	GPIO_InitTypeDef led_GPIOTypedef;
	if(LED == GREEN)
	{
		GPIOx = GREEN_LED_PORT;
		led_GPIOTypedef.GPIO_Pin = GREEN_LED;
	}else
	{
		if(LED == BLUE)
		{
			GPIOx = BLUE_LED_PORT;
			led_GPIOTypedef.GPIO_Pin = BLUE_LED;
		}else
		{
			GPIOx = RED_LED_PORT;
			led_GPIOTypedef.GPIO_Pin = RED_LED;
		}
	}

	led_GPIOTypedef.GPIO_Mode = GPIO_Mode_OUT;
	led_GPIOTypedef.GPIO_OType = GPIO_OType_PP;
	led_GPIOTypedef.GPIO_Speed = GPIO_Speed_50MHz;
	led_GPIOTypedef.GPIO_PuPd = GPIO_PuPd_NOPULL;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	GPIO_Init(GPIOx, &led_GPIOTypedef);

	return(retVal);
}
uint32_t led_ON(LEDColorType LED)
{
	uint32_t retVal = 0;
	uint32_t pinNumber = 0;
	GPIO_TypeDef* GPIOx;
	if(LED == GREEN)
	{
		GPIOx = GREEN_LED_PORT;
		pinNumber = GREEN_LED;
	}else
	{
		if(LED == BLUE)
		{
			GPIOx = BLUE_LED_PORT;
			pinNumber = BLUE_LED;
		}else
		{
			GPIOx = RED_LED_PORT;
			pinNumber = RED_LED;
		}
	}

	GPIO_SetBits(GPIOx, pinNumber);
	return(retVal);
}

uint32_t led_OFF(LEDColorType LED)
{
	uint32_t retVal = 0;
	uint32_t pinNumber = 0;
	GPIO_TypeDef* GPIOx;
	if(LED == GREEN)
	{
		GPIOx = GREEN_LED_PORT;
		pinNumber = GREEN_LED;
	}else
	{
		if(LED == BLUE)
		{
			GPIOx = BLUE_LED_PORT;
			pinNumber = BLUE_LED;
		}else
		{
			GPIOx = RED_LED_PORT;
			pinNumber = RED_LED;
		}
	}
	GPIO_ResetBits(GPIOx,pinNumber);
	return(retVal);
}
uint32_t led_Toggle(LEDColorType LED)
{
	uint32_t retVal = 0;
	if(LED == BLUE)
	{
		retVal = 1;
	}
	return(retVal);
}
