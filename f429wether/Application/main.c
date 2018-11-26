/**
  * @file    main.c 
  * @author  WB R&D Team - openmcu666
  * @version V0.1
  * @date    2018.11.03
  * @brief   Main Program body
  */
#include "stm32f4xx.h"
#include "Gpio.h"
#include "usart.h"
#include "delay.h"
#include "stm32f429i_lcd.h"
#include "esp_function.h"
#include "cJSON.h"
#include "uni.h"
#include "formatjson.h"
void Delay(uint32_t Time)
{
    uint32_t i;
    
    i = 0;
    while (Time--) 
		{
       for (i = 0; i < 5000; i++);
    }
}

	
extern unsigned char gImage_wifi_full[704];
extern unsigned char gImage_sun[20000];//48x48
extern unsigned char gImage_duoyun[20000];
u8 test[]={"{\"code\":1,\"msg\":\"Sucess\",\"counts\":26,\"data\":{\"cityId\":\"CH280601\",\
\"cityName\":\"\\u6df1\\u5733\",\"lastUpdate\":\"2018-11-01 11:01:12\",\"tq\":\"\\u591a\\u4e91\"\
,\"numtq\":\"01\",\"qw\":\"24\",\"numfl\":3,\"fl\":\"5-6\\u7ea7\",\"fx\":\
\"\\u4e1c\\u5317\\u98ce\",\"numfx\":\"1\",\"sd\":\"36\"}}"};


u8 test3[]={"{\"code\":1,\"msg\":\"Sucess\",\"counts\":29,\"data\":{\"cityId\":\"CH280601\",\
\"cityName\":\"\\u6df1\\u5733\",\"sj\":\"2018-11-01 14:00:00\",\"list\":[{\"tq2\":\"\\u591a\\u4e91\",\
\"tq1\":\"\\u591a\\u4e91\",\"numtq1\":\"01\",\"numtq2\":\"01\",\"qw1\":\"26\",\"qw2\":\"22\",\"fl1\":\
\"3-4\\u7ea7\",\"fl2\":\"3-4\\u7ea7\",\"numfl1\":\"1\",\"numfl2\":\"1\",\"fx1\":\"\\u4e1c\\u5317\\u98ce\",\
\"fx2\":\"\\u4e1c\\u5317\\u98ce\",\"numfx1\":\"1\",\"numfx2\":\"1\",\"date\":\"2018-11-01\"},{\"tq2\":\"\
\\u9634\",\"tq1\":\"\\u9634\",\"numtq1\":\"02\",\"numtq2\":\"02\",\"qw1\":\"26\",\"qw2\":\"20\",\"fl1\":\
\"3-4\\u7ea7\",\"fl2\":\"3-4\\u7ea7\",\"numfl1\":\"1\",\"numfl2\":\"1\",\"fx1\":\"\\u4e1c\\u5317\\u98ce\",\
\"fx2\":\"\\u4e1c\\u5317\\u98ce\",\"numfx1\":\"1\",\"numfx2\":\"1\",\"date\":\"2018-11-02\"}]}}"};
/*****************************************************************************
**   Main Function  main()
******************************************************************************/
//struct record {const char *precision;double lat,lon;const char *address,*city,*state,*zip,*country; };
//extern u16 buf[DATA_BUF_SIZE];
//extern char bgk_buf[DATA_BUF_SIZE];
int main(void)
{ 
	USART1_Init();
  LED_Init();
	LCD_Init(); 
	LCD_LayerInit();
	LTDC_Cmd(ENABLE);
	LCD_SetLayer(LCD_FOREGROUND_LAYER); //使能前景层
	LCD_Clear(BLACK);
 
	printf("\r\n");
	printf("Hello Welcome.\r\n");
	printf("Thank You For Choosing Our Products.\r\n");
	printf("Thank You Very Much.\r\n");
	printf("This Example display chinese.\r\n");
	printf("\r\n");
	printf("ltdc Initialization...\r\n");
 		
	printf("Ok,Let's Go...\r\n");
  LCD_DrawFullRect(0, 0, 480, 16);
	LCD_DisplayStr(0,0,"ESP8266 WiFi Weather",WHITE,BLUE,size16x16);	
  Weather_UI_Init();
	LCD_DisplayStr(136,110,"WiFi 连接中",WHITE,BLACK,size16x16); 
	
#if 0	
	root=cJSON_CreateArray();
	for (i=0;i<2;i++)
	{
		cJSON_AddItemToArray(root,fld=cJSON_CreateObject());
		cJSON_AddStringToObject(fld, "precision", fields[i].precision);
		cJSON_AddNumberToObject(fld, "Latitude", fields[i].lat);
		cJSON_AddNumberToObject(fld, "Longitude", fields[i].lon);
		cJSON_AddStringToObject(fld, "Address", fields[i].address);
		cJSON_AddStringToObject(fld, "City", fields[i].city);
		cJSON_AddStringToObject(fld, "State", fields[i].state);
		cJSON_AddStringToObject(fld, "Zip", fields[i].zip);
		cJSON_AddStringToObject(fld, "Country", fields[i].country);
	}
	
	out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s",out);	free(out);
	
	for(;;)
	{
		
	}
#endif
   

#if 1	
  ESP8266_Init();     
  ESP8266_STA_TCP_Client();
	if(ESP8266_Connect_To_Server((u8*)API_WEATHER,80)==0)
	{
		Get_Data(WEATHER_7DAY);
	}
#endif
	LCD_DisplayStr(136,110,"           ",WHITE,BLACK,size16x16); 
	
  

#if 0
  Get_Weather_7Day(test3);
	while(1){;}
#endif
	while(1)
	{	
		while(data_lengthu6)
		{
			delay(10);		
			//USART1_Send_Data(rx_bufferu6,data_lengthu6);	
			//Get_Weather_Info((u8*)rx_bufferu6);
			data_lengthu6 = 0;
			break;
		}	
	}
	//                                    
	
}

	



