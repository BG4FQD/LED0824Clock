#ifndef __VAR_H__
#define __VAR_H__

#define XTAL 11059200L

extern unsigned int Temperature; // �¶ȴ�������ֵ
extern unsigned int Luminance;   // ���ȴ�������ֵ
extern unsigned char KeyboradBuffer[8];
extern unsigned char KeyboradBufferHead, KeyboradBufferTail;
extern unsigned char DSDatetime[7];

#define UARTBUFSIZE 32
extern unsigned char xdata UARTBuf[];
extern unsigned char xdata UARTBUFStart, UARTBUFEnd;

#endif
