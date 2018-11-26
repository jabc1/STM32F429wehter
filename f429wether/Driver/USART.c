/**
  * @file    USART.c 
  * @author  WB R&D Team - openmcu666
  * @version V0.1
  * @date    2015.6.9
  * @brief   USART Driver
  */

#include "usart.h"

uint16_t data_length;								  // 数据长度
uint16_t data_lengthu6;								// 数据长度
uint8_t rx_buffer[DATA_BUF_SIZE];		  // 接收缓冲区
//uint8_t tx_buffer[DATA_BUF_SIZE];		  // 发送缓冲区

uint8_t rx_bufferu6[DATA_BUF_SIZE];		// 接收缓冲区
//uint8_t tx_bufferu6[DATA_BUF_SIZE];		// 发送缓冲区

/**
  * @brief  初始化串口1
  * @param  None
  * @retval None
  */
void USART1_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);


	USART_InitStructure.USART_BaudRate   =115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;
	USART_InitStructure.USART_Parity     = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART1, &USART_InitStructure);

	USART_Cmd(USART1, ENABLE);
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                      //开启接收中断
  data_length=0;								  // 数据长度
  data_lengthu6=0;								// 数据长度
}

/**
  * @brief  串口1发送一个字符
  * @param  ch:要发送的data
  * @retval None
  */
void USART1_SendChar(unsigned char ch)
{
   USART_SendData (USART1,ch);                                               
   while( USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET );                   
   USART_ClearFlag(USART1,USART_FLAG_TC);                                   
}

/**
  * @brief  发送字符串
  * @param  s:要发送的数据
  * @retval None
  */
void USART1_SendString(unsigned char *s)
{
    while (*s != '\0') {
         USART1_SendChar(*s++);
    }
}

void USART1_Send_Data(u8 *buf,uint16_t len)
{
	uint16_t t; 
  	for(t=0;t<len;t++)		//循环发送数据
		{
			while(USART_GetFlagStatus(UART_COM,USART_FLAG_TC)==RESET); //等待发送结束					
			USART_SendData(UART_COM,buf[t]); //发送数据
			
		}	 
		while(USART_GetFlagStatus(UART_COM,USART_FLAG_TC)==RESET); //等待发送结束	

}

int fputc(int ch, FILE *f)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
	{}

	return ch;
}

/**
  * @brief  USART6初始化
  * @param  None
  * @retval None
  */
void USART6_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           //中断分组2,占4个抢占优先级和4个响应优先级
  
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);                //TX

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);                //RX

  USART_InitStructure.USART_BaudRate = 115200;//9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART6, &USART_InitStructure);
	
  NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);
  USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);   //使能接收中断
	
  USART_Cmd(USART6, ENABLE);
}

/**
  * @brief  串口1发送一个字符
  * @param  ch:要发送的data
  * @retval None
  */
void USART6_SendChar(unsigned char ch)
{
   USART_SendData (USART6,ch);                                               
   while( USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET );                   
   USART_ClearFlag(USART6,USART_FLAG_TC);                                   
}

void USART6_SendString(unsigned char *s)
{
    while (*s != '\0') {
         USART6_SendChar(*s++);
    }
}
/**
  * @brief  发送数据函数
  * @param  *buf:发送缓冲区地址 len:需要发送的数据长度
  * @retval None
  */
void USART6_Send_Data(u8 *buf,uint16_t len)
{
	uint16_t t; 
  	for(t=0;t<len;t++)		                                     //循环发送数据
		{	
			while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET); //等待发送结束	

			USART_SendData(USART6,buf[t]);                           //发送数据
		}	
	while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET);     //等待发送结束	
}


static char *itoa( int value, char *string, int radix )
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

void USART6_printf( USART_TypeDef* USARTx, char *Data, ... )
{
	const char *s;
  int d;   
  char buf[16];

  va_list ap;
  va_start(ap, Data);

	while ( *Data != 0)     // 判断是否到达字符串结束符
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //回车符
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;

				case 'n':							          //换行符
					USART_SendData(USARTx, 0x0a);	
					Data ++;
					break;
				
				default:
					Data ++;
				    break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //字符串
					s = va_arg(ap, const char *);
          for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
          }
					Data++;
          break;

        case 'd':										//十进制
          d = va_arg(ap, int);
          itoa(d, buf, 10);
          for (s = buf; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
          }
					Data++;
          break;
				 default:
						Data++;
				    break;
			}		 
		} /* end of else if */
		else USART_SendData(USARTx, *Data++);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
	}
}
