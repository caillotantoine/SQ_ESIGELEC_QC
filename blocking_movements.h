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

uint8_t straight_move(uint8_t direction, uint8_t speed, uint8_t steps, uint16_t turns);



#endif /* BLOCKING_FUNCTION_H_ */
