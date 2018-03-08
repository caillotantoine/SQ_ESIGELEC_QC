#include "blocking_movements.h"
#include "display.h"
#include "control_motors.h"
#include "control_encoders.h"

uint8_t spin_steps(uint8_t direction, uint8_t speed,uint16_t turns, uint8_t steps)
{
	distance_type distance_left;
	    uint16_t steps_left, steps_required_left;

	    if((direction == RIGHT || direction == LEFT) && speed >= 0 && speed <= 100)
	    {
	        Read_distance(LEFT, &distance_left);
	        steps_left = distance_left.turns * MAX_STEPS + distance_left.steps;
	        steps_required_left = turns * MAX_STEPS + steps + steps_left;

	        while(steps_required_left - steps_left > 0)
	        {
	            Read_distance(LEFT, &distance_left);
	            steps_left = distance_left.turns * MAX_STEPS + distance_left.steps;

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

	        Speed_motor(0, RIGHT);
	        Speed_motor(0, LEFT);

	        return 0;
	    }
	    else
	    {
	        return 1;
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
