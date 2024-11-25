// CLI Command Line Interface
/****************************************************

DATE [/T | date]
Current Date: 2024/07/23
New Date: (YYYY/MM/DD)      

TIME [/T | time]
Current Time: 15:07:51.29
New Time: (HH:MM:SS)

HELP

VER

EXIT
****************************************************/

#include <cli.h>

unsigned char code *sCMHelp={
    "EXIT\t Close current connection\n"
    "DATE\tShow or Set Date\n"
    "HELP\tShow Command List\n"
    "TIME\tShow or Set Time\n"
};

unsigned char code *sCMDate={
    "DATE [date]\n"
};

unsigned char code *sCMTime={
    "TIME [time]\n"
};

unsigned char code *sCMVer={
    "LED Clock.\n"
    "Software Ver 1.0\n"
    "Coded by BG4FQD 2024/07/23\n"
};

unsigned char xdata cmlbuf[24];

void Parse(void)
{
    return;
}

void DFADoEvent(void)
{
    for(;;)
    return;
}