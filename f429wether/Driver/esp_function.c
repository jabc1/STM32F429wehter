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
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;            //推挽输出
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
  * @brief  重启8266模块
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
  * @brief  发送AT指令
  * @param  cmd:待发送的指令
  *         reply1,reply2:期待的响应,若无需返回,填入NULL
  *         waittime:等待响应的时间(注意指令发送间隔不能过短,否则容易出现busy)
  * @retval 0:指令发送失败 
  *         1:指令发送成功
  */
bool ESP8266_Cmd ( char * cmd, char * reply1, char * reply2, u32 waittime )
{    	
	//memset(rx_bufferu6, 0, DATA_BUF_SIZE);
	ESP8266_printf( "%s\r\n", cmd );                              //通过USART6 发送AT指令

	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //无需接收数据
		return true;        //非零
	
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
						  strstr ( (char*)rx_bufferu6, reply2 ) ); //搜索一个字符串在另一个字符串中的第一次出现
 	
	else if ( reply1 != 0 )
		return (  strstr ( (char*)rx_bufferu6, reply1 ) );
	
	else
		return  (strstr ( (char*)rx_bufferu6, reply2 )) ;
}


 /**
  * @brief  选择8266的工作模式
  * @param  Mode:工作模式
  * @retval 1:选择成功
  *         0:选择失败
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
  * @brief  STA模式下的tcpclient测试
  * @param  None
  * @retval None
  */
void ESP8266_STA_TCP_Client()
{ 
	 PC_printf("\r\n将要进行的测试是：STA模式-TCP Client\r\n");
	
   if(!ESP8266_Cmd ( "AT+RST","OK", "ready", 2000 ))//指令发送成
		PC_printf("复位指令错误,请检查后重新发送\r\n");
	
	
	 if(!ESP8266_Cmd ( "AT+CWMODE=1", "OK", NULL, 500 ))//设置模式ESP8266_Work_Mode_Choose (STA)
     PC_printf("模式设置指令错误,请检查后重新发送\r\n");
		
	PC_printf("\r\n列出当前可用的无线网络\r\n");
	
	ESP8266_Cmd ("AT+CWLAP", "OK", NULL, 1600);
	delay_ms ( 1000 );
//	delay_ms ( 1000 );
	do
	{		
		
		//sprintf ( SSID_PASSWORD, "AT+CWJAP=\"openmcu\",\"XXXXXX\"");
		//PC_printf("\r\n在串口调试助手发送栏里输入要连接的无线网络,格式为%s\r\n",SSID_PASSWORD);
	 // while(data_length==0);                        //等待用户输入要连接的SSID
		 //PC_printf("\r\n正在连接,请稍等...\r\n");
		 //delay(10);		
		//USART6_Send_Data(rx_buffer,data_length);	     
		//data_length = 0;  
		ESP8266_Cmd ("AT+CWJAP=\"wb\",\"openmcu666\"","OK",NULL , 1600);
		delay_ms ( 2000 );
		PC_printf("\r\nWiFi连接中\r\n");
	}while(!ESP8266_Cmd ("AT+CIFSR", "OK",NULL , 900));//获取本地IP
	
	 delay_ms ( 2000 );
//	 delay_ms ( 2000 );
//	 delay_ms ( 2000 );
	PC_printf("\r\nWiFi已连接\r\n");
//	ESP8266_Cmd ( "AT+CIFSR", "OK", NULL, 1000 );                               //查看模块IP地址
	ESP8266_Cmd ( "AT+CIPMUX=0", "OK", NULL, 500 );                             
	//ESP8266_Cmd ( "AT+CIPSERVER=0", "OK", NULL, 500 );//关闭服务器
	
}

/**
  * @brief  配置8266进入透传模式发送
  * @param  None
  * @retval None
  */
