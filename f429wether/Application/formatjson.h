#ifndef __FORMATJSON_H
#define __FORMATJSON_H
#include <stm32f4xx.h>
#include "stdio.h"
#include "cJSON.h"
#include "string.h"

#define API_WEATHER              "api.yytianqi.com" //api.seniverse.com
#define API_QRCODE               "api.qrserver.com"

typedef enum
{
  WEATHER_NOW=0,
  WEATHER_7DAY,
  QR_CODE,
}Get_Type;

void Weather_UI_Init(void);
void Get_Weather_Now(u8 *buf);
void Get_Weather_Info(u8 *buf,Get_Type type);
void Get_Weather_7Day(u8 *buf);
void Get_Data(Get_Type type);
#endif
