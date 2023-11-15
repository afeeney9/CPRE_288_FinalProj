/*
 * movement.c
 *
 *  Created on: Sep 7, 2023
 *      Author: afeeney9
 */
#include "movement.h"
#include "Timer.h"
#include "open_interface.h"

#define OFFSET 10

void move_forward(oi_t *sensor, int centimeters){
        oi_init(sensor);
         double sum = 0;
         oi_setWheels(150, 150); // move forward; full speed
         while (sum < centimeters*10) {
             oi_update(sensor);
             sum += sensor->distance;
         }
         oi_setWheels(0, 0); // stop
         //oi_free(sensor_data);

};


void turn_clockwise(oi_t *sensor, int degrees){
    oi_init(sensor);
    double angle = 0;
    oi_setWheels(250, -250); 
    while (angle < degrees-OFFSET){
        oi_update(sensor);
        angle += (sensor->angle);
    }
    oi_setWheels(0, 0); // stop
    //oi_free(sensor_data);
};

void turn_ccw(oi_t *sensor, int degrees){
    oi_init(sensor);
    double angle = 0;
    oi_setWheels(-250, 250); 
    while (abs(angle) < degrees-OFFSET){
        oi_update(sensor);
        angle += (sensor->angle);
    }
    oi_setWheels(0, 0); // stop
    //oi_free(sensor);
};
void move_backward(oi_t *sensor, int centimeters){
         oi_init(sensor);
         double sum = 0;
         oi_setWheels(-250, -250); // move backward
         while (sum < centimeters*10) {
             oi_update(sensor);
             sum += abs(sensor->distance);
         }
         oi_setWheels(0, 0); // stop
         //oi_free(sensor);

};
