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

#define SPEED 30
#define CENT_MS 1200000
/*

 * main.c

 */

void main(void) {

    uint16_t actual_bearing = 0;
    int16_t target_bearing = 0;

    //WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
    init_timeout();
    Clock_graceInit_DCO_12M();
    init_display();
    Init_encoders_distance();
    Init_motors();
    compass_init();

    while(1)
    {
        /*if it is ok, display the number*/
        if(Read_compass_16(&actual_bearing) == 0)
        {
            if(new_brearing(actual_bearing, 900, &target_bearing) == 0)
            {
                show_number(target_bearing);
            }
            else
            {
                show_string("Err1");
            }
        }
        else
        {
            show_string("Err0");
        }
        _delay_cycles(CENT_MS);
    }


    __enable_interrupt();


    //spin_steps(RIGHT,30,1,0);

}
