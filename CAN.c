
#include "CAN.h"
#include <pic18f45k80.h>

void CAN_Setup()
{

    CIOCONbits.CANCAP = true;
    // Set CAN module to Configuration mode and wait
    CANCON = 0x80;
    while (CANSTATbits.OPMODE != 0x04);

    // Set CAN module to operate in mode 1
    ECANCON = 0x40;

    // Set baud rate to 500 kb/s
    BRGCON1 = 0x00;
    BRGCON2 = 0xB8;
    BRGCON3 = 0x05;

    // Set buffer 0 to receive and all others to transmit
    BSEL0 = 0xF8;

    // Initialize both receive masks
    //  filter by standard identifier bits only
    RXM0EIDH = 0x00;
    RXM0EIDL = 0x00;
    RXM0SIDH = 0x00;//0xFF;
    RXM0SIDL = 0x00;//0xE0;

    RXM1EIDH = 0x00;
    RXM1EIDL = 0x00;
    RXM1SIDH = 0x00;
    RXM1SIDL = 0x00;

    // Enable filter 0, disable all others
    RXFCON0 = 0x01;
    RXFCON1 = 0x00;

    // Set filter 0 to use receive buffer 0, all others no filter
    RXFBCON0 = 0xF0;
    RXFBCON1 = 0xFF;
    RXFBCON2 = 0xFF;
    RXFBCON3 = 0xFF;
    RXFBCON4 = 0xFF;
    RXFBCON5 = 0xFF;
    RXFBCON6 = 0xFF;
    RXFBCON7 = 0xFF;

    // Set filter 0 to use mask 0
    MSEL0 = 0xFC;
    MSEL1 = 0xFF;
    MSEL2 = 0xFF;
    MSEL3 = 0xFF;

    // Set filter one to accept 0x2C2
    RXF0EIDH = 0x00;
    RXF0EIDL = 0x00;
    RXF0SIDH = 0x2C;
    RXF0SIDL = 0x20;

    // Set CAN module back to Normal mode and wait
    CANCON = 0x00;
    while (CANSTATbits.OPMODE != 0x00);

    RXB0CON = 0x00;//0x04;
    RXB1CON = 0x00;//0x04;
}

void CAN_Transmit(CANMessage* message)
{
    // Set the extended message id
    TXB0EIDH = message->ExtendedID >> 8;
    TXB0EIDL = (message->ExtendedID & 0x07) << 5;

    // Set the standard message id
    TXB0SIDH = (message->StandardID >> 3);
    TXB0SIDL = (message->StandardID & 0x07) << 5;

    // Set the message length
    TXB0DLC = message->MessageLength;

    // Set the message data contents
    TXB0D0 = message->MessageData[0];
    TXB0D1 = message->MessageData[1];
    TXB0D2 = message->MessageData[2];
    TXB0D3 = message->MessageData[3];
    TXB0D4 = message->MessageData[4];
    TXB0D5 = message->MessageData[5];
    TXB0D6 = message->MessageData[6];
    TXB0D7 = message->MessageData[7];

    // Request the message transmission
    TXB0CONbits.TXREQ = 1;
}

bool CAN_Receive()
{
    // Assumes polling mode;

    // If buffer 0 contains a message
    if (RXB0CONbits.RXFUL)
    {
        // Extract it to LastMessage

        // Set the message ids for the message
        Message.ExtendedID = (RXB0EIDH << 3) | (RXB0EIDL >> 5);
        Message.StandardID = (RXB0SIDH << 3) | (RXB0SIDL >> 5);

        // Set the message data length
        Message.MessageLength = RXB0DLC;

        // Set the message data
        Message.MessageData[0] = RXB0D0;
        Message.MessageData[1] = RXB0D1;
        Message.MessageData[2] = RXB0D2;
        Message.MessageData[3] = RXB0D3;
        Message.MessageData[4] = RXB0D4;
        Message.MessageData[5] = RXB0D5;
        Message.MessageData[6] = RXB0D6;
        Message.MessageData[7] = RXB0D7;

        // Reset the receive buffer
        RXB0CONbits.RXFUL = 0;
        PIR5bits.RXB1IF = 0;

        return true;
    }
    else
    {
        // No message received
        return false;
    }


}