/* 
 * File:   ADC.h
 * Author: Brandon E. Walton
 *
 * Created on January 30, 2014, 1:22 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

    void ADC_Setup();
    
    void ADC_Enable();
    void ADC_Disable();

    long int ADC_Read();
    float ADC_ReadF();
    

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

