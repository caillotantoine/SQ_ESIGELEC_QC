/*
 * blocking_function.h
 *
 *  Created on: 7 mars 2018
 *      Author: Antoine
 */

#ifndef BLOCKING_FUNCTION_H_
#define BLOCKING_FUNCTION_H_

#include <stdint.h>
#include <msp430g2553.h>

#define FORWARD     1
#define BACKWARD    0

/* Delta bearing in degree TIMES 10. So 5° is now 50 */
#define DELTA_BEARING 100

/* Straight Movements */
uint8_t straight_move(uint8_t direction, uint8_t speed,uint16_t turns, uint8_t steps);

/* Spin Movements */
uint8_t spin_steps(uint8_t direction, uint8_t speed,uint16_t turns, uint8_t steps);
uint8_t spin_bearing(uint8_t direction, uint8_t speed, uint16_t target_bearing);

void stop(uint16_t ms);

#endif /* BLOCKING_FUNCTION_H_ */
