#include <msp430g2553.h>
#include <stdint.h>
#include "system.h"
#include "control_motors.h"
#include "control_encoders.h"
#include "display.h"
#include "blocking_movements.h"

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	/* Stop the watchdog */
	
	Clock_graceInit_DCO_12M();  /* Set the clock to 12 MHz */

	init_display();             /* Initialize the display */
	Init_encoders_distance();   /* Initialize the encoders */
	Init_motors();              /* Initialize the motors */

	__enable_interrupt();       /* Enable the interruptions */

	Clear_Distance(RIGHT);       /* Clear the distance stored in the memory */
	Clear_Distance(LEFT);

	straight_move(FORWARD, 70, 3, 5);

	return 0;
}
