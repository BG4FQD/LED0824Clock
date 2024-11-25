#ifndef __PINDEF__
#define __PINDEF__

// DS1302
sbit DS1302SCLK = P5^5;                   //DS1302时钟口
sbit DS1302IO = P1^5;                     //DS1302数据口
sbit DS1302RST = P4^0;                    //DS1302片选口CE

// KEM-12288-BSR
// 
// COMMON GND 
#define LEDCOMM     P0

sbit Button1 = P3^0;
sbit Button2 = P3^1;

sbit SensorTemp = P1^6;
sbit SensorLight = P1^7;

sbit Beep = P5^4;

#endif
