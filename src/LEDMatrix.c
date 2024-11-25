#include <string.h>
#include <LEDMatrix.h>
#include <intrins.h>
#include <stc15.h>
#include <pindef.h>
#include <var.h>

// FONT MAP
#define FONTSIZE 20
unsigned char code FONT[20][5] = {
    0x7E, 0x81, 0x81, 0x7E, 0x00, // 0
    0x00, 0x82, 0xFF, 0x80, 0x00, // 1
    0xE2, 0x91, 0x89, 0x86, 0x00, // 2
    0x42, 0x81, 0x89, 0x76, 0x00, // 3
    0x1E, 0x11, 0xFF, 0x10, 0x00, // 4
    0x4F, 0x89, 0x89, 0x71, 0x00, // 5
    0x7E, 0x89, 0x89, 0x72, 0x00, // 6
    0x01, 0xE1, 0x19, 0x07, 0x00, // 7
    0x76, 0x89, 0x89, 0x76, 0x00, // 8
    0x46, 0x89, 0x89, 0x7E, 0x00, // 9
    254, 33, 33, 254, 0,          // A
    255, 137, 137, 118, 0,        // B
    126, 129, 129, 66, 0,         // C
    255, 129, 129, 126, 0,        // D
    0xFF, 0x89, 0x89, 0x89, 0x00, // E
    0xFF, 0x09, 0x09, 0x09, 0x00, // F
    0x80, 0x00, 0x00, 0x00, 0x00, //.
    0x24, 0x00, 0x00, 0x00, 0x00, //:
    0x01, 0x1C, 0x22, 0x22, 0x00, //'c
    0x00, 0x00, 0x00, 0x00, 0x00  // Space
};

#define FONTPoint 16
#define FONTColon 17
#define FONTTemp 18
#define FONTSpace 19
// LED Matrix
// 8*8*3
// unsigned char LEDMatrix[24] = {248,38,33,38,248,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
unsigned char LEDMatrix[24] = {248, 38, 33, 38, 248, 0, 255, 137, 137, 137, 118, 0, 126, 129, 129, 129, 66, 0, 255, 129, 129, 129, 126, 128};

unsigned char code Cols[24] = {20, 21, 22, 23, 24, 25, 26, 27, 34, 35, 36, 37, 41, 42, 43, 44, 10, 11, 47, 12, 13, 32, 45, 46};

void Delay(void)
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

/*
void Delay1ms(void)   //��� 0us
{
    unsigned char a,b;
    for(b=199;b>0;b--)
        for(a=1;a>0;a--);
}
*/

void DisplayCol(char col, char status)
{
    switch (Cols[col])
    {
    // P1
    case 10:
        P10 = status;
        break;
    case 11:
        P11 = status;
        break;
    case 12:
        P12 = status;
        break;
    case 13:
        P13 = status;
        break;
    case 14:
        P14 = status;
        break;
    case 15:
        P15 = status;
        break;
    case 16:
        P16 = status;
        break;
    case 17:
        P17 = status;
        break;
    // P2
    case 20:
        P20 = status;
        break;
    case 21:
        P21 = status;
        break;
    case 22:
        P22 = status;
        break;
    case 23:
        P23 = status;
        break;
    case 24:
        P24 = status;
        break;
    case 25:
        P25 = status;
        break;
    case 26:
        P26 = status;
        break;
    case 27:
        P27 = status;
        break;
    // P3
    case 30:
        P30 = status;
        break;
    case 31:
        P31 = status;
        break;
    case 32:
        P32 = status;
        break;
    case 33:
        P33 = status;
        break;
    case 34:
        P34 = status;
        break;
    case 35:
        P35 = status;
        break;
    case 36:
        P36 = status;
        break;
    case 37:
        P37 = status;
        break;
    // P4
    case 40:
        P40 = status;
        break;
    case 41:
        P41 = status;
        break;
    case 42:
        P42 = status;
        break;
    case 43:
        P43 = status;
        break;
    case 44:
        P44 = status;
        break;
    case 45:
        P45 = status;
        break;
    case 46:
        P46 = status;
        break;
    case 47:
        P47 = status;
        break;
    }
    return;
}

