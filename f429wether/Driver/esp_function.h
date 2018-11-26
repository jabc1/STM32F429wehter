#ifndef __ESP_FUNCTION_H
#define	__ESP_FUNCTION_H 


#include "stm32f4xx.h"
#include <stdbool.h>
#include "USART.h"

#define CHPD_RST_GPIO_PORT            GPIOA
#define CHPD_GPIO_PIN                 GPIO_Pin_4
#define RST_GPIO_PIN                  GPIO_Pin_5
#define CHPD_RST_GPIO_CLK             RCC_AHB1Periph_GPIOA

#define GPIO0_GPIO_PORT               GPIOH
#define GPIO0_GPIO_PIN                GPIO_Pin_2
#define GPIO0_GPIO_CLK                RCC_AHB1Periph_GPIOH

#define GPIO2_GPIO_PORT               GPIOD
#define GPIO2_GPIO_PIN                GPIO_Pin_13
#define GPIO2_GPIO_CLK                RCC_AHB1Periph_GPIOD


#define     ESP8266_printf( fmt, ... )           USART6_printf ( USART6, fmt, ##__VA_ARGS__ ) 
#define     PC_printf( fmt, ... )                printf ( fmt, ##__VA_ARGS__ )

#define     ESP8266_CH_HIGH_LEVEL()             GPIO_SetBits( GPIOA, GPIO_Pin_4 )
#define     ESP8266_CH_LOW_LEVEL()              GPIO_ResetBits( GPIOA, GPIO_Pin_4 )

#define     ESP8266_RST_HIGH_LEVEL()            GPIO_SetBits( GPIOA, GPIO_Pin_5 )
#define     ESP8266_RST_LOW_LEVEL()             GPIO_ResetBits( GPIOA, GPIO_Pin_5 )

/* 8266工作模式*/
typedef enum{
	STA,
  AP,
  STA_AP  
} Work_ModeTypeDef;


typedef enum{
	 enumTCP,
	 enumUDP,
} ENUM_NetPro_TypeDef;
	

typedef enum{
	Multiple_ID_0 = 0,
	Multiple_ID_1 = 1,
	Multiple_ID_2 = 2,
	Multiple_ID_3 = 3,
	Multiple_ID_4 = 4,
	Single_ID     = 5,
} ENUM_ID_NO_TypeDef;
	

typedef enum{
	OPEN = 0,
	WEP = 1,
	WPA_PSK = 2,
	WPA2_PSK = 3,
	WPA_WPA2_PSK = 4,
} ENUM_AP_PsdMode_TypeDef;

void ESP8266_Init(void);
void ESP8266_Rst                         ( void );

bool ESP8266_Cmd                         ( char * cmd, char * reply1, char * reply2, u32 waittime );
bool ESP8266_Work_Mode_Choose             ( Work_ModeTypeDef Mode );

bool ESP8266_Enable_MultipleId           ( FunctionalState enumEnUnvarnishTx );

bool ESP8266_StartOrShutServer           ( FunctionalState enumMode, char * pPortNum, char * pTimeOver );

void ESP8266_AP_TCP_Server               ( void );
void ESP8266_StaTcpClient_ApTcpServer    ( void );
void delay(__IO uint32_t nCount);
void ESP8266_STA_TCP_Client(void);
void ESP8266_TransparentSend(void);
void ESP8266_TransparentExit( void );
u8   ESP8266_Connect_To_Server(u8 *server,u16 port);
#endif    
