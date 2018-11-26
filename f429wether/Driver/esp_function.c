#include "esp_function.h"
#include "Gpio.h"
#include "delay.h" 
#include "uni.h"

void delay(__IO uint32_t nCount)
{
  __IO uint32_t index = 0; 
  for(index = 80000*nCount; index != 0; index--)
  {
  }
}

void ESP8266_Init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(CHPD_RST_GPIO_CLK|GPIO0_GPIO_CLK|GPIO2_GPIO_CLK , ENABLE);     
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;            //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStructure.GPIO_Pin = CHPD_GPIO_PIN;
  GPIO_Init(CHPD_RST_GPIO_PORT, &GPIO_InitStructure);      
  GPIO_SetBits(CHPD_RST_GPIO_PORT,CHPD_GPIO_PIN);         
	
	GPIO_InitStructure.GPIO_Pin = RST_GPIO_PIN;
  GPIO_Init(CHPD_RST_GPIO_PORT, &GPIO_InitStructure);      //RST and CHPD config
	
  GPIO_InitStructure.GPIO_Pin = GPIO0_GPIO_PIN;
  GPIO_Init(GPIO0_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO2_GPIO_PIN;
  GPIO_Init(GPIO2_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIO0_GPIO_PORT,GPIO0_GPIO_PIN); 
  GPIO_SetBits(GPIO2_GPIO_PORT,GPIO2_GPIO_PIN);	

	GPIO_InitStructure.GPIO_Pin = RST_GPIO_PIN;
  GPIO_Init(CHPD_RST_GPIO_PORT, &GPIO_InitStructure);      
	GPIO_ResetBits(CHPD_RST_GPIO_PORT,RST_GPIO_PIN);     
	delay_ms ( 10 );
	GPIO_SetBits(CHPD_RST_GPIO_PORT,RST_GPIO_PIN);     
	USART6_Init();
}

 /**
  * @brief  ����8266ģ��
  * @param  None
  * @retval None
  */
void ESP8266_Rst (void)
{
	 ESP8266_RST_LOW_LEVEL();
	 delay_ms(300); 
	 ESP8266_RST_HIGH_LEVEL();
}


/**
  * @brief  ����ATָ��
  * @param  cmd:�����͵�ָ��
  *         reply1,reply2:�ڴ�����Ӧ,�����践��,����NULL
  *         waittime:�ȴ���Ӧ��ʱ��(ע��ָ��ͼ�����ܹ���,�������׳���busy)
  * @retval 0:ָ���ʧ�� 
  *         1:ָ��ͳɹ�
  */
bool ESP8266_Cmd ( char * cmd, char * reply1, char * reply2, u32 waittime )
{    	
	//memset(rx_bufferu6, 0, DATA_BUF_SIZE);
	ESP8266_printf( "%s\r\n", cmd );                              //ͨ��USART6 ����ATָ��

	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //�����������
		return true;        //����
	
	delay_ms ( waittime );                 
		 
	 while(data_lengthu6)
		{
			delay(10);		
			USART1_Send_Data(rx_bufferu6,data_lengthu6);	
			data_lengthu6 = 0;
			break;
		}	
			
	if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
		return (  strstr ( (char*)rx_bufferu6, reply1 ) || 
						  strstr ( (char*)rx_bufferu6, reply2 ) ); //����һ���ַ�������һ���ַ����еĵ�һ�γ���
 	
	else if ( reply1 != 0 )
		return (  strstr ( (char*)rx_bufferu6, reply1 ) );
	
	else
		return  (strstr ( (char*)rx_bufferu6, reply2 )) ;
}


 /**
  * @brief  ѡ��8266�Ĺ���ģʽ
  * @param  Mode:����ģʽ
  * @retval 1:ѡ��ɹ�
  *         0:ѡ��ʧ��
  */
bool ESP8266_Work_Mode_Choose (Work_ModeTypeDef Mode)
{
	switch (Mode)
	{
		case STA:
			return ESP8266_Cmd ( "AT+CWMODE=1", "OK", "no change", 1000 ); 
		
	  case AP:
		  return ESP8266_Cmd ( "AT+CWMODE=2", "OK", "no change", 1000 ); 
		
		case STA_AP:
		  return ESP8266_Cmd ( "AT+CWMODE=3", "OK", "no change", 1000 ); 
		
	  default:
		  return false;
  }
	
}
/**
  * @brief  STAģʽ�µ�tcpclient����
  * @param  None
  * @retval None
  */
