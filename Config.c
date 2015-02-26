#include "Config.h"
#include "CAN.h"
#include <pic18.h>

void Setup()
{
    // Set the main oscillator to run 16 MHz
    OSCCON |= 114;//112;

    // Set tristates
    TRISD = 0x00;
    TRISC = 0x00;
    TRISBbits.TRISB3 = true;

    // Set all outputs to zero
    LATA = 0;
    LATB = 0;
    LATC = 0;
    LATD = 0;
    LATE = 0;

    // Setup the CAN module
    CAN_Setup();
}
