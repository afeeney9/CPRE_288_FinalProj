#include <stdio.h>
#include <math.h>
#include "movement.h"
#include "open_interface.h"
#include "lcd.h"
#include "uart.h"
#include "Timer.h"

#define OFFSET 16
#define OneSquare 550
#define PI 3.14159265358979323846

//Main for movement test
/*
 * #include <stdint.h>
 #include <stdbool.h>
 #include <Math.h>
 #include "open_interface.h"
 #include "movement.h"
 #include "uart.h"
 #include "Timer.h"
 #include "lcd.h"
 #include <inc/tm4c123gh6pm.h>
 #include <inttypes.h>

 int main(void)
 {


 //Initializations
 //-----------------------
 timer_init();
 lcd_init();
 uart_init();
 oi_t *sensor_data = oi_alloc();
 oi_init(sensor_data);
 //-----------------------


 extern struct cyBotPos cyBotPos;
 cyBotPos.posX = 0;
 cyBotPos.posY = 0;
 cyBotPos.direction = 90;

 //check cliff sensor values
 //    while(1){
 //        oi_update(sensor_data);
 //        lcd_printf("%"PRIu16"", sensor_data -> cliffFrontLeftSignal);
 //    }

 char c = ' ';
 while(1){
 c = uart_receive();
 switch(c){
 case 'w':
 move_forward(sensor_data, 100);
 break;
 case 'a':
 turn_cclockwise(sensor_data, 45);
 break;
 case 'd':
 turn_clockwise(sensor_data, 45);
 break;
 }
 }

 //fieldScan(sensor_data);



 return 0;
 }

 */

extern struct cyBotPos cyBotPos;
extern struct object objectList[15];
int i;
int objectCount = 0;
char cyBotPosString[10];

void send_pos(char bump){
    sprintf(cyBotPosString, "%d\r\n", cyBotPos.posX);
    uart_sendStr(cyBotPosString);
    sprintf(cyBotPosString, "%d\r\n", cyBotPos.posY);
    uart_sendStr(cyBotPosString);
    sprintf(cyBotPosString, "%d\r\n", cyBotPos.direction);
    uart_sendStr(cyBotPosString);
    sprintf(cyBotPosString, "%c\r\n", bump);
        uart_sendStr(cyBotPosString);
}

void move_forward(oi_t *sensor, int millimeters)
{
    oi_init(sensor);
    double sum = 0;
    oi_setWheels(250, 250); // move forward; full speed

    while (sum < millimeters)
    {
        oi_update(sensor);
        sum += sensor->distance;

//         //position incrementing
        cyBotPos.posX += cos(cyBotPos.direction * PI / 180) * sensor->distance;
        cyBotPos.posY += sin(cyBotPos.direction * PI / 180) * sensor->distance;

        //crater detection
        if (sensor->bumpLeft)
        {
            oi_setWheels(0, 0);
//            sprintf(cyBotPosString, "%d, %d \r\n%d\r\n'l'\r\n", cyBotPos.posX,
//                    cyBotPos.posY, cyBotPos.direction);
//            uart_sendStr(cyBotPosString);
            send_pos('y');
            return;
        }
        if (sensor->bumpRight)
        {
            oi_setWheels(0, 0);
//            sprintf(cyBotPosString, "%d, %d \r\n%d\r\n'r'\r\n", cyBotPos.posX,
//                    cyBotPos.posY, cyBotPos.direction);
//            uart_sendStr(cyBotPosString);
            send_pos('y');
            return;
        }

        //edge detection
        if (sensor->cliffFrontLeftSignal > 2600
                || sensor->cliffFrontRightSignal > 2600)
        {
            //move_backwards(sensor, 150);
            oi_setWheels(0, 0);
//            sprintf(cyBotPosString, "%d, %d \r\n%d\r\n'e'\r\n", cyBotPos.posX,
//                    cyBotPos.posY, cyBotPos.direction);
//            uart_sendStr(cyBotPosString);
            send_pos('c');
            return;
        }
<<<<<<< HEAD
        lcd_printf("%d, %d \n%d", cyBotPos.posX, cyBotPos.posY,
                   cyBotPos.direction);

=======

        //hole detection
        if(sensor -> cliffFrontLeftSignal < 400 || sensor -> cliffFrontRightSignal < 400){
            move_backwards(sensor, 50);
            oi_setWheels(0,0);
            // sprintf(cyBotPosString, "%d, %d \r\n%d\r\n'h'\r\n", cyBotPos.posX, cyBotPos.posY, cyBotPos.direction);
            // uart_sendStr(cyBotPosString);
            send_pos('h');
            return;
        }

        lcd_printf("%d, %d \n%d", cyBotPos.posX, cyBotPos.posY,
                   cyBotPos.direction);

>>>>>>> b0721cb0eb8d2392a739b01786714d296a6b71d9
    }
    lcd_printf("%d, %d \n%d", cyBotPos.posX, cyBotPos.posY, cyBotPos.direction);
//     sprintf(cyBotPosString, "%d, %d \r\n%d\r\n's'\r\n", cyBotPos.posX, cyBotPos.posY, cyBotPos.direction);
//     uart_sendStr(cyBotPosString);
    oi_setWheels(0, 0); // stop
    send_pos('n');
}
void move_backwards(oi_t *sensor, int millimeters)
{
    oi_init(sensor);
    double sum = 0;
    oi_setWheels(-250, -250); // move back; full speed

    while (sum > -millimeters)
    {
        oi_update(sensor);
<<<<<<< HEAD
=======

        //position incrementing
        cyBotPos.posX += cos(cyBotPos.direction*PI /180) * sensor->distance;
        cyBotPos.posY += sin(cyBotPos.direction*PI /180) * sensor->distance;
        
>>>>>>> b0721cb0eb8d2392a739b01786714d296a6b71d9
        lcd_printf("%d, %d \n%d", cyBotPos.posX, cyBotPos.posY,
                   cyBotPos.direction);
        sum += sensor->distance;
    }
    oi_setWheels(0, 0); // stop
    send_pos('n');
}

