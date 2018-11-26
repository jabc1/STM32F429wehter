#ifndef _USART_H_
#define _USART_H_

#include "stdio.h"
#include <string.h> 
#include <stm32f4xx.h>
#include <stdarg.h>

/* 设置当前串口为USART1 */
#define UART_COM                  USART1
#define UART_IRQ                  USART1_IRQn
#define USART_IRQHandler					USART1_IRQHandler
#define DATA_BUF_SIZE							1024//

extern uint16_t data_length;
extern uint16_t data_lengthu6;
extern uint8_t rx_buffer[];
extern uint8_t tx_buffer[];

extern uint8_t rx_bufferu6[];
extern uint8_t tx_bufferu6[];
void USART1_Init(void);
void USART1_SendChar(unsigned char ch);
void USART1_SendString(unsigned char *s);
void USART1_Send_Data(u8 *buf,uint16_t len);
void USART6_Init(void);
void USART6_Send_Data(u8 *buf,uint16_t len);
void USART6_SendString(unsigned char *s);
void USART6_printf( USART_TypeDef* USARTx, char *Data, ... );
#endif
