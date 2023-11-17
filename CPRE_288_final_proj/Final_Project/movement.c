#include "movement.h"
#include "open_interface.h"
#include "lcd.h"
#include "uart.h"
#include "Timer.h"

#define OFFSET 5
#define OneSquare 550


extern struct cyBotPos cyBotPos;
extern struct object objectList[15];
int i;
int objectCount = 0;

//make sure its going straight
//TODO
//        if(((sensor->angle) / .324056)>0 ){
//            oi_setWheels(250, 250 - 12*(sensor->angle/ .324056));
//        }
//        if(((sensor->angle) / .324056)<0 ){
//            oi_setWheels(250 + 12*(sensor->angle/ .324056), 250);
//        }

void moveForwardTillWall(oi_t *sensor, int limit){
    oi_init(sensor);

    //while(sensor -> cliffFrontLeftSignal < 2700 && sensor -> cliffFrontRightSignal < 2700){
    while(cyBotPos.posY < limit && cyBotPos.posX < limit){
        oi_update(sensor);
        oi_setWheels(0, 0);
        timer_waitMillis(500);//scan
        oi_setWheels(250, 250);
        //if there is no object in the path
        move_forward(sensor, OneSquare);
        //else move right and go straight past the square

        cyBotPos.posX += 2;
        cyBotPos.posY += 2;





//        if(objectCount > 0){
//            for(i = 0; i < objectCount; i ++){
//                if((objectList[i].y < cyBotPos.posY+15 && objectList[i].y > cyBotPos.posY-15) && (objectList[i].x < cyBotPos.posX+15 && objectList[i].x > cyBotPos.posX-15)){
//                    oi_setWheels(0, 0);
//                }
//            }
//        }

        lcd_printf("%d, %d \n%c", cyBotPos.posX, cyBotPos.posY, cyBotPos.direction);




    }

    oi_setWheels(0, 0);

}

void fieldScan(oi_t *sensor){
    move_forward(sensor, 500);
    move_backwards(sensor, 20);
    turn_clockwise(sensor, 500);
    timer_waitMillis(500);//scan squares 1 and 2
    move_forward(sensor, OneSquare-330);
//    moveForwardTillWall(sensor, 14);
    moveForwardTillWall(sensor, 4);
    move_forward(sensor, 100);
    turn_clockwise(sensor, 215);
    cyBotPos.posX = 14;
    cyBotPos.posY = 12;
    //check if there no object in path between squares 12 and 14
    cyBotPos.direction = 'E';
    move_forward(sensor, OneSquare-165);
    cyBotPos.posX = 15;
    cyBotPos.posY = 17;
    timer_waitMillis(500);//scan 15 and 17
    oi_setWheels(250, 250);
    //check if there is no object in path between square 15 and 17
    move_forward(sensor, OneSquare);
    cyBotPos.posX = 16;
    cyBotPos.posY = 18;
    timer_waitMillis(500);//scan 16 and 18
    turn_clockwise(sensor, 215);
    cyBotPos.direction = 'S';
    cyBotPos.posX = 18;
    cyBotPos.posY = 17;
    timer_waitMillis(500);//scan 17 and 18
    moveForwardTillWall(sensor, 28);
}

void move_forward(oi_t *sensor, int millimeters){
     oi_init(sensor);
     double sum = 0;
     oi_setWheels(250, 250); // move forward; full speed

     while (sum < millimeters && sensor -> cliffFrontLeftSignal < 2700 && sensor -> cliffFrontRightSignal < 2700) {
     oi_update(sensor);
     lcd_printf("%d, %d \n%c", cyBotPos.posX, cyBotPos.posY, cyBotPos.direction);
     sum += sensor->distance;


     //crater detection
     if(sensor->bumpLeft){
         move_backwards(sensor, 150);
         sum -= 30;
         turn_clockwise(sensor, 250);
         move_forward(sensor, 250);
         turn_cclockwise(sensor, 250);
         oi_setWheels(250,250);
         }
     if(sensor->bumpRight){
         move_backwards(sensor, 150);
         sum -= 30;
         turn_cclockwise(sensor, 250);
         move_forward(sensor, 250);
         turn_clockwise(sensor, 250);
         oi_setWheels(250,250);
         }

     //edge detection
//     if(sensor -> cliffFrontLeftSignal > 2300 || sensor -> cliffFrontRightSignal >2300){
//         move_backwards(sensor, 150);
//         turn_clockwise(sensor, 250);
//         oi_setWheels(250,250);
//
//     }

     }





     oi_setWheels(0, 0); // stop
}
void move_backwards(oi_t *sensor, int millimeters){
     oi_init(sensor);
     double sum = 0;
     oi_setWheels(-250, -250); // move back; full speed

     while (sum > -millimeters) {
     oi_update(sensor);
     lcd_printf("%d, %d \n%c", cyBotPos.posX, cyBotPos.posY, cyBotPos.direction);
     sum += sensor->distance;
     }
     oi_setWheels(0, 0); // stop
}

void turn_clockwise(oi_t *sensor, int degrees){
    oi_init(sensor);
    double angle = 0;
    oi_setWheels(-250, 250);
    int dist = degrees - OFFSET;
    while (angle > -dist) {
    oi_update(sensor);
    angle += (sensor->angle / 0.324056);
    }
    oi_setWheels(0, 0); // stop
}
void turn_cclockwise(oi_t *sensor, int degrees){
    oi_init(sensor);
    double angle = 0;
    oi_setWheels(250, -250);
    int dist = degrees - OFFSET;
    while (angle < dist) {
    oi_update(sensor);
    angle += (sensor->angle / 0.324056);
    }
    oi_setWheels(0, 0); // stop
}

void newObject(int objNum,int startAngle,int dist,int width,int endAngle,int y,int x,char type){
    objectList[objectCount].objNum = objectCount;
    objectList[objectCount].dist = dist;
    objectList[objectCount].width = width;
    objectList[objectCount].endAngle = endAngle;
    objectList[objectCount].y = y;
    objectList[objectCount].x = x;
    objectList[objectCount].type = type;
}

