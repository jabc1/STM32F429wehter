/**
  * @file    formatjson.c 
  * @author  WB R&D Team - openmcu666
  * @version V0.1
  * @date    2018.11.03
  * @brief   Weather interface
  */
#include "formatjson.h"
#include "stm32f429i_lcd.h"
#include "uni.h"
#include "esp_function.h"
#include <stdlib.h>
 
extern unsigned char gImage_wifi_full[704];
extern unsigned char gImage_overcast[20000] ;
extern unsigned char gImage_sun[20000];
extern unsigned char gImage_cloudy[20000];
extern unsigned char gImage_unknown[20000];
//��ȡʵʱ����������
//u8 GET_DATA_NOW[]={"GET https://api.seniverse.com/v3/weather/now.json?key=xxxxxxxxxxxx&location=shenzhen&language=zh-Hans&unit=c\r\n"};
u8 GET_DATA_7DAY[]={"GET http://api.yytianqi.com/forecast7d?city=CH280601&key=xxxxxxxxxxxx\r\n"};
u8 GET_DATA_NOW[]={"GET http://api.yytianqi.com/observe?city=CH280601&key=xxxxxxxxxxx\r\n"};

//u8 GET_DATA[]={"GET https://free-api.heweather.com/s6/weather/lifestyle?location=shenzhen&key=XXXXXXXXX\n\n"};
u8 GET_DATA_QRCODE[]={"GET https://api.qrserver.com/v1/create-qr-code/?size=50x50&data=http://www.openmcu.com\r\n"};
//��ά�����ɽӿ�

void Weather_UI_Init(void)
{		
	LCD_SetTextColor(WHITE);
	LCD_DrawFullRect(110, 45, 2, 32);
	LCD_DrawFullRect(0, 136, 479, 2);
	
	LCD_DrawPicture(230,30,100, 100,gImage_unknown);
	LCD_DisplayStr(340,30,"����:",WHITE,BLACK,size16x16);
	LCD_DisplayStr(340,55,"�¶�:",WHITE,BLACK,size16x16);
  LCD_DisplayStr(397,55,"��",WHITE,BLACK,size16x16);
	LCD_DisplayStr(340,80,"����:",WHITE,BLACK,size16x16);
	LCD_DisplayStr(340,105,"����:",WHITE,BLACK,size16x16);
  LCD_DrawPicture(455,0,16, 22,gImage_wifi_full);
  
	LCD_DisplayStr(80,180,"��������Ԥ��",WHITE,BLACK,size16x16);
	
	LCD_DrawPicture(230,156,100, 100,gImage_unknown);
	LCD_DisplayStr(340,156,"����:",WHITE,BLACK,size16x16);
	LCD_DisplayStr(340,180,"�¶�:",WHITE,BLACK,size16x16);
  LCD_DisplayStr(397,180,"��",WHITE,BLACK,size16x16);
	LCD_DisplayStr(340,205,"����:",WHITE,BLACK,size16x16);
	LCD_DisplayStr(340,235,"����:",WHITE,BLACK,size16x16);
}

