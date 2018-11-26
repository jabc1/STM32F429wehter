/**
  * @file    USART.c 
  * @author  WB R&D Team - openmcu666
  * @version V0.1
  * @date    2015.6.9
  * @brief   USART Driver
  */

#include "usart.h"

uint16_t data_length;								  // ���ݳ���
uint16_t data_lengthu6;								// ���ݳ���
uint8_t rx_buffer[DATA_BUF_SIZE];		  // ���ջ�����
//uint8_t tx_buffer[DATA_BUF_SIZE];		  // ���ͻ�����

uint8_t rx_bufferu6[DATA_BUF_SIZE];		// ���ջ�����
//uint8_t tx_bufferu6[DATA_BUF_SIZE];		// ���ͻ�����

/**
  * @brief  ��ʼ������1
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
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                      //���������ж�
  data_length=0;								  // ���ݳ���
  data_lengthu6=0;								// ���ݳ���
}

/**
  * @brief  ����1����һ���ַ�
  * @param  ch:Ҫ���͵�data
  * @retval None
  */
void USART1_SendChar(unsigned char ch)
{
   USART_SendData (USART1,ch);                                               
   while( USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET );                   
   USART_ClearFlag(USART1,USART_FLAG_TC);                                   
}

/**
  * @brief  �����ַ���
  * @param  s:Ҫ���͵�����
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
  	for(t=0;t<len;t++)		//ѭ����������
		{
			while(USART_GetFlagStatus(UART_COM,USART_FLAG_TC)==RESET); //�ȴ����ͽ���					
			USART_SendData(UART_COM,buf[t]); //��������
			
		}	 
		while(USART_GetFlagStatus(UART_COM,USART_FLAG_TC)==RESET); //�ȴ����ͽ���	

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
  * @brief  USART6��ʼ��
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           //�жϷ���2,ռ4����ռ���ȼ���4����Ӧ���ȼ�
  
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
  USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);   //ʹ�ܽ����ж�
	
  USART_Cmd(USART6, ENABLE);
}

/**
  * @brief  ����1����һ���ַ�
  * @param  ch:Ҫ���͵�data
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
  * @brief  �������ݺ���
  * @param  *buf:���ͻ�������ַ len:��Ҫ���͵����ݳ���
  * @retval None
  */
void USART6_Send_Data(u8 *buf,uint16_t len)
{
	uint16_t t; 
  	for(t=0;t<len;t++)		                                     //ѭ����������
		{	
			while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET); //�ȴ����ͽ���	

			USART_SendData(USART6,buf[t]);                           //��������
		}	
	while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET);     //�ȴ����ͽ���	
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

	while ( *Data != 0)     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;

				case 'n':							          //���з�
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
				case 's':										  //�ַ���
					s = va_arg(ap, const char *);
          for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
          }
					Data++;
          break;

        case 'd':										//ʮ����
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