void ESP8266_TransparentSend ( void )
{
	ESP8266_Cmd ( "AT+CIPMODE=1", "OK", 0, 300 );      //设置为透传
	ESP8266_Cmd ( "AT+CIPSEND", "\r\n", ">", 300 );    //开始透传
}

/**
  * @brief  配置8266退出透传模式发送
  * @param  None
  * @retval None
  */
void ESP8266_TransparentExit( void )
{
	ESP8266_printf("+++");
	ESP8266_Cmd ("AT", "OK", NULL, 500 );
}

/**
  * @brief  连接服务器
  * @param  server:ip或域名;port:服务器端口
  * @retval 1:连接失败
  *         0:连接成功
  */
u8 ESP8266_Connect_To_Server(u8 *server,u16 port)
{
	char AT_CMD[60];
	memset(rx_bufferu6,0,DATA_BUF_SIZE);
	sprintf(AT_CMD,"AT+CIPSTART=\"TCP\",\"%s\",%d",server,port);
 if(ESP8266_Cmd (AT_CMD , "OK", NULL, 500 ))                                    //创建TCP client
  //ESP8266_Cmd ( "AT+CWJAP?", "OK", NULL, 500 );                               //查看是否已连接 
  //if(ESP8266_Cmd ( "AT+CIPSTART=\"TCP\",\"api.qrserver.com\",80", "OK", NULL, 500 ))//QRCODE在线生成接口
	{
		 PC_printf("\r\n已连接至%s\r\n",server);
     return 0;
  }
	else
	{
	 PC_printf("\r\n连接[%s]失败\r\n",server);
		return 1;
	}
}

/**
  * @brief  AP模式下tcpserver测试
  * @param  None
  * @retval None
  */
void ESP8266_AP_TCP_Server (void)
{
	char SSID_PASSWORD[30];
  PC_printf("\r\n将要进行的测试是：AP模式-TCP Server\r\n");
  ESP8266_Cmd ( "AT+RST", "OK", "ready", 2000 );

	//ESP8266_Net_Mode_Choose ( AP );
	ESP8266_Cmd( "AT+CWMODE=2", "OK", NULL, 500 );//设置模式
  ESP8266_Cmd( "AT+RST", "OK", "ready", 2000 );

	sprintf ( SSID_PASSWORD, "AT+CWSAP=\"openmcu\",\"XXXXXXXX\",1,3");//密码长度不能少于8位
  PC_printf("\r\n在串口调试助手发送栏里输入要创建的无线网络,格式为%s\r\n",SSID_PASSWORD);
	while(data_length==0);                        //等待用户输入要创建的SSID
	printf("\r\n正在创建,请稍等...\r\n");
	delay(10);

	USART6_Send_Data(rx_buffer,data_length);	 
		
   while(!ESP8266_Cmd ((char*)rx_buffer, "OK", NULL, 500 ))
	 {  
		 data_length = 0;   
	   printf("\r\nWi-Fi创建失败,检查后重新输入...\r\n");
	   while(data_length==0);                        //等待用户输入要创建的SSID
	   printf("\r\n再次尝试创建,请稍等...\r\n");
	 }

	 data_length = 0;    
	 PC_printf("\r\n创建成功...\r\n");
   ESP8266_Cmd ( "AT+CIPMODE=0", "OK", NULL, 500 );//失能透传模式
   ESP8266_Cmd ( "AT+CIPMUX=1", "OK", NULL, 500 );//开启多连接
   ESP8266_Cmd ( "AT+CIPSERVER=1,8088", "OK", NULL, 500 );//创建服务器
  

	PC_printf( "\r\n正在查询ESP8266模块IP...\r\n" );
	ESP8266_Cmd ( "AT+CIFSR", "OK", NULL, 500 );
		
	PC_printf ( "\r\n用PC或手机连接刚才创建的Wi-Fi,打开网络调试助手,以TCP Client连接刚才开启的服务器(AP IP)...\r\n" );

	PC_printf( "\r\n在网络调试助手发送栏里输入字符,点击发送\r\n" );

}
