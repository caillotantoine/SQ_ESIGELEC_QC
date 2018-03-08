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

    __disable_interrupt();          /* We disable the interruptions to avoid race conditions */

    timer_backup = TA0CTL & TAIE;   /* We save the state of the timer interruption */
    TA0CTL &= ~TAIE;                /* Reset the timer interruption */
    tckout = Tick_out;              /* We save the Tick_out value to return it later */
    Tick_out = 0;                   /* We reset Tick_out */
    TA0CTL |= timer_backup;         /* We reset the timer interruption to the previous value*/

    __enable_interrupt();           /* All the work on the variable is done, we can re-enable the interruption system */

    return tckout;                  /* We send the value of Tick_out */
}





