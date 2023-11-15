/**
 * lab6_main.c

 */
#include <stdint.h>
#include <stdbool.h>
#include <Math.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "uart.h"
#include "cyBot_Scan.h"
#include "open_interface.h"
#include "movement.h"

//extern volatile char uart_data;
//extern volatile char uart_flag;
int position[3];

void printString(char *arr)
{
    int i = 0;
    while (arr[i])
    {
        uart_sendChar(arr[i]);
        i++;
    }
    uart_sendChar('\n');
    uart_sendChar('\r');
}

void driveTo(int angle, int distance, oi_t *sensor)
{
    if (angle > 90)
    {
        turn_clockwise(sensor, angle - 90);
    }
    else
    {
        turn_ccw(sensor, 90 - angle);
    }
    move_forward(sensor, distance - 6);
}

void scan(int mode, oi_t *sensor)
{
    if (mode < 3)
    {
        int i, j;
        int smallWidth[3] = { 1000000, 25000000, 0 };
        int objects[40];
        int numOfScans = 3;
        float distVals[91];

        cyBOT_Scan_t scan;
        for (i = 0; i <= 180; i += 2)
        {
            int average = 0;
            for (j = 0; j < numOfScans; j++)
            {
                cyBOT_Scan(i, &scan);
                average += ((10000000) * pow(scan.IR_raw_val, -1.769));

            }
            distVals[i / 2] = average / numOfScans;

        }
        i = 1;
        int count = 0;
        int obj = 0;
        while (i <= 91)
        {
            if (distVals[i] - 4 < distVals[i - 1]
                    && distVals[i - 1] < distVals[i] + 4
                    && distVals[i - 1] < 100)
            {
                count++;
            }
            else
            {
                count = 0;
            }

            if (count > 3)
            {
                obj++;
                objects[(obj - 1) * 5] = obj;   //object number
                objects[((obj - 1) * 5) + 1] = i * 2 - 8; //start angle
                int dist = distVals[i - 4] + distVals[i - 3] + distVals[i - 2]
                        + distVals[i - 1];
                while (distVals[i] - 4 < distVals[i - 1]
                        && distVals[i - 1] < distVals[i] + 4
                        && distVals[i - 1] < 100)
                {
                    dist += distVals[i];
                    count++;
                    i++;
                }
                objects[((obj - 1) * 5) + 2] = dist / count; //distance

                objects[((obj - 1) * 5) + 3] = i * 2 - ((i - count) * 2); //width
                objects[((obj - 1) * 5) + 4] = i * 2; //end angle

                if (objects[((obj - 1) * 5) + 3] < smallWidth[0]) //check for smallest width
                {
                    smallWidth[0] = objects[((obj - 1) * 5) + 3]; //width
                    smallWidth[1] = objects[((obj - 1) * 5) + 1]; //angle
                    smallWidth[2] = objects[((obj - 1) * 5) + 2]; //distance
                }
                count = 0;
                i--;
            }
            i++;
        }

        char buffer[100];
        if (mode == 2)
        {
            position[0]= smallWidth[1];
            position[1] = smallWidth[2];
            char dir[18];
            int angle;
            if (smallWidth[1] > 90)
            {
                snprintf(dir, 20, "clockwise");
                angle = smallWidth[1] - 90;
            }
            else
            {
                snprintf(dir, 20,"counter clockwise");
                angle = 90 - smallWidth[1];
            }
            snprintf(
                    buffer,
                    100,
                    "The robot will turn %d %s, then move %d centimeters forward",
                    angle, dir, smallWidth[2]);
            printString(buffer);
        }
        else
        {
            char head[] = "Angle(Degrees)    Distance(m)";
            printString(head);
            for (i = 0; i <= 90; i++)
            {
                snprintf(buffer, 100, "%d                %f", i * 2,
                         distVals[i] / 100);
                printString(buffer);
            }

            char head2[] =
                    "Object#  Start angle      End angle      Distance     Width";
            printString(head2);
            for (i = 0; i < obj; i++)
            {
                snprintf(
                        buffer,
                        100,
                        "%d            %d            %d           %d               %d",
                        objects[i * 5], objects[(i * 5) + 1],
                        objects[(i * 5) + 4], objects[(i * 5) + 2],
                        objects[(i * 5) + 3]);
                printString(buffer);
            }
            snprintf(buffer, 100, "smallest angle location: %d and distance %d",
                     smallWidth[1], smallWidth[2]);
            printString(buffer);

        }
    }
    else
    {
        driveTo( position[0], position[1], sensor);
    }
}



int main(void)
{
cyBOT_init_Scan(0b0111);
right_calibration_value = 290500;
left_calibration_value = 1235500;
oi_t *sensor = oi_alloc();
oi_init(sensor);
//cybot 8
lcd_init();
timer_init();
uart_init();
lcd_clear();
uart_interrupt_init();

char uart_data;
int mode = 1; //if mode = 1 Manual mode, if mode = 2 Autonomous scan mode, if mode = 3 Autonomous drive
printString("you are in Manual Mode");
while (1)
{
    if (uart_byte_to_recive())
    {
        uart_data = uart_receive();
        if (uart_data == 'h' && mode != 1)
        {
            scan(mode, sensor);
            if (mode == 2)
            {
                mode++;
            }
            else
            {
                mode = 2;
            }
            uart_data = 0x00;
        }
        else if (uart_data == 't')
        {
            if (mode > 1)
            {
                mode = 1;
                printString("you are in Manual Mode");
            }
            else
            {
                mode = 2;
                printString("you are in Autonomous Mode");
            }
            uart_data = 0x00;
        }
        else if (uart_data == 'm')
        {
            scan(mode, sensor);
            while (uart_data != 't')
            {
                if (uart_byte_to_recive())
                {
                    uart_data = uart_receive();
                    if (uart_data == 'm')
                    {
                        scan(mode, sensor);
                    }
                    else if (uart_data == 'w')
                    {
                        move_forward(sensor, 5);
                    }else if (uart_data == 's'){
                        move_backward(sensor, 5);
                    }else if (uart_data == 'a'){
                        turn_clockwise(sensor, 12);
                    }else if  (uart_data == 'd'){
                        turn_ccw(sensor, 12);
                    }
                }
            }
        }

    }

}

return 0;
}
