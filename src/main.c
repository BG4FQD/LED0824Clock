/*
 MAIN
*/
#include <stc15.h>
#include <intrins.h>
#include <rtx51tny.h>
#include <pindef.h>
#include <var.h>
#include <adc.h>
#include <LEDMatrix.h>
#include <ds1302.h>
#include <uart.h>

void Init()
{
    P0M0 = 0xFF;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    UART_Initial();
    // DS1302_Initial();
    ADC_Initial();
    LED_Initial();
    // 12288 COMMON GND
// #define FORTEST
#ifdef FORTEST
    DSDatetime[0] = 0x00; // second
    DSDatetime[1] = 0x42; // mins
    DSDatetime[2] = 0x22; // clock
    DSDatetime[3] = 0x24; // Date
    DSDatetime[4] = 0x08; // July
    DSDatetime[5] = 0x06; // Saturday
    DSDatetime[6] = 0x24; // 2024
    DS1302_SetTime(DSDatetime);
#endif
}

// refresh LED RAM
void Job_Main(void) _task_ 1
{
    unsigned char t = 0;
    for (;;)
    {
        if (t == 0)
            DS1302_GetTime();
        t = (t + 1) % 4;
        DrawTime();
        os_wait2(K_TMO, 5);
    }
}

// ADC
void Job_ADC(void) _task_ 2
{
    for (;;)
    {
        GetLuminance();
        UART_SendData(Luminance >> 8);
        UART_SendData(Luminance & 0xFF);
        GetTemperature();
        UART_SendData(Temperature >> 8);
        UART_SendData(Temperature & 0xFF);
        UART_SendData(0x00);
        UART_SendData(0x01);
        UART_SendData(0x02);
        os_wait2(K_TMO, 50);
    }
}

// Read Button
void Job_Keyboard(void) _task_ 3
{
    for (;;)
    {
        os_switch_task();
    }
}

// Update VRAM to LED
void Job_Display(void) _task_ 4
{
    for (;;)
    {
        Refresh();
        os_wait2(K_TMO, 1);
    }
}

// Prase Command Line
void Job_CLI(void) _task_ 5
{
    for (;;)
    {
        os_wait2(K_SIG, 1);
        os_switch_task();
    }
}

void startup_task(void) _task_ 0
{
    Init();
    os_create_task(1);
    os_create_task(2);
    os_create_task(3);
    os_create_task(4);

    os_delete_task(0);
}
