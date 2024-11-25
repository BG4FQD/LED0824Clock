/**************************************

**************************************/

#include "stc15.h"
#include "intrins.h"
#include <pindef.h>
#include <var.h>

typedef unsigned char BYTE;

/*****************************************************************
 DS1302
*****************************************************************/
#define SCLK DS1302SCLK // DS1302
#define IO DS1302IO     // DS1302
#define RST DS1302RST   // DS1302

/*
void main()
{
    DS1302_Initial();               //��ʼ��DS1302
    DS1302_SetTime(init);           //���ó�ʼʱ��

    DS1302_GetTime(now);            //��ȡ��ǰʱ��
    while (1);
}
*/

/**************************************
��ʱX΢��(STC12C5A60S2@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
����ʱ������ʹ��1T��ָ�����ڽ��м���,�봫ͳ��12T��MCU��ͬ
**************************************/
void Delay00()
{
    _nop_();
    _nop_();
}

/**************************************
��DS1302��1�ֽ�����
**************************************/
BYTE DS1302_ReadByte()
{
    BYTE i;
    BYTE dat = 0;

    for (i = 0; i < 8; i++) // 8λ������
    {
        SCLK = 0;  // ʱ��������
        Delay00(); // ��ʱ�ȴ�
        dat >>= 1; // ��������һλ
        if (IO)
            dat |= 0x80; // ��ȡ����
        SCLK = 1;        // ʱ��������
        Delay00();       // ��ʱ�ȴ�
    }
    return dat;
}

/**************************************
��DS1302д1�ֽ�����
**************************************/
void DS1302_WriteByte(BYTE dat)
{
    char i;

    for (i = 0; i < 8; i++) // 8λ������
    {
        SCLK = 0;  // ʱ��������
        Delay00(); // ��ʱ�ȴ�
        dat >>= 1; // �Ƴ�����
        IO = CY;   // �ͳ����˿�
        SCLK = 1;  // ʱ��������
        Delay00(); // ��ʱ�ȴ�
    }
}

/**************************************
��DS1302ĳ��ַ�ĵ�����
**************************************/
BYTE DS1302_ReadData(BYTE addr)
{
    BYTE dat;

    RST = 0;
    Delay00();
    SCLK = 0;
    Delay00();
    RST = 1;
    Delay00();
    DS1302_WriteByte(addr);  // д��ַ
    dat = DS1302_ReadByte(); // ������
    SCLK = 1;
    RST = 0;

    return dat;
}

/**************************************
��DS1302��ĳ����ַд������
**************************************/
void DS1302_WriteData(BYTE addr, BYTE dat)
{
    RST = 0;
    Delay00();
    SCLK = 0;
    Delay00();
    RST = 1;
    Delay00();
    DS1302_WriteByte(addr); // д��ַ
    DS1302_WriteByte(dat);  // д����
    SCLK = 1;
    RST = 0;
}

/**************************************
д���ʼʱ��
**************************************/
void DS1302_SetTime(BYTE *p)
{
    BYTE addr = 0x80;
    BYTE n = 7;

    DS1302_WriteData(0x8e, 0x00); // ����д����
    while (n--)
    {
        DS1302_WriteData(addr, *p++);
        addr += 2;
    }
    DS1302_WriteData(0x8e, 0x80); // д����
}

/**************************************
��ȡ��ǰʱ��
**************************************/
void DS1302_GetTime(void)
{
    BYTE addr = 0x81;
    BYTE n = 7;
    BYTE *p = DSDatetime;
    while (n--)
    {
        *p++ = DS1302_ReadData(addr);
        addr += 2;
    }
}

/**************************************
��ʼ��DS1302
**************************************/
void DS1302_Initial()
{
    // unsigned char t;
    RST = 0;
    SCLK = 0;
    // DS1302_WriteData(0x8e, 0x00); // Enable write
    // t = DS1302_ReadData(0x81);
    //  t |= 0x80;
    // DS1302_WriteData(0x80, t);    // Start Clock
    // DS1302_WriteData(0x90, 0xa6); // Enable Changer
    // DS1302_WriteData(0x8e, 0x80); // Disable write

    DS1302_WriteData(0x8e, 0x00); // ����д����
    DS1302_WriteData(0x80, 0x00); // ʱ������
    DS1302_WriteData(0x90, 0xa6); // һ�������ܣ�4K������
    DS1302_WriteData(0x8e, 0x80); // д����
}
