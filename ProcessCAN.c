#include <GenericTypeDefs.h>
#include "ProcessCAN.h"
#include "Config.h"
#include "CAN.h"
#include "CurrentSensor.h"

void ProcessCAN()
{
    // If a CAN message has been received
    if (CAN_Receive())
    {
        if (Message.StandardID == 0x2C2)
        {
            // Commit the message contents to the port states
            UINT8 Temp = (Message.MessageData[0] & 0x80) != 0;
            PIN_LED01 = Temp;

            Temp = (Message.MessageData[0] & 0x40) != 0;
            PIN_LED02 = Temp;

            Temp = (Message.MessageData[0] & 0x20) != 0;
            PIN_LED03 = Temp;

            Temp = (Message.MessageData[0] & 0x10) != 0; // Charge indicator
            PIN_LED04 = Temp;

            Temp = (Message.MessageData[0] & 0x08) != 0;
            PIN_LED05 = Temp;

            Temp = (Message.MessageData[0] & 0x04) != 0;
            PIN_LED06 = Temp;
        }
    }

    ProcessCANTransmits();
}

void ProcessCANTransmits()
{
    TransmitCounter++;

    if (TransmitCounter >= CANMsg_TransmitCounter)
    {
        bool State = PIN_LEDIND;

        PIN_LEDIND = !State;

//        UINT32 RawReading = CurrentSensor_CANRead();
//
//        CANMessage StatusMessage;
//        StatusMessage.StandardID = CANMsgID_BenchStatus;
//        StatusMessage.MessageLength = 2;
//        StatusMessage.MessageData[1] = (RawReading & 0xFF00) >> 8;
//        StatusMessage.MessageData[0] = (RawReading & 0xFF);
//
//        CAN_Transmit(&StatusMessage);
//
        TransmitCounter = 0;
    }
}