#ifndef __DS1302_H__
#define __DS1302_H__

// *p
//                   //Sec   Min  Hour  Date   Mon   Day  Year
//BYTE code init[] = {0x00, 0x00, 0x20, 0x01, 0x01, 0x05, 0x10};
//

void DS1302_Initial();
void DS1302_SetTime(unsigned char *p);
void DS1302_GetTime(void);
#endif
