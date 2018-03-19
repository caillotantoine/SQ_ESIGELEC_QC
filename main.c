#include <msp430g2553.h>
#include "system.h"
#include <stdint.h>
#include "intrinsics.h"
#include "timeout.h"
#include "display.h"
#include "compass.h"
#include "control_motors.h"
#include "scheduler.h"

#include "non_blocking.h"

#define SPEED 30
/*

 * main.c

 */

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

	Clock_graceInit_DCO_12M();
	Init_encoders_distance();
	Init_motors();

	__enable_interrupt();

	spin_steps(RIGHT,30,1,0);

}
