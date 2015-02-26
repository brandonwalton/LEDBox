#include "Config.h"
#include "CurrentSensor.h"
#include "ADC.h"
#include <math.h>

float InverseSampleNumber = 1f / CurrentSensor_ZeroSamples;
INT32 ZeroValue = 0x0698;//0x056C;

void CurrentSensor_Zero()
{
    float SampleTotal = 0;
    int Samples = 0;

    for (Samples = 0; Samples < CurrentSensor_ZeroSamples; Samples++)
    {
        SampleTotal += ADC_Read();
    }

    // Calculate the zero value from the averages taken,
    //  use the inverse sample number to try not to do float division on
    //  and 8 bit microcontroller...
    ZeroValue = (INT32)(SampleTotal * InverseSampleNumber);
}

INT32 CurrentSensor_CANRead()
{
    // Get the value and round
    INT32 RawValue = (INT32)round((ADC_Read() - ZeroValue) * CurrentSensor_Conversion);
    INT32 MeasuredValue = (RawValue);

    // Return the actual zeroed value
    return MeasuredValue > 0 ? MeasuredValue : 0;
}

float CurrentSensor_Read()
{
    float MeasuredValue = (ADC_ReadF() - ZeroValue) * CurrentSensor_Conversion;
    return MeasuredValue > 0 ? MeasuredValue : 0;
}

