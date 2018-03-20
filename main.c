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
    //uint16_t actual_bearing = 0;
    //int16_t target_bearing = 0;

    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
    Clock_graceInit_DCO_12M();
    init_display();
    Init_motors();
    Init_encoders_distance();
    __enable_interrupt();

    show_number(0);
    __delay_cycles(12000000);
    show_number((uint16_t) -turn_step_plus(FORWARD, RIGHT, 30, 50, 3, 4));
    __delay_cycles(12000000);
    show_number((uint16_t) -turn_step_plus(BACKWARD, RIGHT, 30, 50, 3, 4));
    __delay_cycles(12000000);
    //turn_step_plus(BACKWARD, RIGHT, 30, 50, 3, 4);

}

