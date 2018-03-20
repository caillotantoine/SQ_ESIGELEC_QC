/*
 * non_blocking.c
 *
 *  Created on: 7 mars 2018
 *      Author: a001220-dev
 */
#include "non_blocking.h"
#include "control_motors.h"
#include "blocking_movements.h"

static uint16_t distance_to_stop;
static uint16_t shared_target_bearing;

uint8_t check_stop_bearing()
{
	uint16_t actual_bearing = 0, upper =0 , lower =0;

	upper = shared_target_bearing + 3600 + DELTA_BEARING;
	lower = shared_target_bearing + 3600 - DELTA_BEARING;

	while(Read_compass_16(&actual_bearing) != 0);

	if( ( ((actual_bearing+3600) <= upper) && ((actual_bearing+3600) >= lower) ) || (actual_bearing > lower)  )
	{
		Speed_motor(0,RIGHT);
		Speed_motor(0, LEFT);
		return 0;
	}
	else
	{
		return 1;
	}

}

/* Non- blocking spin
 * @param Direction The rotation direction (Right or Left)
 * @param speed Between 0 to 100
 * @param target_bearing The absolute bearing to reach
 * Return 1 if the parameter are wrong, else 0 if everything ok*/
uint8_t nb_spin_bearing(uint8_t direction, uint8_t speed, uint16_t target_bearing)
{
	if( ( (direction == RIGHT) || (direction == LEFT) ) && (speed >= 0) && (speed <= 100) && ( (target_bearing >= 0) && (target_bearing < 3600) ) )
	{
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

		shared_target_bearing = target_bearing;
	}
	else
	{
		return 1;
	}

	return 0;
}

/**
 * Check if the robot got the wanted distance
 * Use Left encoders
 * Returns 0 if the robots has been stop in this function, 1 if it's still moving
 */
uint8_t check_stop_steps()
{
	distance_type read_dist;

	//read the distance
	Read_distance(LEFT,&read_dist);

	//if the robots are in the wanted position
	if( distance_to_stop <= (read_dist.turns*MAX_STEPS + read_dist.steps))
	{
		Speed_motor(0,RIGHT);
		Speed_motor(0,LEFT);
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
 * Non-Blocking function to move straight backward or straight forward
 * Indicate the number of turns and steps to reach
 * Return 1 if the parameters are not correct
 */
uint8_t nb_straight_move(uint8_t direction, uint8_t speed,uint16_t turns,uint8_t steps)
{
	distance_type distance_left;

	if( ((direction == FORWARD) || (direction == BACKWARD) ) && ( (speed >= 0) && (speed <= 100) ))
	{
		Read_distance(LEFT, &distance_left);
		distance_to_stop = distance_left.turns * MAX_STEPS + distance_left.steps + steps + turns * MAX_STEPS;

		if(direction == FORWARD)
		{
			Speed_motor(speed,RIGHT);
			Speed_motor(speed,LEFT);
		}
		else if (direction == BACKWARD)
		{
			Speed_motor(-speed,RIGHT);
			Speed_motor(-speed,LEFT);
		}
	}
	else
	{
		return 1;
	}

	return 0;
}

/**
 * Non-Blocking function to spin
 * Indicate the number of turns and steps to reach
 * Return 1 if the parameters are not correct
 */
uint8_t nb_spin_steps(uint8_t direction, uint8_t speed,uint16_t turns,uint8_t steps)
{
	distance_type distance_left;

	if( ((direction == RIGHT) || (direction == LEFT) ) && ( (speed >= 0) && (speed <= 100) ))
	{
		Read_distance(LEFT, &distance_left);
		/* Use the same variable in order to use the same check_stop_steps() function */
		distance_to_stop = distance_left.turns * MAX_STEPS + distance_left.steps + steps + turns * MAX_STEPS;

		if(direction == RIGHT)	/* Spin to right */
		{
			Speed_motor(-speed,RIGHT);
			Speed_motor(speed,LEFT);
		}
		else if (direction == LEFT)	/* Spin to left */
		{
			Speed_motor(speed,RIGHT);
			Speed_motor(-speed,LEFT);
		}
	}
	else
	{
		return 1;
	}

	return 0;
}

