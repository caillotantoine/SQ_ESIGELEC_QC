/*
 * Turn_path.c
 *
 *  Created on: 19 mars 2018
 *      Author: Antoine
 */

#include "Turn_path.h"
#include "control_encoders.h"
#include "control_motors.h"
#include "blocking_movements.h"
#include "display.h"

uint32_t step_to_reach;
uint8_t direction_glob;

int8_t turn_step_plus_bearing(uint8_t runDirection, uint8_t direction, uint8_t innerWspeed, uint8_t outerWspeed, uint16_t target_bearing)
{
	if(runDirection == FORWARD)
	{
		return turn_step_basic_bearing(direction, innerWspeed, outerWspeed, target_bearing);
	}
	else if (runDirection == BACKWARD)
	{
		return turn_step_basic_bearing(direction, -innerWspeed, -outerWspeed, target_bearing);
	}
	else
	{
		return -4;
	}
}

int8_t turn_step_basic_bearing(uint8_t direction, int8_t innerWspeed, int8_t outerWspeed, uint16_t target_bearing)
{
	uint16_t actual_bearing = 0, upper, lower;
	char stop =0;

	if((innerWspeed >= -100) && (innerWspeed <= 100) && (outerWspeed >= -100) && (outerWspeed <= 100) && ( (target_bearing >= 0) && (target_bearing < 3600) ) )
	{
		/* Read bearing */
		while(Read_compass_16(&actual_bearing) != 0)
		{
			show_string("Err1");
		}

		upper = target_bearing + 3600 + DELTA_BEARING;
		lower = target_bearing + 3600 - DELTA_BEARING;

		if( ( ((actual_bearing+3600) < upper) && ((actual_bearing+3600) > lower) ) || (actual_bearing > lower) || ((actual_bearing+7200) < upper) )
		{
			stop = 1;
		}
		else
		{
			stop = 0;

			if(direction == RIGHT)
			{
				Speed_motor(outerWspeed, LEFT);
				Speed_motor(innerWspeed, RIGHT);
			}
			else
			{
				Speed_motor(outerWspeed, RIGHT);
				Speed_motor(innerWspeed, LEFT);
			}
		}

		while(!stop)
		{
			show_number(actual_bearing);

			while(Read_compass_16(&actual_bearing) != 0)
			{
				__delay_cycles(105*ONE_MS);

				show_string("Err2");

			}

			if( ( ((actual_bearing+3600) <= upper) && ((actual_bearing+3600) >= lower) ) || (actual_bearing > lower) || ((actual_bearing+7200) < upper)  )
			{
				stop = 1;
			}
			else
			{
				stop = 0;
			}
			__delay_cycles(105*ONE_MS);

		}

	}
	else
	{
		return 1;
	}

	Speed_motor(0, RIGHT);
	Speed_motor(0, LEFT);
	return 0;
}


int8_t turn_step_plus_nb(uint8_t runDirection, uint8_t direction, uint8_t innerWspeed, uint8_t outerWspeed, uint16_t outerWturns, uint8_t outerWsteps)
{
	if(runDirection == FORWARD)
	{
		return turn_step_basic_nb_start(direction, innerWspeed, outerWspeed, outerWturns, outerWsteps);
	}
	else if (runDirection == BACKWARD)
	{
		return turn_step_basic_nb_start(direction, -innerWspeed, -outerWspeed, outerWturns, outerWsteps);
	}
	else
	{
		return -4;
	}
}

int8_t turn_step_basic_nb_start(uint8_t direction, int8_t innerWspeed, int8_t outerWspeed, uint16_t outerWturns, uint8_t outerWsteps)
{
	distance_type distance_runned;
	if((innerWspeed >= -100) && (innerWspeed <= 100) && (outerWspeed >= -100) && (outerWspeed <= 100))
	{
		direction_glob = direction;
		if(direction == LEFT)
		{
			/* outer wheel is the right one */
			Read_distance(RIGHT, &distance_runned);
			step_to_reach = distance2steps(distance_runned) + (outerWturns * MAX_STEPS) + outerWsteps;

			Speed_motor(outerWspeed, RIGHT);
			Speed_motor(innerWspeed, LEFT);
		}
		else if (direction == RIGHT)
		{
			/* outer wheel is the left one */
			Read_distance(LEFT, &distance_runned);
			step_to_reach = distance2steps(distance_runned) + (outerWturns * MAX_STEPS) + outerWsteps;

			Speed_motor(outerWspeed, LEFT);
			Speed_motor(innerWspeed, RIGHT);
		}
		else
		{
			return -2;
		}
	}
	else
	{
		return -1;
	}
	return 0;
}

int8_t check_stops_turning()
{
	distance_type distance_runned;

	if(direction_glob == LEFT)
	{
		/* outer wheel is the right one */
		Read_distance(RIGHT, &distance_runned);
		if(step_to_reach > distance2steps(distance_runned))
		{
			Speed_motor(0, RIGHT);
			Speed_motor(0, LEFT);
			return 0;
		}
	}
	else if (direction_glob == RIGHT)
	{
		/* outer wheel is the left one */
		Read_distance(LEFT, &distance_runned);
		if(step_to_reach < distance2steps(distance_runned))
		{
			Speed_motor(0, RIGHT);
			Speed_motor(0, LEFT);
			return 0;
		}
	}
	else
	{
		return 2;
	}
	return 1;
}

int8_t turn_step_basic(uint8_t direction, int8_t innerWspeed, int8_t outerWspeed, uint16_t outerWturns, uint8_t outerWsteps)
{
	distance_type distance_runned;
	uint32_t step_done, step_required;

	if((innerWspeed >= -100) && (innerWspeed <= 100) && (outerWspeed >= -100) && (outerWspeed <= 100))
	{
		if(direction == LEFT)
		{
			/* outer wheel is the right one */
			Read_distance(RIGHT, &distance_runned);
			step_required = distance2steps(distance_runned) + (outerWturns * MAX_STEPS) + outerWsteps;

			Speed_motor(outerWspeed, RIGHT);
			Speed_motor(innerWspeed, LEFT);

			while((step_required - step_done) > 0)
			{
				Read_distance(RIGHT, &distance_runned);
				step_done = distance2steps(distance_runned);
			}
		}
		else if (direction == RIGHT)
		{
			/* outer wheel is the left one */
			Read_distance(LEFT, &distance_runned);
			step_required = distance2steps(distance_runned) + (outerWturns * MAX_STEPS) + outerWsteps;

			Speed_motor(outerWspeed, LEFT);
			Speed_motor(innerWspeed, RIGHT);

			while((step_required - step_done) > 0)
			{
				Read_distance(LEFT, &distance_runned);
				step_done = distance2steps(distance_runned);
			}
		}
		else
		{
			return -2;
		}
	}
	else
	{
		return -1;
	}

	Speed_motor(0, RIGHT);
	Speed_motor(0, LEFT);
	return 0;
}

int8_t turn_step_plus(uint8_t runDirection, uint8_t direction, uint8_t innerWspeed, uint8_t outerWspeed, uint16_t outerWturns, uint8_t outerWsteps)
{
	if(runDirection == FORWARD)
	{
		return turn_step_basic(direction, innerWspeed, outerWspeed, outerWturns, outerWsteps);
	}
	else if (runDirection == BACKWARD)
	{
		return turn_step_basic(direction, -innerWspeed, -outerWspeed, outerWturns, outerWsteps);
	}
	else
	{
		return -4;
	}
}

uint32_t distance2steps(distance_type distance)
{
	return ((uint32_t) distance.turns * (uint32_t) MAX_STEPS) + (uint32_t) distance.steps;
}