void LED_Initial()
{
    P0 = 0;
    Cls();
    return;
}
/*
void AutoDelay(unsigned char d)
{
    char i, j;
    for(i=0; i<8; i++)
        if ((d >> i) & 0x01)
            for(j=0; j<10; j++)
                _nop_();
}
*/

// Auto delay
void AutoDelay(unsigned char d)
{
    //                           0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    unsigned char code dly[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
    int i, t, k = 8;
    // AD1.6 Light Sensor
    if (Luminance > 0x0340)
        k = 2;
    t = (dly[d & 0x0F] + dly[d >> 4]) * k;
    for (i = 0; i < t; i++)
        _nop_();
}

// Refresh LED
void Refresh()
{
    unsigned char i;
    for (i = 0; i < 24; i++)
    {
        DisplayCol(i, 0);
        LEDCOMM = LEDMatrix[i];
        AutoDelay(LEDMatrix[i]);
        DisplayCol(i, 1);
        LEDCOMM = 0;
        Delay();
    }
    return;
}

// Full LED_Buffer with 0x00
void Cls()
{
    unsigned char i;
    for (i = 0; i < 24; i++)
        LEDMatrix[i] = 0;
    return;
}

// for test
/*
void DrawText(char x, char y, char *p)
{
    static unsigned char k= 0;
    unsigned char i, t;
    for(i=0; i<24; i++)
    {
        t= (k + i) % (FONTSIZE * 5);
        LEDMatrix[i]= FONT[t/5][t%5];
    }
    k= (k + 1) % (FONTSIZE * 5);
    return;
}
*/
/*
void DrawText(char x, char y, char *p)
{
    unsigned char i;
    for(i=0; i<24; i++)
    {
        LEDMatrix[i]= FONT[i/5][i%5];
    }
    return;
}
*/

void AnimateDigital(unsigned char *vram, unsigned char vramsize, unsigned char DigiOld, unsigned char DigiNew, unsigned char step)
{
    unsigned char i, t = 0;
    if (DigiNew != DigiOld)
        for (i = 0; i < vramsize; i++)
        {
            if (step <= 7)
                t = (FONT[DigiNew][i] >> step);
            if (step >= 2)
                t |= (FONT[DigiOld][i] << (9 - step));
            *(vram + i) = t;
        }
    return;
}

// DrawTime HH:MM to VRAM
void DrawTime(void)
{
    static unsigned char DSDatetimeHis[3] = {0xAA, 0xAA, 0xAA}; // FONT: space
    static unsigned char k = 0;
    unsigned char t = 0;

    if (k == 0)
        if ((DSDatetimeHis[0] != DSDatetime[0]) || (DSDatetimeHis[1] != DSDatetime[1]) || (DSDatetimeHis[2] != DSDatetime[2]))
            k = 9;

    // Draw HOUR
    if (k != 0)
    {
        k--;
        // Draw Hour
        AnimateDigital(LEDMatrix + 0, 5, DSDatetimeHis[2] >> 4, DSDatetime[2] >> 4, k);
        AnimateDigital(LEDMatrix + 5, 5, DSDatetimeHis[2] & 0x0F, DSDatetime[2] & 0x0F, k);
        // Draw Minute
        AnimateDigital(LEDMatrix + 12, 5, DSDatetimeHis[1] >> 4, DSDatetime[1] >> 4, k);
        AnimateDigital(LEDMatrix + 17, 5, DSDatetimeHis[1] & 0x0F, DSDatetime[1] & 0x0F, k);
        if (k == 0)
        {
            DSDatetimeHis[0] = DSDatetime[0];
            DSDatetimeHis[1] = DSDatetime[1];
            DSDatetimeHis[2] = DSDatetime[2];
        }
    }

    // Draw Colon :
    if (DSDatetime[0] & 0x01)
        t = 1;
    memcpy(LEDMatrix + 10, FONT[FONTColon] + t, 2);
    // Clear SPACE
    *(LEDMatrix + 22) = 0x00;
    // Draw Second BCD
    *(LEDMatrix + 23) = DSDatetime[0];

    return;
}
