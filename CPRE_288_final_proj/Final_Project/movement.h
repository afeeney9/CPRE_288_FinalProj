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
        char direction; // N, S, E, W
    };

    struct object{
        int objNum;
        int startAngle;
        int dist;
        int width;
        int endAngle;
        int y;
        int x;
        char type;
    };
    struct object objectList[15];

    struct cyBotPos cyBotPos;

void newObject(int objNum,int startAngle,int dist,int width,int endAngle,int y,int x,char type);
void moveForwardTillWall(oi_t *sensor, int limit);
void fieldScan(oi_t *sensor);
void move_forward(oi_t *sensor, int millimeters);
void move_backwards(oi_t *sensor, int millimeters);
void turn_clockwise(oi_t *sensor, int degrees);
void turn_cclockwise(oi_t *sensor, int degrees);
#endif /* MOVEMENT_H_ */
