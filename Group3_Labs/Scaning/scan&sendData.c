/**
 * lab10_main.c

 */
#include <stdint.h>
#include <stdbool.h>
#include <Math.h>
#include "timer.h"
#include "lcd.h"
#include "button.h"
#include "ping.h"
#include "uart.h"
#include "servo.h"
#include <inc/tm4c123gh6pm.h>

char buffer[100];
volatile struct object objArr[15];
volatile struct currentCyPos;

//servo calibration for cybot00
int zeroMatch = 311467;
int oneEightyMatch = 284356;

struct object
{
    int objNum;
    int startAngle;
    int dist;
    int width;
    int endAngle;
    char y;
    char x;
    char type;
};

struct cyBotPos{
    char posX;
    char posY;
    char direction;
}

volatile enum
{
    LOW, HIGH, DONE
} state;
volatile unsigned int rising_time;
volatile unsigned int falling_time;

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


void scan()
{
    int pulse_time;
    int matchVal = zeroMatch;
    int decrement = ((zeroMatch - oneEightyMatch) / 180) * 2;
    char i = 0;
    int dataArr[91];

    while (matchVal > oneEightyMatch)
    {
        for (i = 0; i <= 180; i += 2)
        {
            timer_waitMillis(100);
            //adc get distance
            data = adc_read();
            dist = 98223 * (pow(data, -1.152));
            dataArr[i / 2] = dist;
            timer_waitMillis(100);
            matchVal -= decrement;
            servo_move(matchVal);
        }
        i = 1;
        int count = 0;
        while (i <= 91)
        {
            if (dataArr[i] - 2 < dataArr[i - 1]
                    && dataArr[i - 1] < dataArr[i] + 2 && dataArr[i - 1] < 50)
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
                    smallWidth[1] = (objArr[obj - 1].startAngle
                            + objArr[obj - 1].endAngle) / 2; //angle
                    smallWidth[2] = objArr[obj - 1].dist; //distance

                }
                count = 0;
                i--;
            }
            i++;
        }

        for(i=0; i < )
        //go back to objects for better distance
        pulse_time = ping_read();
        pulse_time = (abs(pulse_time) / (2 * 16)) * 0.034;
        dataArr[i] = pulse_time;
    }
}

int main(void)
{

    timer_init();
    lcd_init();
    lcd_clear();
    servo_init();
    button_init();
    ping_init();
    uart_init();
    TIMER3B_Handler();

    while (1)
    {
        char uart_char = uart_receive();
        if (uart_char == 'm')
            scan();

    }

    return 0;
}