//��������ͼ��
void Weather_Updata_Icon(u8 *code,u8 time)
{
	int num;
	num=atoi(code);
  switch(num)         //�����������YY��������  http://www.yytianqi.com/weather.html
	{
		case 0://��
			   if(time==0)LCD_DrawPicture(230,30,100, 100,gImage_sun);   //��������
			   else LCD_DrawPicture(230,156,100, 100,gImage_sun);           //��������
		     break;
		case 1: //����
			   if(time==0)LCD_DrawPicture(230,30,100, 100,gImage_cloudy);
			   else LCD_DrawPicture(230,156,100, 100,gImage_cloudy);   
		     break;
		case 2://��
			   if(time==0)LCD_DrawPicture(230,30,100, 100,gImage_overcast);
			    else LCD_DrawPicture(230,156,100, 100,gImage_overcast);   
		      break;
	  case 3://����
		break;
		case 4://������
		break;
		case 7://С��
		break;
		case 8: //����
		break;
		case 9://����
		break;
	  case 10://����
		break;
		case 11://����
		break;
		case 12://�ش���
			   break;
	  default:
		  printf("\r\nϵͳδ�������������,�뼰ʱ����\r\n");
		   if(time==0)LCD_DrawPicture(230,30,100, 100,gImage_unknown);
			    else LCD_DrawPicture(230,156,100, 100,gImage_unknown);   
		break;
	
	}

}
//��ȡʵʱ������Ϣ
void Get_Weather_Info(u8 *buf,Get_Type type)
{	
	cJSON *root,*Sub,*arrayItem;
	cJSON *Item,*SubItem,*ChildItem;	
	cJSON *LastItem;
  char *pr,*utf8;
	u8 gbk[10];
  u8 size = 0,i=0;
	printf("\r\n%s\r\n",buf);
  root = cJSON_Parse((const char*)buf);
	if(root != NULL)
	{
		Sub = cJSON_GetObjectItem(root,"results");
		if(Sub != NULL)
		{
			arrayItem = cJSON_GetArrayItem(Sub,0);
			pr = cJSON_Print(arrayItem);
			Item = cJSON_Parse(pr);
			if(Item != NULL)
			{
				SubItem = cJSON_GetObjectItem(Item,"location");
				if(SubItem != NULL)
				{
					ChildItem = cJSON_GetObjectItem(SubItem,"name");  //��������
					if(ChildItem != NULL)
					{
						utf8 = ChildItem->valuestring;
						SwitchToGbk((const u8*)utf8,strlen(utf8),(u8 *)gbk);
						LCD_DisplayStr(50,50,gbk,WHITE,BLACK,size24x24);
						printf("\r\nname=%s\r\n",gbk);
					}
				}
        if(type==WEATHER_NOW)      //ʵʱ����
				{	
					  SubItem = cJSON_GetObjectItem(Item,"now");
						if(SubItem != NULL)
						{
							ChildItem = cJSON_GetObjectItem(SubItem,"text");  //������Ϣ
							if(ChildItem != NULL)
							{
								utf8 = ChildItem->valuestring;
								SwitchToGbk((const u8*)utf8,strlen(utf8),(u8 *)gbk);
								LCD_DisplayStr(388,50,gbk,WHITE,BLACK,size16x16);
								printf("\r\ntext=%s\r\n",gbk);
							}
						
							ChildItem = cJSON_GetObjectItem(SubItem,"code");
							if(ChildItem != NULL)
							{
								//gbkstr = ChildItem->valuestring;
								//show_weather_icon((u8 *)gbkstr,0);
							}
					
							ChildItem = cJSON_GetObjectItem(SubItem,"temperature");
							if(ChildItem != NULL)
							{
								 utf8 = ChildItem->valuestring;
								//temperature = str2int((u8 *)gbkstr);
							//	gui_show_num(140,22,2,WHITE,54,temperature,0x80);
								LCD_DisplayStr(260,55,(u8*)utf8,WHITE,BLACK,size24x24);
								printf("\r\n�¶� = %s\r\n",utf8);
							}
						}
					}
				else if(type==WEATHER_7DAY)  //δ������
        {
				  SubItem = cJSON_GetObjectItem(Item,"daily");
				  if(SubItem != NULL)
					{
						size = cJSON_GetArraySize(SubItem);
					  for(i=0;i<size;i++)
					  {
							  if(i==3)break;
								arrayItem = cJSON_GetArrayItem(SubItem,i);
								pr = cJSON_Print(arrayItem);
								LastItem = cJSON_Parse(pr);
								if(LastItem != NULL)
								{
									if(i==0)
									{
										ChildItem =  cJSON_GetObjectItem(LastItem,"wind_direction");
										utf8 = ChildItem->valuestring;
										SwitchToGbk((const u8*)utf8,strlen(utf8),(u8 *)gbk);
										//LCD_Fill(220,45,320,61,BLACK);
										//Show_Str(220,45,lcddev.width,lcddev.height,(u8 *)gbkstr,16,0);
									  printf("\r\nwind_direction=%s\r\n",gbk);
										ChildItem =  cJSON_GetObjectItem(LastItem,"wind_scale");
										utf8 = ChildItem->valuestring;
										//LCD_ShowString(220,65,20,20,16,(u8 *)gbk);
										 printf("\r\nwind_scale=%s\r\n",utf8);
									 
										ChildItem =  cJSON_GetObjectItem(LastItem,"wind_speed");
										utf8 = ChildItem->valuestring;
										printf("\r\nwind_speed=%s\r\n",utf8);
										//LCD_ShowxNum(260,85,str2int((u8 *)gbkstr),2,16,0x80);
		//							LCD_ShowString(260,85,20,20,16,(u8 *)gbkstr);
									}
									
									ChildItem =  cJSON_GetObjectItem(LastItem,"high");
									utf8= ChildItem->valuestring;
								//	LCD_ShowxNum(30+110*i,130,str2int((u8 *)gbkstr),2,12,0x80);
		//							LCD_ShowString(30+110*i,130,20,20,12,(u8 *)gbkstr);
									printf("\r\nhigh=%s\r\n",utf8);
									
									ChildItem =  cJSON_GetObjectItem(LastItem,"low");
									utf8 = ChildItem->valuestring;
									//LCD_ShowxNum(48+110*i,130,str2int((u8 *)gbkstr),2,12,0x80);
	                printf("\r\nlow=%s\r\n",utf8);
									
									ChildItem =  cJSON_GetObjectItem(LastItem,"code_day");												
									utf8 = ChildItem->valuestring;
									 printf("\r\ncode_day=%s\r\n",utf8);
									//show_weather_icon((u8 *)gbkstr,i+1);
																
								}
								cJSON_Delete(LastItem);
					  }
				
				}
			}
			cJSON_Delete(Item);
		}
	}
	cJSON_Delete(root);
}
else {printf("\r\nroot==NULL\r\n");}
}


 
//��ȡʵʱ������Ϣ
void Get_Weather_Now(u8 *buf)
{	
	cJSON *root,*Sub,*arrayItem;
	cJSON *Item,*SubItem,*ChildItem;
	cJSON *LastItem;
  char *pr,*utf8;
	u8 gbk[10];
	u8 size = 0;
	u8 i;
	printf("\r\n%s\r\n",buf);

  root = cJSON_Parse((const char*)buf);
	if(root != NULL)
	{
		Sub=cJSON_GetObjectItem(root,"msg");
		if(Sub != NULL)
		{
		  SwitchToGbk((const u8*)Sub->valuestring,strlen(Sub->valuestring),(u8 *)gbk);
			printf("��Ϣ״̬=%s\r\n",gbk);
		}
		Sub=cJSON_GetObjectItem(root,"counts");
		if(Sub != NULL)
		{
		  //SwitchToGbk((const u8*)Sub->valuedouble,strlen(Sub->valuedouble),(u8 *)gbk);
			printf("ʣ����ʴ���=%d\r\n",(char)Sub->valuedouble);
		}
		Sub = cJSON_GetObjectItem(root,"data");
		if(Sub != NULL)
		{
			//arrayItem = cJSON_GetArrayItem(Sub,0);
			//pr = cJSON_Print(arrayItem);
			//Item = cJSON_Parse("cityName");
			Item=cJSON_GetObjectItem(Sub,"cityName");
			if(Item != NULL)
			{
				SwitchToGbk((const u8*)Item->valuestring,strlen(Item->valuestring),(u8 *)gbk);
				printf("cityName=%s\r\n",gbk);
				Item=cJSON_GetObjectItem(Sub,"tq");
				if(Item != NULL)
				{
				  SwitchToGbk((const u8*)Item->valuestring,strlen(Item->valuestring),(u8 *)gbk);
				  printf("����=%s\r\n",gbk);
				}
				Item=cJSON_GetObjectItem(Sub,"qw");
				if(Item != NULL)
				{
				  SwitchToGbk((const u8*)Item->valuestring,strlen(Item->valuestring),(u8 *)gbk);
				  printf("�¶�=%s��\r\n",gbk);
				}
				Item=cJSON_GetObjectItem(Sub,"sd");
				if(Item != NULL)
				{
				  SwitchToGbk((const u8*)Item->valuestring,strlen(Item->valuestring),(u8 *)gbk);
				  printf("ʪ��=%s%%\r\n",gbk);
				}
				Item=cJSON_GetObjectItem(Sub,"fl");
				if(Item != NULL)
				{
				  SwitchToGbk((const u8*)Item->valuestring,strlen(Item->valuestring),(u8 *)gbk);
				  printf("����=%s\r\n",gbk);
				}
				Item=cJSON_GetObjectItem(Sub,"fx");
				if(Item != NULL)
				{
				  SwitchToGbk((const u8*)Item->valuestring,strlen(Item->valuestring),(u8 *)gbk);
				  printf("����=%s\r\n",gbk);
				}
				Item=cJSON_GetObjectItem(Sub,"lastUpdate");
				if(Item != NULL)
				{
				  SwitchToGbk((const u8*)Item->valuestring,strlen(Item->valuestring),(u8 *)gbk);
				  printf("����ʱ��=%s\r\n",gbk);
				}
			}
			cJSON_Delete(Item);
		}
	}
	cJSON_Delete(root);
}

