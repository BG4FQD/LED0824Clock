#include <stc15.h>
#include <intrins.h>
#include <pindef.h>
#include <var.h>
#include <adc.h>

#define ADC_POWER 0x80
#define ADC_SPEEDLL 0x00
#define ADC_FLAG 0x10
#define ADC_START 0x08
#define NTC_CHAN 0x03
#define ADC_ADJ 0x00

void ADC_Initial(void)
{
    P1ASF = 0xC0; // 1100 0000
    ADC_RES = 0;
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_ADJ;
    // CLK_DIV |= 0x20;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    return;
}

// 8bit ADC
unsigned int GetADCResult(unsigned char ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG))
        ;
    ADC_CONTR &= ~ADC_FLAG; // Close ADC
    return (unsigned int)(ADC_RES << 2) | (unsigned int)(ADC_RESL & 0x03);
}

// P1^7 ADC Light Sensor
void GetLuminance()
{
    Luminance = GetADCResult(0x07);
    return;
}

/********************************************
0x01E1      26.3
0x01C7      27.8
0x01D7      25.9
********************************************/
void GetTemperature()
{
    //    static unsigned int LastValue= 0;
    //    Temperature= LastValue + GetADCResult(0x06)) / 2;
    //    LastValue= Temperature;
    Temperature = GetADCResult(0x06);
    return;
}
