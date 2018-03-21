/*
 * Turn_path.h
 *
 *  Created on: 19 mars 2018
 *      Author: Antoine
 */

#ifndef SQ_ESIGELEC_QC_TURN_PATH_H_
#define SQ_ESIGELEC_QC_TURN_PATH_H_

#include <msp430g2553.h>
#include "stdint.h"
#include "control_encoders.h"

int8_t turn_step_basic(uint8_t direction, int8_t innerWspeed, int8_t outerWspeed, uint16_t outerWturns, uint8_t outerWsteps);
int8_t turn_step_plus(uint8_t runDirection, uint8_t direction, uint8_t innerWspeed, uint8_t outerWspeed, uint16_t outerWturns, uint8_t outerWsteps);
uint32_t distance2steps(distance_type distance);
int8_t check_stops_turning();
int8_t turn_step_basic_nb_start(uint8_t direction, int8_t innerWspeed, int8_t outerWspeed, uint16_t outerWturns, uint8_t outerWsteps);
int8_t turn_step_plus_nb(uint8_t runDirection, uint8_t direction, uint8_t innerWspeed, uint8_t outerWspeed, uint16_t outerWturns, uint8_t outerWsteps);

#endif /* SQ_ESIGELEC_QC_TURN_PATH_H_ */
