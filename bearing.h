/*
 * bearing.h
 *
 *  Created on: 19 mars 2018
 *      Author: Antoine
 */

#ifndef SQ_ESIGELEC_QC_BEARING_H_
#define SQ_ESIGELEC_QC_BEARING_H_

#include <msp430g2553.h>
#include "stdint.h"

/* Be careful, angle are multiplied by 10. so 90.1° would be 901. */
uint8_t new_brearing(uint16_t actual_bearing, int16_t relative_angle, int16_t* new_bearing);

#endif /* SQ_ESIGELEC_QC_BEARING_H_ */
