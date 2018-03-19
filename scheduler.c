/*
 * scheduler.c
 *
 *  Created on: 29/1/2018
 *      Author: amarti
 */
#include <msp430g2553.h>
#include "scheduler.h"

uint16_t Tick_out=0;                /* The variable is now local to the module */

/* Called from TA_0 ISR*/
void callback_2ms(void) 
{
    Tick_out = 1;
}

uint8_t check_and_clear_Tick_out(void)
{
    uint16_t timer_backup = 0;      /* Save of the timer state */
    uint8_t  tckout = 0;            /* Variable used to return the value of Tick_out */
    uint8_t  GIEdisabled = 0;

    if(__get_SR_register() & GIE)   /* Check if the general interruptions are already disabled */
    {
        GIEdisabled = 0;            /* It was enabled */
    }
    else
    {
        GIEdisabled = 1;            /* It was disabled, be careful. */
    }

    __disable_interrupt();          /* We disable the interruptions to avoid race conditions */

    tckout = Tick_out;              /* We save the Tick_out value to return it later */
    Tick_out = 0;                   /* We reset Tick_out */

    if(!GIEdisabled)                /* We re-enable the general interruption only if it was not disabled before */
    {
        __enable_interrupt();       /* All the work on the variable is done, we can re-enable the interruption system */
    }

    return tckout;                  /* We send the value of Tick_out */
}





