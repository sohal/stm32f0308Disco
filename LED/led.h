/*
 * led.h
 *
 *  Created on: Jan 19, 2018
 *      Author: p
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

#define GREEN_LED_PORT	GPIOC
#define BLUE_LED_PORT	GPIOC
#define RED_LED_PORT	GPIOA

#define GREEN_LED		GPIO_Pin_9
#define BLUE_LED		GPIO_Pin_8
#define RED_LED			GPIO_Pin_1
typedef enum {
	GREEN,
	BLUE,
	RED
}LEDColorType;

uint32_t led_Init(LEDColorType);
uint32_t led_ON(LEDColorType);
uint32_t led_OFF(LEDColorType);
uint32_t led_Toggle(LEDColorType);

#endif /* LED_H_ */
