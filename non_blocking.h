/*
 * non_blocking.h
 *
 *  Created on: 7 mars 2018
 *      Author: a001220-dev
 */

#ifndef SQ_ESIGELEC_QC_NON_BLOCKING_H_
#define SQ_ESIGELEC_QC_NON_BLOCKING_H_

#include "../control_encoders.h"

#define FORWARD     1
#define BACKWARD    0

uint8_t nb_straight_move(uint8_t direction, uint8_t speed, uint16_t turns, uint8_t steps);
uint8_t check_stop_steps();

#endif /* SQ_ESIGELEC_QC_NON_BLOCKING_H_ */
