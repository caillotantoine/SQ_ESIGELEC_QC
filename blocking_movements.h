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

uint8_t straight_move(uint8_t direction, uint8_t speed,uint16_t turns, uint8_t steps);
uint8_t spin_steps(uint8_t direction, uint8_t speed,uint16_t turns, uint8_t steps);


#endif /* BLOCKING_FUNCTION_H_ */
