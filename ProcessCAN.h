/* 
 * File:   ProcessCAN.h
 * Author: Brandon E. Walton
 *
 * Created on January 30, 2014, 4:09 PM
 */

#ifndef PROCESSCAN_H
#define	PROCESSCAN_H

#ifdef	__cplusplus
extern "C" {
#endif

    // Public:
    void ProcessCAN();

    // Private:
    UINT32 TransmitCounter = 0;

    void ProcessMessage_BenchRequest();
    void ProcessMessage_MosfetRequest();
    void ProcessMessage_RelayRequest();
    void ProcessCANTransmits();

#ifdef	__cplusplus
}
#endif

#endif	/* PROCESSCAN_H */

