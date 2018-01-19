/*
 * usart1.h
 *
 *  Created on: Jan 19, 2018
 *      Author: p
 */

#ifndef USART1_H_
#define USART1_H_

#include "stm32f0xx.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"

#define TX_GPIO_PORT	GPIOA
#define TX_GPIO			GPIO_Pin_9
#define RX_GPIO_PORT	GPIOA
#define RX_GPIO			GPIO_Pin_10
#define BAUD_RATE		57600

#define TBUF_SIZE		64
#define RBUF_SIZE		64

struct buf_st
{
	uint32_t in;
	uint32_t out;
	uint8_t buf[RBUF_SIZE];
};


uint32_t usart1_Init(void);
uint32_t usart1_Tx(uint8_t *pBuff, uint8_t length);
uint32_t usart1_Rx(uint8_t *pBuff, uint8_t length);
#endif /* USART1_H_ */
