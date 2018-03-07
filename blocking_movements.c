#include "blocking_movements.h"
#include "../display.h"
#include "../control_motors.h"
#include "../control_encoders.h"

uint8_t straight_move(uint8_t direction, uint8_t speed, uint8_t steps, uint16_t turns)
{
    distance_type distance_left, distance_right;
    uint16_t steps_right, steps_left, steps_required_left, steps_required_right;
    uint16_t initial_steps_difference, steps_difference;

    if((direction == FORWARD || direction == BACKWARD) && (speed >= 0 || speed <= 100))
    {
        Read_distance(LEFT, &distance_left);
        steps_left = distance_left.turns * MAX_STEPS + distance_left.steps;
        steps_required_left = turns * MAX_STEPS + steps + steps_left;

        Read_distance(RIGHT, &distance_left);
        steps_right = distance_right.turns * MAX_STEPS + distance_right.steps;
        steps_required_right = turns * MAX_STEPS + steps + steps_right;

        initial_steps_difference = steps_required_left - steps_required_right;

        while(steps_required_left > steps_left && steps_required_right > steps_right)
        {
            Read_distance(LEFT, &distance_left);
            steps_left = distance_left.turns * MAX_STEPS + distance_left.steps;

            Read_distance(RIGHT, &distance_left);
            steps_right = distance_right.turns * MAX_STEPS + distance_right.steps;

            steps_difference = steps_left - steps_right;

            if(steps_difference - initial_steps_difference > 1)
            {
                Speed_motor(speed-20, RIGHT);
                Speed_motor(speed, LEFT);
            }
            else if(steps_difference - initial_steps_difference < -1)
            {
                Speed_motor(speed, RIGHT);
                Speed_motor(speed-20, LEFT);
            }
            else
            {
                Speed_motor(speed, RIGHT);
                Speed_motor(speed, LEFT);
            }
        }

        return 0;
    }
    else
    {
        init_display();
        show_string("ErrP");
        return 1;
    }
}
