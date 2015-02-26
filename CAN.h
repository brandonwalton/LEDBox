/* 
 * File:   CAN.h
 * Author: Brandon E. Walton
 *
 * Created on January 24, 2014, 11:41 PM
 */

#include <GenericTypeDefs.h>
#include "StandardTypes.h"

#ifndef CAN_H
#define	CAN_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct CANMessage CANMessage;
struct CANMessage
{
    int ExtendedID;
    int StandardID;
    UINT8 MessageLength;
    UINT8 MessageData[8];
};

CANMessage Message;

void CAN_Setup(void);
void CAN_Transmit(CANMessage*);
bool CAN_Receive(void);

#ifdef	__cplusplus
}
#endif

#endif	/* CAN_H */

