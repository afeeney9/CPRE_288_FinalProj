/**
 * lab6_main.c

 */
#include <adc.h>
#include <stdint.h>
#include <stdbool.h>
#include <Math.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"
#include "movement.h"
#include "cyBot_Scan.h"
#include <inc/tm4c123gh6pm.h>

struct object
{
    int objNum;
    int startAngle;
    int dist;
    int width;
    int endAngle;
};

int data, dist;
int dataArr[91];
struct object objArr[5];
int smallWidth[3] = { 1000000, 25000000, 100000 };
char buffer[100];
int position[3];

void printString(char *arr)
{
    int i = 0;
    lcd_clear();
    while (arr[i])
    {
        uart_sendChar(arr[i]);
        i++;
    }
    uart_sendChar('\n');
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

void ADCscan(int mode, oi_t *sensor)
{
    int i;
    int obj = 0;
    cyBOT_Scan_t scan;
    if (mode < 3)
    {

        for (i = 0; i <= 180; i += 2)
        {
            data = adc_read();
            dist = 98223 * (pow(data, -1.152));
            dataArr[i / 2] = dist;
            cyBOT_Scan(i, &scan);
        }
        i = 1;
        int count = 0;
        while (i <= 91)
        {
            if (dataArr[i] - 4 < dataArr[i - 1]
                    && dataArr[i - 1] < dataArr[i] + 4 && dataArr[i - 1] < 100)
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
                objArr[obj - 1].objNum = obj;   //object number
                objArr[obj - 1].startAngle = i * 2 - 8; //start angle
                int dist = dataArr[i - 4] + dataArr[i - 3] + dataArr[i - 2]
                        + dataArr[i - 1];
                while (dataArr[i] - 4 < dataArr[i - 1]
                        && dataArr[i - 1] < dataArr[i] + 4
                        && dataArr[i - 1] < 100)
                {
                    dist += dataArr[i];
                    count++;
                    i++;
                }
                objArr[obj - 1].dist = dist / count; //distance

                objArr[obj - 1].width = i * 2 - ((i - count) * 2); //width
                objArr[obj - 1].endAngle = i * 2; //end angle

                if (objArr[obj - 1].width < smallWidth[0]) //check for smallest width
                {
                    smallWidth[0] = objArr[obj - 1].width; //width
                    smallWidth[1] = objArr[obj - 1].startAngle; //angle
                    smallWidth[2] = objArr[obj - 1].dist; //distance
                }
                count = 0;
                i--;
            }
            i++;
        }
    }
    if (mode == 1)
    {
        char head[] = "Angle(Degrees)    Distance(m)";
        printString(head);
        for (i = 0; i <= 90; i++)
        {
            snprintf(buffer, 100, "%d                %d", i * 2, dataArr[i]);
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
                    objArr[i].objNum, objArr[i].startAngle, objArr[i].endAngle,
                    objArr[i].dist, objArr[i].width);
            printString(buffer);
        }
        snprintf(buffer, 100, "smallest angle location: %d and distance %d",
                 smallWidth[1], smallWidth[2]);
        printString(buffer);
        cyBOT_Scan(smallWidth[1], &scan);
    }
    else if (mode == 2)
    {
        position[0] = smallWidth[1];
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
            snprintf(dir, 20, "counter clockwise");
            angle = 90 - smallWidth[1];
        }
        snprintf(buffer, 100,
                 "The robot will turn %d %s, then move %d centimeters forward",
                 angle, dir, smallWidth[2]);
        printString(buffer);
    }
    else
    {
        driveTo(position[0], position[1] -3, sensor);
    }
    uart_sendChar('\n');
    uart_sendChar('\n');
    uart_sendChar('\n');
    uart_sendChar('\n');
    uart_sendChar('\n');
    uart_sendChar('\n');
    uart_sendChar('\n');
    uart_sendChar('\n');
    uart_sendChar('\n');
    uart_sendChar('\n');
}

void part4(oi_t *sensor)
{
    char my_data;       // Variable to get bytes from Client
    int mode = 1; //if mode = 1 Manual mode, if mode = 2 Autonomous scan mode, if mode = 3 Autonomous drive

    // Write to LCD so that we know the program is running
    lcd_printf("Running");

    while (1)
    {
        my_data = uart_receive(); // Get first byte of the command from the Client
        if (my_data == 'h' && mode != 1)
        {
            ADCscan(mode, sensor);
            if (mode == 2)
            {
                mode++;
            }
            else
            {
                mode = 2;
            }
            my_data = 0x00;
        }
        else if (my_data == 't')
        {
            if (mode > 1)
            {
                mode = 1;
                lcd_clear();
                lcd_puts("you are in Manual Mode");
            }
            else
            {
                mode = 2;
                lcd_clear();
                lcd_puts("you are in Autonomous Mode");
            }
            my_data = 0x00;
        }
        else if (mode == 1)
        {
            while (my_data != 't')
            {
                my_data = uart_receive();
                if (my_data == 'm')
                {
                    ADCscan(mode, sensor);
                }
                else if (my_data == 'w')
                {
                    move_forward(sensor, 5);
                }
                else if (my_data == 's')
                {
                    move_backward(sensor, 5);
                }
                else if (my_data == 'a')
                {
                    turn_clockwise(sensor, 12);
                }
                else if (my_data == 'd')
                {
                    turn_ccw(sensor, 12);
                }
                else if (my_data == 't')
                {
                    lcd_clear();
                    mode = 2;
                    lcd_puts("you are in Autonomous Mode");
                }
            }
        }
    }
}

int main(void)
{
//Question 1: we will use GPIO reg B because it contains the pin associated with AIN10
///Question 2: we will configure AIN10 (pin 4 of port B) to be analog
//Question 3: We will use the hardware approach to do sampling average and set ADCSAC to 0x1
//Question 4: You should enable any interrupts that you want to trigger an interrupt in the ADC_IM register
//and set bit 14 in the NVIC_EN0_R because that is what corresponds to ADC0 SS0 (pg104 DS)
    timer_init();
    adc_init();
    lcd_init();
    lcd_clear();
    uart_init();

    cyBOT_init_Scan(0b0111);
    right_calibration_value = 290500;
    left_calibration_value = 1235500;
    oi_t *sensor = oi_alloc();
    oi_init(sensor);

    part4(sensor);

//PART 3
//    while(1){
//        char c = uart_receive();
//        if(c == 'm'){
//            ADCscan(1, sensor);
//        }
//
//    }

//PART 2
//    data = adc_read();
//    dist = 98223 * (pow(data, -1.152));
//    snprintf(dataArr, 100, "The sensor read %d The item is %d cm away", data,
//             dist);
//    lcd_puts(dataArr);

    return 0;
}