//��ȡ7��������Ϣ
//����û�ֻ�ܻ�ȡ2���������Ϣ,ÿСʱ30�εķ�����.
void Get_Weather_7Day(u8 *buf)
{	
	cJSON *root,*Sub,*arrayItem;
	cJSON *Item,*SubItem,*ChildItem;
  char *pr,*utf8;
	u8 gbkcode[12];
	u8 size = 0,i;
	char *status="Sucess";
	//printf("\r\n%s\r\n",buf);

  root = cJSON_Parse((const char*)buf);
	if(root != NULL)
	{
		Sub=cJSON_GetObjectItem(root,"msg");
		if(*status == *(Sub->valuestring))
		{
		 // SwitchToGbk((const u8*)Sub->valuestring,strlen(Sub->valuestring),(u8 *)gbk);
			printf("��Ϣ״̬=%s\r\n",Sub->valuestring);
		 
		  Sub=cJSON_GetObjectItem(root,"counts");
		if(Sub != NULL)
		{
		  //SwitchToGbk((const u8*)Sub->valuedouble,strlen(Sub->valuedouble),(u8 *)gbk);
			printf("ʣ����ʴ���=%d\r\n",(char)Sub->valuedouble);
		}
		Sub = cJSON_GetObjectItem(root,"data");
		if(Sub != NULL)
		{
			Item=cJSON_GetObjectItem(Sub,"cityName");
			if(Item != NULL)
			{
				SwitchToGbk((const u8*)Item->valuestring,strlen(Item->valuestring),gbkcode);
				printf("cityName=%s\r\n",gbkcode);
				LCD_DisplayStr(50,50,gbkcode,WHITE,BLACK,size24x24);
			}
				Item=cJSON_GetObjectItem(Sub,"sj");//���ݸ���ʱ��
				if(Item != NULL)
				{
				  //SwitchToGbk((const u8*)Item->valuestring,strlen(Item->valuestring),(u8 *)gbk);
				  printf("���ݸ���ʱ��=%s\r\n",Item->valuestring);
					memcpy(gbkcode,(u8*)Item->valuestring,10);
					gbkcode[10]='\0';
					LCD_DisplayStr(130,45,gbkcode,WHITE,BLACK,size16x16);
					
					Item->valuestring+=11;
					memcpy(gbkcode,(u8*)Item->valuestring,5);
				  gbkcode[5]='\0';
					LCD_DisplayStr(130,65,gbkcode,WHITE,BLACK,size16x16);
					LCD_DisplayStr(175,63,"����",WHITE,BLACK,size16x16);
				}
				
        Item=cJSON_GetObjectItem(Sub,"list"); 
				size = cJSON_GetArraySize(Item);
				//printf("\r\nsize=%d\r\n",size);
        for(i=0;i<size;i++)
		  	{
			    arrayItem = cJSON_GetArrayItem(Item,i);
					pr = cJSON_Print(arrayItem);
			    SubItem = cJSON_Parse(pr);
			    if(SubItem != NULL)
				  {
							ChildItem = cJSON_GetObjectItem(SubItem,"tq1");//��������
							SwitchToGbk((const u8*)ChildItem->valuestring,strlen(ChildItem->valuestring),gbkcode);
							//printf("��������=%s\r\n",gbkcode);
						  if(i==0) LCD_DisplayStr(380,30,gbkcode,WHITE,BLACK,size16x16);//��������
							else 		LCD_DisplayStr(380,156,gbkcode,WHITE,BLACK,size16x16);//��������
						  
						  ChildItem = cJSON_GetObjectItem(SubItem,"tq2");//ҹ������
							//SwitchToGbk((const u8*)ChildItem->valuestring,strlen(ChildItem->valuestring),gbkcode);
							//printf("ҹ������=%s\r\n",gbkcode);
							
							ChildItem = cJSON_GetObjectItem(SubItem,"qw1");//��������
							//SwitchToGbk((const u8*)ChildItem->valuestring,strlen(ChildItem->valuestring),gbkcode);
							//printf("��������=%s\r\n",ChildItem->valuestring);
						  
						   if(i==0) LCD_DisplayStr(380,55,(u8*)ChildItem->valuestring,WHITE,BLACK,size16x16);
					   	else	LCD_DisplayStr(380,180,(u8*)ChildItem->valuestring,WHITE,BLACK,size16x16);
								
						  ChildItem = cJSON_GetObjectItem(SubItem,"qw2");//ҹ������
							//SwitchToGbk((const u8*)ChildItem->valuestring,strlen(ChildItem->valuestring),(u8 *)gbk);
							//printf("ҹ������=%s\r\n",ChildItem->valuestring);
							
							ChildItem = cJSON_GetObjectItem(SubItem,"fl1");//�������
							SwitchToGbk((const u8*)ChildItem->valuestring,strlen(ChildItem->valuestring),gbkcode);
							//printf("�������=%s\r\n",gbkcode);
						  if(i==0) LCD_DisplayStr(380,80,gbkcode,WHITE,BLACK,size16x16);
						  else LCD_DisplayStr(380,205,gbkcode,WHITE,BLACK,size16x16);
						
							ChildItem = cJSON_GetObjectItem(SubItem,"fl2");//ҹ�����
							//SwitchToGbk((const u8*)ChildItem->valuestring,strlen(ChildItem->valuestring),gbkcode);
							//printf("ҹ�����=%s\r\n",gbkcode);
							
							ChildItem = cJSON_GetObjectItem(SubItem,"fx1");//�������
							SwitchToGbk((const u8*)ChildItem->valuestring,strlen(ChildItem->valuestring),gbkcode);
							//printf("�������=%s\r\n",gbk);
							if(i==0) LCD_DisplayStr(380,105,gbkcode,WHITE,BLACK,size16x16);
							else LCD_DisplayStr(380,235,gbkcode,WHITE,BLACK,size16x16);
							
							ChildItem = cJSON_GetObjectItem(SubItem,"fx2");//ҹ�����
							//SwitchToGbk((const u8*)ChildItem->valuestring,strlen(ChildItem->valuestring),gbkcode);
							//printf("ҹ�����=%s\r\n",gbkcode);
							
							ChildItem = cJSON_GetObjectItem(SubItem,"date");//Ԥ��ʱ��
							//SwitchToGbk((const u8*)ChildItem->valuestring,strlen(ChildItem->valuestring),(u8 *)gbk);
							//printf("Ԥ������=%s\r\n",ChildItem->valuestring);
							//
							if(i==0)LCD_DisplayStr(80,90,(u8*)ChildItem->valuestring,WHITE,BLACK,size16x16);
								else LCD_DisplayStr(80,205,(u8*)ChildItem->valuestring,WHITE,BLACK,size16x16);
								
							ChildItem = cJSON_GetObjectItem(SubItem,"numtq1");//������������,�������
					    Weather_Updata_Icon((u8*)ChildItem->valuestring,i);
					}
				 cJSON_Delete(SubItem);
		   }
		 }
	 }
		else printf("��������ʧ��=%s\r\n",Sub->valuestring);
	}
	cJSON_Delete(root);
}

