#include <msp430g2553.h>
#include "system.h"
#include <stdint.h>
#include "intrinsics.h"
#include "timeout.h"
#include "display.h"
#include "compass.h"
#include "control_motors.h"
#include "scheduler.h"

#include "non_blocking.h"

#define SPEED 30
/*

 * main.c

 */

void main(void) {
    distance_type dist;
	uint8_t in_movement = 0,direction = 0;
	WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

	Clock_graceInit_DCO_12M();
	init_display();
	Init_encoders_distance();
	Init_motors();

	__enable_interrupt();

	while(1)
	{
		if(in_movement == 0)
		{
			switch(direction)
			{
			case 0:
				nb_straight_move(FORWARD,SPEED,1,0); /* Move forward */
				break;
			case 1:
				nb_straight_move(BACKWARD,SPEED,1,0); /* Move backward */
				break;
			default:;
			}

			direction = 1 - direction; /*Change direction*/
			in_movement = 1; /*Now we are in movement */
		}
		/*if the robot is moving check if it must stop*/
		else
		{
			/*Every 2ms we enter in the condition */
			if(check_and_clear_Tick_out() == 1)
			{
				if(check_stop_steps() == 0) //if the robot need to stop
					in_movement = 0; /* we are ready to launch new movement */
				else
					in_movement = 1;

			}
		}

		/* Do something to show that we are using not blocking functions */
		Read_distance(LEFT, &dist);
		show_number(dist.turns);
	}
}
