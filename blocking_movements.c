#include "blocking_movements.h"
#include "display.h"
#include "control_motors.h"
#include "control_encoders.h"

#define ONE_MS 12000
#define ONE_US 12

uint8_t spin_bearing(uint8_t direction, uint8_t speed, uint16_t target_bearing)
{
	uint16_t actual_bearing = 0, actual_bearing2=0, actual_bearing3=0, upper, lower;
	char stop =0;

	if( ( (direction == RIGHT) || (direction == LEFT) ) && (speed >= 0) && (speed <= 100) && ( (target_bearing >= 0) && (target_bearing < 3600) ) )
	{
		/* Read bearing */
		while(Read_compass_16(&actual_bearing) != 0)
		{
			show_string("Err1");
		}
		/*__delay_cycles(ONE_US);
		Read_compass_16(&actual_bearing2);
		__delay_cycles(ONE_US);
		Read_compass_16(&actual_bearing3);
		__delay_cycles(ONE_US);*/

		//actual_bearing = (actual_bearing + actual_bearing2 + actual_bearing3)/3.0;

		upper = target_bearing + 3600 + DELTA_BEARING;
		lower = target_bearing + 3600 - DELTA_BEARING;

		if( ( ((actual_bearing+3600) < upper) && ((actual_bearing+3600) > lower) ) || (actual_bearing > lower)  )
		{
			stop = 1;
		}
		else
		{
			stop = 0;

			if(direction == RIGHT)
			{
				Speed_motor(-speed, RIGHT);
				Speed_motor(speed, LEFT);
			}
			else
			{
				Speed_motor(speed, RIGHT);
				Speed_motor(-speed, LEFT);
			}
		}

		while(!stop)
		{
			//show_number((uint16_t)fabs(target_bearing - actual_bearing));
			show_number(actual_bearing);

			while(Read_compass_16(&actual_bearing) != 0)
			{
				__delay_cycles(105*ONE_MS);

				show_string("Err2");

			}

			if( ( ((actual_bearing+3600) <= upper) && ((actual_bearing+3600) >= lower) ) || (actual_bearing > lower)  )
			{
				stop = 1;
			}
			else
			{
				stop = 0;
			}
			__delay_cycles(105*ONE_MS);

		}

		Speed_motor(0, RIGHT);
		Speed_motor(0, LEFT);

		return 0;
	}
	else
	{
		return 1; 		/* If the parameters are wrong values, we return an error code */
	}
}

uint8_t spin_steps(uint8_t direction, uint8_t speed,uint16_t turns, uint8_t steps)
{
	distance_type distance_left;
	uint16_t steps_left, steps_required_left;

	/* Checking the consistence of the parameters */
	if( ( (direction == RIGHT) || (direction == LEFT) ) && (speed >= 0) && (speed <= 100) )
	{
		Read_distance(LEFT, &distance_left);	/* Read the distance */
		steps_left = distance_left.turns * MAX_STEPS + distance_left.steps;		/* Convert in steps */
		steps_required_left = turns * MAX_STEPS + steps + steps_left;			/* Compute the steps to reach */

		/* Blocking part */
		while((steps_required_left - steps_left) > 0)
		{
			Read_distance(LEFT, &distance_left);
			steps_left = distance_left.turns * MAX_STEPS + distance_left.steps;		/* Get and compute the current steps */

			if(direction == RIGHT)
			{
				Speed_motor(-speed, RIGHT);
				Speed_motor(speed, LEFT);
			}
			else if(direction == LEFT)
			{
				Speed_motor(speed, RIGHT);
				Speed_motor(-speed, LEFT);
			}
		}

		/* Stop moving if the robot reached the numbers of turns and steps */
		Speed_motor(0, RIGHT);
		Speed_motor(0, LEFT);

		return 0;
	}
	else
	{
		return 1;			/*Return an error if the parameters are not correct */
	}
}
uint8_t straight_move(uint8_t direction, uint8_t speed,uint16_t turns, uint8_t steps)
{
	distance_type distance_left;
	uint16_t steps_left, steps_required_left;

	if((direction == FORWARD || direction == BACKWARD) && speed >= 0 && speed <= 100)
	{
		Read_distance(LEFT, &distance_left);
		steps_left = distance_left.turns * MAX_STEPS + distance_left.steps;
		steps_required_left = turns * MAX_STEPS + steps + steps_left;

		while(steps_required_left - steps_left > 0)
		{
			Read_distance(LEFT, &distance_left);
			steps_left = distance_left.turns * MAX_STEPS + distance_left.steps;

			if(direction == FORWARD)
			{
				Speed_motor(speed, RIGHT);
				Speed_motor(speed, LEFT);
			}
			else if(direction == BACKWARD)
			{
				Speed_motor(-speed, RIGHT);
				Speed_motor(-speed, LEFT);
			}
		}

		Speed_motor(0, RIGHT);
		Speed_motor(0, LEFT);

		return 0;
	}
	else
	{
		return 1;
	}
}
