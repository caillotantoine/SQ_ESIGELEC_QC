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

int8_t turn_step_basic(uint8_t direction, int8_t innerWspeed, int8_t outerWspeed, uint16_t outerWturns, uint8_t outerWsteps)
{
    distance_type distance_runned;
    uint16_t step_done, step_required;

    if((innerWspeed >= -100) && (innerWspeed <= 100) && (outerWspeed >= -100) && (outerWspeed <= 100))
    {
        if(direction == LEFT)
        {
            /* outer wheel is the right one */
            Read_distance(RIGHT, &distance_runned);
            step_done = distance2steps(distance_runned);
            step_required =  + (outerWturns * MAX_STEPS) + outerWsteps;
            while((step_required - step_done) > 0)
            {
                Read_distance(RIGHT, &distance_runned);
                step_done = distance2steps(distance_runned);

                Speed_motor(outerWspeed, RIGHT);
                Speed_motor(innerWspeed, LEFT);
            }
        }
        else if (direction == RIGHT)
        {
            /* outer wheel is the left one */
            Read_distance(LEFT, &distance_runned);
            step_required = distance2steps(distance_runned) + (outerWturns * MAX_STEPS) + outerWsteps;

            while((step_required - step_done) > 0)
            {
                Read_distance(LEFT, &distance_runned);
                step_done = distance2steps(distance_runned);

                Speed_motor(outerWspeed, LEFT);
                Speed_motor(innerWspeed, RIGHT);
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

uint16_t distance2steps(distance_type distance)
{
    return ((uint16_t) distance.turns * (uint16_t) MAX_STEPS) + (uint16_t) distance.steps;
}
