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

#define SPEED 25
#define CENT_MS 1200000
/*

 * main.c

 */

void main(void) {

	uint16_t actual_bearing =0, target_bearing = 0;
	int to_right=1;

	//WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
	init_timeout();
	Clock_graceInit_DCO_12M();
	init_display();
	compass_init();
	Init_motors();

	__enable_interrupt();

	while(1){

		while(Read_compass_16(&actual_bearing) != 0)
		{
			show_string("Err0");
		}

		if(to_right == 1)
		{
			new_bearing(actual_bearing,900,&target_bearing);
			spin_bearing(RIGHT,SPEED,target_bearing);
			to_right = 1 - to_right;
		}
		else
		{
			new_bearing(actual_bearing,-450,&target_bearing);
			spin_bearing(LEFT,SPEED,target_bearing);
			to_right = 1 - to_right;
		}


		__delay_cycles(5*CENT_MS);
	}

}