void ESP8266_STA_TCP_Client()
{ 
	 PC_printf("\r\n��Ҫ���еĲ����ǣ�STAģʽ-TCP Client\r\n");
	
   if(!ESP8266_Cmd ( "AT+RST","OK", "ready", 2000 ))//ָ��ͳ�
		PC_printf("��λָ�����,��������·���\r\n");
	
	
	 if(!ESP8266_Cmd ( "AT+CWMODE=1", "OK", NULL, 500 ))//����ģʽESP8266_Work_Mode_Choose (STA)
     PC_printf("ģʽ����ָ�����,��������·���\r\n");
		
	PC_printf("\r\n�г���ǰ���õ���������\r\n");
	
	ESP8266_Cmd ("AT+CWLAP", "OK", NULL, 1600);
	delay_ms ( 1000 );
//	delay_ms ( 1000 );
	do
	{		
		
		//sprintf ( SSID_PASSWORD, "AT+CWJAP=\"openmcu\",\"XXXXXX\"");
		//PC_printf("\r\n�ڴ��ڵ������ַ�����������Ҫ���ӵ���������,��ʽΪ%s\r\n",SSID_PASSWORD);
	 // while(data_length==0);                        //�ȴ��û�����Ҫ���ӵ�SSID
		 //PC_printf("\r\n��������,���Ե�...\r\n");
		 //delay(10);		
		//USART6_Send_Data(rx_buffer,data_length);	     
		//data_length = 0;  
		ESP8266_Cmd ("AT+CWJAP=\"wb\",\"openmcu666\"","OK",NULL , 1600);
		delay_ms ( 2000 );
		PC_printf("\r\nWiFi������\r\n");
	}while(!ESP8266_Cmd ("AT+CIFSR", "OK",NULL , 900));//��ȡ����IP
	
	 delay_ms ( 2000 );
//	 delay_ms ( 2000 );
//	 delay_ms ( 2000 );
	PC_printf("\r\nWiFi������\r\n");
//	ESP8266_Cmd ( "AT+CIFSR", "OK", NULL, 1000 );                               //�鿴ģ��IP��ַ
	ESP8266_Cmd ( "AT+CIPMUX=0", "OK", NULL, 500 );                             
	//ESP8266_Cmd ( "AT+CIPSERVER=0", "OK", NULL, 500 );//�رշ�����
	
}

/**
  * @brief  ����8266����͸��ģʽ����
  * @param  None
  * @retval None
  */
void ESP8266_TransparentSend ( void )
{
	ESP8266_Cmd ( "AT+CIPMODE=1", "OK", 0, 300 );      //����Ϊ͸��
	ESP8266_Cmd ( "AT+CIPSEND", "\r\n", ">", 300 );    //��ʼ͸��
}

/**
  * @brief  ����8266�˳�͸��ģʽ����
  * @param  None
  * @retval None
  */
void ESP8266_TransparentExit( void )
{
	ESP8266_printf("+++");
	ESP8266_Cmd ("AT", "OK", NULL, 500 );
}

/**
  * @brief  ���ӷ�����
  * @param  server:ip������;port:�������˿�
  * @retval 1:����ʧ��
  *         0:���ӳɹ�
  */
u8 ESP8266_Connect_To_Server(u8 *server,u16 port)
{
	char AT_CMD[60];
	memset(rx_bufferu6,0,DATA_BUF_SIZE);
	sprintf(AT_CMD,"AT+CIPSTART=\"TCP\",\"%s\",%d",server,port);
 if(ESP8266_Cmd (AT_CMD , "OK", NULL, 500 ))                                    //����TCP client
  //ESP8266_Cmd ( "AT+CWJAP?", "OK", NULL, 500 );                               //�鿴�Ƿ������� 
  //if(ESP8266_Cmd ( "AT+CIPSTART=\"TCP\",\"api.qrserver.com\",80", "OK", NULL, 500 ))//QRCODE�������ɽӿ�
	{
		 PC_printf("\r\n��������%s\r\n",server);
     return 0;
  }
	else
	{
	 PC_printf("\r\n����[%s]ʧ��\r\n",server);
		return 1;
	}
}

/**
  * @brief  APģʽ��tcpserver����
  * @param  None
  * @retval None
  */
void ESP8266_AP_TCP_Server (void)
{
	char SSID_PASSWORD[30];
  PC_printf("\r\n��Ҫ���еĲ����ǣ�APģʽ-TCP Server\r\n");
  ESP8266_Cmd ( "AT+RST", "OK", "ready", 2000 );

	//ESP8266_Net_Mode_Choose ( AP );
	ESP8266_Cmd( "AT+CWMODE=2", "OK", NULL, 500 );//����ģʽ
  ESP8266_Cmd( "AT+RST", "OK", "ready", 2000 );

	sprintf ( SSID_PASSWORD, "AT+CWSAP=\"openmcu\",\"XXXXXXXX\",1,3");//���볤�Ȳ�������8λ
  PC_printf("\r\n�ڴ��ڵ������ַ�����������Ҫ��������������,��ʽΪ%s\r\n",SSID_PASSWORD);
	while(data_length==0);                        //�ȴ��û�����Ҫ������SSID
	printf("\r\n���ڴ���,���Ե�...\r\n");
	delay(10);

	USART6_Send_Data(rx_buffer,data_length);	 
		
   while(!ESP8266_Cmd ((char*)rx_buffer, "OK", NULL, 500 ))
	 {  
		 data_length = 0;   
	   printf("\r\nWi-Fi����ʧ��,������������...\r\n");
	   while(data_length==0);                        //�ȴ��û�����Ҫ������SSID
	   printf("\r\n�ٴγ��Դ���,���Ե�...\r\n");
	 }

	 data_length = 0;    
	 PC_printf("\r\n�����ɹ�...\r\n");
   ESP8266_Cmd ( "AT+CIPMODE=0", "OK", NULL, 500 );//ʧ��͸��ģʽ
   ESP8266_Cmd ( "AT+CIPMUX=1", "OK", NULL, 500 );//����������
   ESP8266_Cmd ( "AT+CIPSERVER=1,8088", "OK", NULL, 500 );//����������
  

	PC_printf( "\r\n���ڲ�ѯESP8266ģ��IP...\r\n" );
	ESP8266_Cmd ( "AT+CIFSR", "OK", NULL, 500 );
		
	PC_printf ( "\r\n��PC���ֻ����ӸղŴ�����Wi-Fi,�������������,��TCP Client���Ӹղſ����ķ�����(AP IP)...\r\n" );

	PC_printf( "\r\n������������ַ������������ַ�,�������\r\n" );

}
