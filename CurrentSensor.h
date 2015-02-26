/* 
 * File:   CurrentSensor.h
 * Author: Brandon E. Walton
 *
 * Created on February 6, 2014, 10:01 AM
 */

#ifndef CURRENTSENSOR_H
#define	CURRENTSENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

    void CurrentSensor_Zero();
    INT32 CurrentSensor_CANRead();
    float CurrentSensor_Read();

#ifdef	__cplusplus
}
#endif

#endif	/* CURRENTSENSOR_H */

