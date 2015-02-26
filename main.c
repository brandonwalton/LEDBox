/* 
 * File:   main.c
 * Author: Brandon E. Walton
 *
 * Created on January 24, 2014, 11:04 PM
 */
#include <GenericTypeDefs.h>
#include "StandardTypes.h"

#include <stdio.h>
#include <stdlib.h>
#include <p18f45k80.h>
#include <xc.h>

#pragma config XINST = OFF
#pragma config WDTEN = OFF

#include "CAN.h"
#include "Config.h"
#include "ProcessCAN.h"

void main()
{
    Setup();

    while (true)
    {
        ProcessCAN();
    }

    // Don't enter the void.
    while (true);
}

