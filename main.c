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
	uint16_t actual_bearing = 0;
	int16_t target_bearing = 0;

	//WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
	init_timeout();
	Clock_graceInit_DCO_12M();
	init_display();
	Init_motors();
	Init_encoders_distance();

	compass_init();
	__enable_interrupt();

	while(1)
	{
		while(Read_compass_16(&actual_bearing) != 0)
		{
			show_string("Err0");
		}
		new_bearing(actual_bearing,900,&target_bearing);
		turn_step_basic_bearing(RIGHT,SPEED*0.5,SPEED,target_bearing);

		while(Read_compass_16(&actual_bearing) != 0)
		{
			show_string("Err0");
		}
		new_bearing(actual_bearing,-900,&target_bearing);
		turn_step_basic_bearing(LEFT,SPEED*0.5,SPEED,target_bearing);

	}
}

