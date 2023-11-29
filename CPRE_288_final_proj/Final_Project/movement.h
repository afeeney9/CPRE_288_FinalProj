/*
 * movement.h
 *
 *  Created on: Sep 7, 2023
 *      Author: esivets
 */
#include "open_interface.h"

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

    struct cyBotPos{
        int posX;
        int posY;
        int direction;
    };



    struct cyBotPos cyBotPos;

void moveForwardTillWall(oi_t *sensor, int limit);
void fieldScan(oi_t *sensor);
void move_forward(oi_t *sensor, int millimeters);
void move_backwards(oi_t *sensor, int millimeters);
void turn_clockwise(oi_t *sensor, int degrees);
void turn_cclockwise(oi_t *sensor, int degrees);
void init_pos(void);
#endif /* MOVEMENT_H_ */
