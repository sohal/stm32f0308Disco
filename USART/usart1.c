/*
 * usart1.c
 *
 *  Created on: Jan 19, 2018
 *      Author: p
 */


#include "usart1.h"
#include "string.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx.h"
static struct buf_st 	rbuf;
static struct buf_st 	tbuf;
static uint32_t			tx_restart = 1;
#define SIO_RBUFLEN 	((uint16_t)(rbuf.in - rbuf.out))
#define SIO_TBUFLEN 	((uint16_t)(tbuf.in - tbuf.out))

uint32_t usart1_Init(void)
{
	uint32_t retVal = 0;
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = TX_GPIO | RX_GPIO;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

	USART_InitStruct.USART_BaudRate = BAUD_RATE;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStruct);

	USART_Cmd(USART1, ENABLE);

	return (retVal);
}
uint32_t usart1_Tx(uint8_t *pBuff, uint8_t length)
{
	uint32_t retVal = 0;
	if((length > TBUF_SIZE) ||(pBuff == (void*)0) || (SIO_TBUFLEN >= TBUF_SIZE))
	{
		retVal = 1;
	}else
	{
		memcpy(&tbuf, pBuff,length);
		if(tx_restart)
		{
			tx_restart = 0;
			USART1->CR1 |= USART_FLAG_TXE;
		}
	}
	return (retVal);
}
uint32_t usart1_Rx(uint8_t *pBuff, uint8_t length)
{
	uint32_t retVal = 0;
	if(SIO_RBUFLEN == RBUF_SIZE)
	{
		memcpy(pBuff, &rbuf, length);
		rbuf.in = 0;
		rbuf.out = 0;
	}else
	{
		rbuf.out = length;
		retVal = 1;
	}
	return (retVal);
}

void USART1_IRQHandler(void)
{
	volatile uint32_t IIR;
	struct buf_st *p;

	IIR = USART1->ISR;
	if(IIR & USART_FLAG_RXNE)
	{
		USART1->ISR &= ~USART_FLAG_RXNE;

		p = &rbuf;

		if(((p->in - p->out) & ~(RBUF_SIZE - 1)) == 0)
		{
			p->buf[p->in & (RBUF_SIZE - 1)] = (USART1->RDR & 0x01FF);
			p->in++;
		}
	}

	if(IIR & USART_FLAG_TXE)
	{
		USART1->ISR &= ~USART_FLAG_TXE;

		p = &tbuf;

		if(p->in != p->out)
		{
			USART1->TDR = (p->buf[p->out & (TBUF_SIZE - 1)] & 0x1FF);
			p->out++;
			tx_restart = 0;
		}else
		{
			tx_restart = 1;
			USART1->CR1 &= ~USART_FLAG_TXE;
		}
	}

}
