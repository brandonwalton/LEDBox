/* 
 * File:   Config.h
 * Author: Brandon E. Walton
 *
 * Created on January 24, 2014, 11:51 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <pic18.h>

#define _XTAL_FREQ 16000000

// Message IDs
#define CANMsgID_LEDRequest 0x01

#define CANMsg_TransmitRate 50 // approx. ms
#define CANMsg_TransmitCounter _XTAL_FREQ / (6*1000) * CANMsg_TransmitRate

// Pin Assignments
#define PIN_LED01 LATCbits.LATC0
#define PIN_LED02 LATCbits.LATC1
#define PIN_LED03 LATCbits.LATC2
#define PIN_LED04 LATCbits.LATC3
#define PIN_LED05 LATDbits.LATD0
#define PIN_LED06 LATDbits.LATD1

#define PIN_LEDIND LATDbits.LATD2

#define PIN_CANTx PORTCbits.RC6
#define PIN_CANRx PORTCbits.RC7

void Setup();

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