void turn_clockwise(oi_t *sensor, int degrees)
{
    oi_init(sensor);
    double angle = 0;
    oi_setWheels(-250, 250);
    int dist = degrees - OFFSET;
    cyBotPos.direction -= degrees;
    while (angle > -dist)
    {
        oi_update(sensor);
        //angle += (sensor->angle / 0.324056);
        angle += (sensor->angle);
        if (cyBotPos.direction < 0)
        {
            cyBotPos.direction = 360 + cyBotPos.direction;
        }
        lcd_printf("%d, %d \n%d", cyBotPos.posX, cyBotPos.posY,
                   cyBotPos.direction);

    }

    oi_setWheels(0, 0); // stop
    send_pos('n');
}
void turn_cclockwise(oi_t *sensor, int degrees)
{
    oi_init(sensor);
    double angle = 0;
    oi_setWheels(250, -250);
    int dist = degrees - OFFSET;
    cyBotPos.direction += degrees;
    while (angle < dist)
    {
        oi_update(sensor);
        //angle += (sensor->angle / 0.324056);
        angle += (sensor->angle);
        if (cyBotPos.direction >= 360)
        {
            cyBotPos.direction = cyBotPos.direction % 360;
        }
        lcd_printf("%d, %d \n%d", cyBotPos.posX, cyBotPos.posY,
                   cyBotPos.direction);

    }
    oi_setWheels(0, 0); // stop
    send_pos('n');
}

//make sure its going straight
//TODO
//        if(((sensor->angle) / .324056)>0 ){
//            oi_setWheels(250, 250 - 12*(sensor->angle/ .324056));
//        }
//        if(((sensor->angle) / .324056)<0 ){
//            oi_setWheels(250 + 12*(sensor->angle/ .324056), 250);
//        }

void moveForwardTillWall(oi_t *sensor, int limit)
{
    oi_init(sensor);

    //while(sensor -> cliffFrontLeftSignal < 2700 && sensor -> cliffFrontRightSignal < 2700){
    while (cyBotPos.posY < limit && cyBotPos.posX < limit)
    {
        oi_update(sensor);
        oi_setWheels(0, 0);
        timer_waitMillis(500); //scan
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

        lcd_printf("%d, %d \n%d", cyBotPos.posX, cyBotPos.posY,
                   cyBotPos.direction);

    }

    oi_setWheels(0, 0);

}

void fieldScan(oi_t *sensor)
{
    move_forward(sensor, 500);
    move_backwards(sensor, 20);
    turn_clockwise(sensor, 500);
    timer_waitMillis(500); //scan squares 1 and 2
    move_forward(sensor, OneSquare - 330);
//    moveForwardTillWall(sensor, 14);
    moveForwardTillWall(sensor, 4);
    move_forward(sensor, 100);
    turn_clockwise(sensor, 225);
    cyBotPos.posX = 14;
    cyBotPos.posY = 12;
    //check if there no object in path between squares 12 and 14
    cyBotPos.direction = 'E';
    move_forward(sensor, OneSquare - 165);
    cyBotPos.posX = 15;
    cyBotPos.posY = 17;
    timer_waitMillis(500); //scan 15 and 17
    oi_setWheels(250, 250);
    //check if there is no object in path between square 15 and 17
    move_forward(sensor, OneSquare);
    cyBotPos.posX = 16;
    cyBotPos.posY = 18;
    timer_waitMillis(500); //scan 16 and 18
    turn_clockwise(sensor, 225);
    cyBotPos.direction = 'S';
    cyBotPos.posX = 18;
    cyBotPos.posY = 17;
    timer_waitMillis(500); //scan 17 and 18
    moveForwardTillWall(sensor, 28);
}
