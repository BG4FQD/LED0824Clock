// UART
#include "stc15.h"
#include <rtx51tny.h>
#include <uart.h>
#include <var.h>

#define BAUD 115200

void UART_Initial(void)
{
    /*
    SCON = 0x50;
    TMOD |= 0x20;
    TH1 = 221;
    //TL2 = 0xFD;
    TI = 1;     //
    */
    SCON = 0x5A;
    AUXR = 0x14;
    AUXR |= 0x01;
    T2L = 0xe8; //(65536 - (11059200L/4/BAUD));
    T2H = 0xff; //(65536 - (XTAL/32/BAUD)) >> 8;
    return;
}

void UART_SendData(unsigned char dat)
{
    while (!TI)
        ;
    TI = 0;
    SBUF = dat;
}

void uart(void) interrupt 4 using 2
{
    unsigned char c;
    bit start_trans = 0;

    if (RI)
    {             /* if receiver interrupt                 */
        c = SBUF; /* read character                        */
        RI = 0;   /* clear interrupt request flag          */
        UARTBUFEnd = (UARTBUFEnd + 1) % UARTBUFSIZE;
        UARTBuf[UARTBUFEnd] = c;
        if (c == 0x0A)
            isr_send_signal(5);
    }
    return;
}
