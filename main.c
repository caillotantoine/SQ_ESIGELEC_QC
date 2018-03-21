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
#include "control_encoders.h"

#include "non_blocking.h"
#include "blocking_movements.h"
#include "Turn_path.h"

#define SPEED 30
#define CENT_MS 1200000
/*

 * main.c

 */

void main(void) {
    distance_type dist;
    uint8_t in_movement = 0, direction = 0;

    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
    Clock_graceInit_DCO_12M();
    init_display();
    Init_motors();
    Init_encoders_distance();

    __enable_interrupt();

    while(1)
    {

        if(in_movement == 0){
            if(direction == FORWARD)/* Move forward */
            {
                turn_step_plus_nb(FORWARD, RIGHT, 30, 50, 3, 4);
                direction = BACKWARD;
                in_movement = 1;
            }
            else
            {
                turn_step_plus_nb(BACKWARD, RIGHT, 30, 50, 3, 4);
                direction = FORWARD;
                in_movement = 1;
            }
        }

        /*Every 2ms we enter in the condition */
        if(check_and_clear_Tick_out() == 1)
        {
            if(check_stops_turning() == 0)
            {
                //show_string("o  o");
                in_movement = 0;
            }

        }

        /* Do something to show that we are using not blocking functions */
        Read_distance(LEFT, &dist);                                 /* We read the distance on the left wheel */
        show_number(dist.turns);                                    /* We print the number of turn we made on the display */

    }
}
