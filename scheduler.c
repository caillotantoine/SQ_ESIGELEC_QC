/*
 * scheduler.c
 *
 *  Created on: 29/1/2018
 *      Author: amarti
 */
#include <msp430g2553.h>
#include "scheduler.h"

uint16_t Tick_out=0; /* MUST DECLARE AND INSTANTIATE HERE */

/* Called from TA_0 ISR*/
void callback_2ms(void) 
{
    Tick_out = 1;
}

uint8_t check_and_clear_Tick_out(void)
{
    uint16_t timer_backup = 0;
    uint8_t  tckout = 0;

    __disable_interrupt();

    timer_backup = TA0CTL & TAIE;
    TA0CTL &= ~TAIE;
    tckout = Tick_out;
    Tick_out = 0;
    TA0CTL |= timer_backup;

    __enable_interrupt();

    return tckout;
}





