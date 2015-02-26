#include "ADC.h"
#include "StandardTypes.h"
#include "Config.h"

#include <xc.h>

void ADC_Setup()
{
    // Set AN0 as an input
    TRISAbits.TRISA0 = true;
    // Select AN0 as an analogue pin
    ANCON0bits.ANSEL0 = true;

    // Set the Special Trigger Select bits to zero (not using these)
    ADCON1bits.TRIGSEL = false;
    // Set the ADC unit to select AVdd as VREF+
    ADCON1bits.VCFG = false;
    // Set the ADC unit to select AVss as VREF-
    ADCON1bits.VNCFG = false;
    // Set the analog negative channel select bits to AVss
    ADCON1bits.CHSN = false;

    // Select "right justification" for analogue reads
    ADCON2bits.ADFM = true;
    // Select the acquisition time bits
    ADCON2bits.ACQT = 0x6; // 110, 64Tosc
    // Select the conversion clock select bits
    ADCON2bits.ADCS = 0x0; // ADC clock @ Fosc/2 8 MHz

    __delay_ms(1);

    // This must be set last
    ADCON0bits.ADON = true;
    __delay_us(15);
}

void ADC_Enable()
{
    ADCON0bits.ADON = true;
    __delay_us(15);
}

void ADC_Disable()
{
    ADCON0bits.ADON = false;
    __delay_us(15);
}

INT32 ADC_Read()
{
    ADCON0bits.CHS = 0x0; // Channel AN0
    ADCON0bits.GODONE = true;

    while (!ADCON0bits.GODONE);

    int Temp = 0;
    int ReadValue = 0;

    ReadValue = ADRESL;
    Temp = ADRESH;
    ReadValue |= Temp << 8;

    INT32 MeasuredValue = (INT32)(5000 * ((float)ReadValue / (float)4096));
    INT32 ReturnValue = MeasuredValue < 0 ? 0 : MeasuredValue;

    return ReturnValue;
}

float ADC_ReadF()
{
    ADCON0bits.CHS = 0x0; // Channel AN0
    ADCON0bits.GODONE = true;

    while (!ADCON0bits.GODONE);

    int Temp = 0;
    int ReadValue = 0;

    ReadValue = ADRESL;
    Temp = ADRESH;
    ReadValue |= Temp << 8;

    float MeasuredValue = (5000 * ((float)ReadValue / (float)4096));

    return MeasuredValue < 0 ? 0 : MeasuredValue;
}