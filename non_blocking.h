/*
 * non_blocking.h
 *
 *  Created on: 7 mars 2018
 *      Author: a001220-dev
 */

#ifndef SQ_ESIGELEC_QC_NON_BLOCKING_H_
#define SQ_ESIGELEC_QC_NON_BLOCKING_H_

#include "control_encoders.h"

#define FORWARD     1
#define BACKWARD    0

/* Straight Movement */
uint8_t nb_straight_move(uint8_t direction, uint8_t speed, uint16_t turns, uint8_t steps);
uint8_t check_stop_steps();

/* Spin Movements */
uint8_t nb_spin_steps(uint8_t direction, uint8_t speed, uint16_t turns, uint8_t steps);
uint8_t nb_spin_bearing(uint8_t direction, uint8_t speed, uint16_t target_bearing);

uint8_t check_stop_bearing();

/* Turns Movements */
int8_t nb_turn_step_basic_bearing(uint8_t direction, int8_t innerWspeed, int8_t outerWspeed, uint16_t target_bearing);
int8_t nb_turn_step_plus_bearing(uint8_t runDirection, uint8_t direction, int8_t innerWspeed, int8_t outerWspeed, uint16_t target_bearing);

#endif /* SQ_ESIGELEC_QC_NON_BLOCKING_H_ */
