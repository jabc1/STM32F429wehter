/**
  * @file    fonts_hz16.c 
  * @author  WB R&D Team - openmcu666
  * @version V0.1
  * @date    2015.9.9
  * @brief   16x16����ģ(����-����-С��)
  */
#include "fonts.h"

const FNT_GB16 Chinese16x16_Table[] = {
	"��",
	0x00,0x00,0x31,0xFC,0x31,0xFC,0x60,0x30,0x6C,0x30,0xFC,0x30,0xF8,0x30,0x18,0x30,
  0x30,0x30,0x7C,0x30,0x7C,0x30,0x00,0x30,0x7D,0xFE,0xF1,0xFE,0x00,0x00,0x00,0x00,
	
	"��",
  0x03,0x00,0x03,0x60,0x03,0x30,0x03,0x10,0x7F,0xFC,0x7F,0xFC,0x06,0xC0,0x06,0xD8,
  0x06,0xD8,0x0C,0xF0,0x0C,0xE0,0x18,0xC0,0x31,0xC6,0x67,0xFE,0x42,0x7C,0x00,0x00,
	
	"��",
	0x00,0x00,0x7F,0xFC,0x7F,0xFC,0x0C,0x60,0x0C,0x60,0x0C,0x60,0xFF,0xFE,0xFF,0xFE,
  0x0C,0x60,0x0C,0x60,0x0C,0x60,0x18,0x60,0x18,0x60,0x70,0x60,0x20,0x60,0x00,0x00,
	
	"��",
	0x03,0x00,0x33,0x30,0x33,0x18,0x33,0x00,0x7F,0xFC,0x7F,0xFC,0x06,0x00,0x07,0xF8,
  0x0F,0xF8,0x1A,0x30,0x33,0x60,0x61,0xC0,0x43,0xE0,0x1E,0x3E,0x18,0x0E,0x00,0x00,
	
	"��",
	0x30,0x00,0x30,0x3C,0x33,0xF0,0xFF,0x00,0xFF,0xFC,0x33,0xFC,0x33,0x6C,0x7B,0x6C,
  0x7F,0x6C,0xB7,0x68,0xB3,0x38,0x33,0x30,0x36,0x78,0x34,0xCC,0x31,0x86,0x00,0x00,
	
	"��",
	0x02,0x00,0x02,0x00,0x07,0xF0,0x08,0x20,0x38,0x40,0x04,0x80,0x03,0x40,0x0C,0x80,
  0x71,0xF8,0x02,0x08,0x0C,0x10,0x32,0x20,0x01,0x40,0x01,0x80,0x0E,0x00,0x70,0x00,
	
	"��",
	0x00,0x00,0x3F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x02,0x00,
  0x04,0x00,0x04,0x00,0x08,0x40,0x10,0x20,0x20,0x10,0x7F,0xF8,0x20,0x08,0x00,0x08,
	
	"��",
	0x00,0x20,0x00,0x20,0x7B,0xFE,0x48,0x20,0x49,0xFC,0x48,0x20,0x4B,0xFE,0x78,0x00,
  0x49,0xFC,0x49,0x04,0x49,0xFC,0x49,0x04,0x79,0xFC,0x49,0x04,0x01,0x14,0x01,0x08,
	
	"��",
	0x00,0x00,0x7D,0xFC,0x45,0x04,0x49,0x04,0x49,0x04,0x51,0xFC,0x49,0x04,0x49,0x04,
  0x45,0x04,0x45,0xFC,0x45,0x04,0x69,0x04,0x52,0x04,0x42,0x04,0x44,0x14,0x48,0x08,
	
	"��",
	0x00,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x7F,0xFC,0x41,0x04,0x41,0x04,
  0x49,0x44,0x45,0x24,0x41,0x04,0x49,0x44,0x45,0x24,0x41,0x04,0x41,0x14,0x40,0x08,
	
  "��",
	0x02,0x00,0x02,0x00,0x02,0x00,0x7F,0xFC,0x04,0x00,0x09,0x00,0x11,0x00,0x21,0x00,
	0x3F,0xF8,0x01,0x00,0x09,0x20,0x11,0x10,0x21,0x08,0x41,0x04,0x05,0x00,0x02,0x00,

	"��",
	0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x7F,0xFC,0x48,0x24,0x44,0x44,
	0x4F,0xE4,0x41,0x04,0x41,0x04,0x5F,0xF4,0x41,0x04,0x41,0x04,0x41,0x14,0x40,0x08,

	"��",
	0x00,0x00,0xFF,0xFE,0x04,0x40,0x04,0x40,0x04,0x40,0x3F,0xF8,0x24,0x48,0x24,0x48,
	0x24,0x48,0x24,0x48,0x28,0x38,0x30,0x08,0x20,0x08,0x20,0x08,0x3F,0xF8,0x20,0x08,

	"��",
	0x04,0x40,0x04,0x40,0x04,0x40,0x04,0x44,0x04,0x48,0x7C,0x50,0x04,0x60,0x04,0x40,
	0x04,0x40,0x04,0x40,0x04,0x40,0x04,0x42,0x1C,0x42,0xE4,0x42,0x44,0x3E,0x04,0x00,

  "��",
	0x00,0x00,0x3F,0xF0,0x20,0x10,0x20,0x10,0x28,0x50,0x24,0x50,0x22,0x90,0x22,0x90,
  0x21,0x10,0x21,0x10,0x22,0x90,0x22,0x92,0x24,0x4A,0x48,0x4A,0x40,0x06,0x80,0x02,
	
	"��",
	0x00,0x00,0x1F,0xF8,0x10,0x08,0x10,0x08,0x10,0x08,0x1F,0xF8,0x10,0x08,0x10,0x08,
  0x10,0x08,0x1F,0xF8,0x10,0x08,0x10,0x08,0x20,0x08,0x20,0x08,0x40,0x28,0x80,0x10,
	
	"��",
	0x00,0x00,0x1F,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,
  0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,
  "��",
	0x00,0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	"��",
	0x10,0x00,0x13,0xFC,0x20,0x84,0x20,0x88,0x48,0x88,0xF8,0x90,0x10,0x9C,0x20,0x84,
  0x41,0x44,0xF9,0x44,0x41,0x28,0x01,0x28,0x1A,0x10,0xE2,0x28,0x44,0x44,0x01,0x82,

  "��",
  0x00,0x40,0x20,0x40,0x17,0xFC,0x10,0x40,0x03,0xF8,0x02,0x48,0xF2,0x48,0x13,0xF8,
  0x10,0xE0,0x11,0x50,0x12,0x48,0x14,0x44,0x10,0x40,0x28,0x00,0x47,0xFE,0x00,0x00,
	
	"��",
	0x00,0x00,0x3F,0xF0,0x00,0x10,0x00,0x10,0x00,0x10,0x20,0x10,0x20,0x10,0x3F,0xF0,
	0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x04,0x20,0x04,0x20,0x04,0x1F,0xFC,0x00,0x00,

	"δ",
	0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,
	0x03,0x80,0x05,0x40,0x09,0x20,0x11,0x10,0x21,0x08,0xC1,0x06,0x01,0x00,0x01,0x00,

	"��",
	0x00,0x40,0x20,0x40,0x17,0xFE,0x10,0x80,0x00,0xA0,0x01,0x20,0xF3,0xFC,0x10,0x20,
	0x10,0x20,0x10,0x20,0x17,0xFE,0x10,0x20,0x10,0x20,0x28,0x20,0x47,0xFE,0x00,0x00,

	"��",
	0x10,0x80,0x10,0x40,0x13,0xFC,0x10,0x00,0xFD,0x08,0x10,0x90,0x17,0xFE,0x10,0x40,
	0x18,0x40,0x37,0xFE,0xD0,0x88,0x11,0x08,0x10,0x90,0x10,0x60,0x51,0x98,0x26,0x04,
	
	"��",
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,
  0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
	
	"��",
	0x00,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,
	0x21,0x08,0x21,0x08,0x3F,0xF8,0x11,0x00,0x0A,0x00,0x06,0x00,0x19,0xC0,0xE0,0x3E,
	
	"��",
	0x10,0x00,0x08,0x04,0x7F,0x78,0x00,0x40,0x22,0x40,0x14,0x40,0xFF,0x7E,0x08,0x48,
	0x08,0x48,0x7F,0x48,0x08,0x48,0x2A,0x48,0x49,0x48,0x88,0x88,0x28,0x88,0x11,0x08,

  "��",
	0x00,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,
	0x02,0x80,0x02,0x80,0x04,0x40,0x04,0x40,0x08,0x20,0x10,0x10,0x20,0x08,0xC0,0x06,

  "��",
	0x10,0x00,0x10,0x00,0x3F,0xFC,0x20,0x00,0x4F,0xF0,0x80,0x00,0x3F,0xF0,0x00,0x10,
	0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x0A,0x00,0x0A,0x00,0x06,0x00,0x02,
 
  "��",
	0x00,0x00,0x23,0xF8,0x12,0x08,0x12,0x08,0x83,0xF8,0x42,0x08,0x42,0x08,0x13,0xF8,
	0x10,0x00,0x27,0xFC,0xE4,0xA4,0x24,0xA4,0x24,0xA4,0x24,0xA4,0x2F,0xFE,0x00,0x00,

	"��",
	0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,
	0x23,0xE0,0x20,0x00,0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E,
	
	"��",
	0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x7F,0xF8,0x02,0x08,0x02,0x08,0x02,0x08,
	0x02,0x08,0x04,0x08,0x04,0x08,0x08,0x08,0x08,0x08,0x10,0x88,0x20,0x50,0x40,0x20,

	"��",
	0x02,0x00,0x04,0x00,0x08,0x00,0x7F,0xFC,0x40,0x04,0x40,0x04,0x47,0xC4,0x44,0x44,
	0x44,0x44,0x44,0x44,0x44,0x44,0x47,0xC4,0x44,0x44,0x40,0x04,0x40,0x14,0x40,0x08,
	
	"��",
	0x00,0x00,0x00,0xFC,0x7C,0x84,0x44,0x84,0x44,0x84,0x44,0xFC,0x7C,0x84,0x44,0x84,
	0x44,0x84,0x44,0xFC,0x7C,0x84,0x44,0x84,0x01,0x04,0x01,0x04,0x02,0x14,0x04,0x08,

	"Ԥ",
	0x00,0x00,0xF9,0xFE,0x08,0x20,0x50,0x40,0x21,0xFC,0x11,0x04,0xFD,0x24,0x25,0x24,
	0x29,0x24,0x21,0x24,0x21,0x24,0x21,0x44,0x20,0x50,0x20,0x88,0xA1,0x04,0x42,0x02,

  "��",
	0x10,0x00,0x11,0xFC,0x11,0x04,0x11,0x04,0xFD,0x14,0x11,0x08,0x11,0x00,0x15,0xFC,
	0x19,0x44,0x31,0x44,0xD1,0x28,0x11,0x28,0x11,0x10,0x11,0x28,0x51,0x44,0x21,0x82,
	
	"��",
	0x00,0x00,0x3F,0xF0,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x7F,0xFC,0x04,0x80,
  0x04,0x80,0x04,0x80,0x08,0x80,0x08,0x80,0x10,0x84,0x20,0x84,0x40,0x7C,0x80,0x00,
	
	"��",
	0x10,0x20,0x10,0x20,0x10,0x20,0x11,0xFC,0xFC,0x20,0x10,0x20,0x13,0xFE,0x10,0x08,
  0x18,0x08,0x33,0xFE,0xD0,0x08,0x10,0x88,0x10,0x48,0x10,0x08,0x50,0x28,0x20,0x10,
	
	"��",
	0x10,0x20,0x10,0x20,0x21,0xFC,0x24,0x20,0x44,0x20,0xFB,0xFE,0x10,0x02,0x20,0x94,
  0x40,0x50,0xFD,0x10,0x40,0x90,0x03,0xFE,0x1C,0x28,0xE0,0x44,0x40,0x82,0x03,0x02,
	
	"΢",
	0x11,0x08,0x15,0x48,0x25,0x48,0x45,0x50,0x97,0xDE,0x10,0x24,0x20,0x14,0x6F,0xD4,
  0xA0,0x14,0x27,0x94,0x24,0x94,0x24,0xA8,0x24,0xC8,0x24,0x94,0x28,0x14,0x30,0x22
};

 sFONT Font16x16 = {
  (const uint16_t*)Chinese16x16_Table->Index,
  16, /* Width */
  16, /* Height */
};
 