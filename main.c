#include <msp430g2553.h>
#include "system.h"
#include <stdint.h>
#include "intrinsics.h"
#include "timeout.h"
#include "display.h"
#include "compass.h"
#include "control_motors.h"
#include "scheduler.h"
#include "bearing.h"

#include "non_blocking.h"
#include "blocking_movements.h"

#define SPEED 22
#define CENT_MS 1200000
/*

 * main.c

 */

void main(void) {
	distance_type dist;
	uint8_t in_movement = 0,direction = 0;
	uint16_t actual_bearing =0, target_bearing = 0;

	//WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
	init_timeout();
	Clock_graceInit_DCO_12M();
	init_display();
	Init_encoders_distance();
	Init_motors();
	compass_init();


	__enable_interrupt();

	while(1)
	{
		if(in_movement == 0)
		{
			while(Read_compass_16(&actual_bearing) != 0)
			{
				show_string("Err0");
			}


			switch(direction)
			{
			case 0:
				/*Compute target bearing */
				new_bearing(actual_bearing,900,&target_bearing);
				nb_spin_bearing(RIGHT,SPEED,target_bearing);
				break;
			case 1:
				/*Compute target bearing */
				new_bearing(actual_bearing,-450,&target_bearing);
				nb_spin_bearing(LEFT,SPEED,target_bearing);
				break;
			default:;
			}

			direction = 1 - direction;                              /* Change direction */
			in_movement = 1;                                        /* Now we are in movement */
		}
		/*if the robot is moving check if it must stop*/
		else
		{
			/*Every 2ms we enter in the condition */
			if(check_and_clear_Tick_out() == 1)
			{
				if(check_stop_bearing() == 0)                         /* If the robot need to stop */
					in_movement = 0;                                /* we are ready to launch new movement */
				else
					in_movement = 1;

			}
		}

		/* Do something to show that we are using not blocking functions */
		Read_distance(LEFT, &dist);                                 /* We read the distance on the left wheel */
		show_number(dist.turns);                                    /* We print the number of turn we made on the display */
	}
}
