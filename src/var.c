// var.c
#include < var.h>

unsigned int Temperature = 0; //
unsigned int Luminance = 0;   //
unsigned char KeyboradBuffer[8] = {0};
unsigned char KeyboradBufferHead = 0, KeyboradBufferTail = 0;
//                             ss    mm    hh    date  mon   day   year
unsigned char DSDatetime[7] = {0x00, 0x00, 0x12, 0x01, 0x07, 0x02, 0x13};

unsigned char xdata UARTBuf[UARTBUFSIZE];
unsigned char xdata UARTBUFStart = 0, UARTBUFEnd = 0;