//ͨ��GET������������
void Get_Data(Get_Type type)
{
	ESP8266_TransparentSend();//����Ϊ͸��,��ʼ������
	data_lengthu6=0;
	memset(rx_bufferu6,0,DATA_BUF_SIZE);
	switch(type)
	{
	  case WEATHER_NOW :
			USART6_SendString(GET_DATA_NOW);	
			break;
		 case WEATHER_7DAY :
			 USART6_SendString(GET_DATA_7DAY);	
			break;
		  case QR_CODE :
				USART6_SendString(GET_DATA_QRCODE);	
			break;
	}
	 delay(80);
	  while(data_lengthu6) //�ȴ����ؽ��
		//while(USART_GetFlagStatus(USART6, USART_FLAG_IDLE) == RESET)
	  {
			delay(10);	
      // printf("\r\nReceive data\r\n");			
			USART1_Send_Data(rx_bufferu6,data_lengthu6);	//ת���������ݵĸ�ʽ(utf-8 bgk)
		//	printf("\r\n[%s]\r\n",rx_bufferu6);
			//printf("\r\nReceive data[%d]\r\n",data_lengthu6);
			data_lengthu6 = 0;
			Get_Weather_7Day(rx_bufferu6);
			break;
	  }
//		ESP8266_TransparentExit();
//		ESP8266_Cmd ("AT+CIPCLOSE", "OK", NULL, 500 );//�ر�����
}
