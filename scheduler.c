/*
 * scheduler.c
 *
 *  Created on: 29/1/2018
 *      Author: amarti
 */

#include "scheduler.h"

uint16_t Tick_out=0; /* MUST DECLARE AND INSTANTIATE HERE */

/* Called from TA_0 ISR*/
void callback_2ms(void) 
{
	//Tick_out = 0; //Maybe this is no the final place to declare this variable

	Tick_out = 1;
}






