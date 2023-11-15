/*
 * movement.h
 *
 *  Created on: Sep 7, 2023
 *      Author: afeeney9
 */
#include "open_interface.h"

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

void move_forward(oi_t *sensor, int centimeters);
void move_backward(oi_t *sensor, int centimeters);
void turn_clockwise(oi_t *sensor, int degrees);
void turn_ccw(oi_t *sensor, int degrees);



#endif /* MOVEMENT_H_ */
