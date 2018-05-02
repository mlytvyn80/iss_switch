/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * Simple AVR demonstration.  Controls a LED that can be directly
 * connected from OC1/OC1A to GND.  The brightness of the LED is
 * controlled with the PWM.  After each period of the PWM, the PWM
 * value is either incremented or decremented, that's all.
 *
 * $Id: group__demo__project.html,v 1.1.1.24 2016/02/09 07:13:43 joerg_wunsch Exp $
 */
#include <inttypes.h>
#include <avr/io.h>

//#include <avr/interrupt.h>
//#include <avr/sleep.h>

#include "hal.h"

void ioinit (void)
{   
    DDRB = 0x00; // Set port B as input
    DDRD = 0x00; // Set port D as input

    //sei ();
}

int main (void)
{
    ioinit ();
    
    for (;;)
        ;//sleep_mode();
        
    return (0);
}
