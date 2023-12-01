#include "scan.h"

//servo calibration for cybot00 works with cybot02
int zeroMatch = 311467;
int oneEightyMatch = 284356;
signed int scanOffset = -15;

struct object
{
    int objNum;
    int startAngle;
    int dist;
    int width;
    int endAngle;
};

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
    int matchVal = zeroMatch;
    int decrement = ((zeroMatch - oneEightyMatch) / 180) * 2;
    char i = 0;
    int dataArr[91];
    struct object objArr[5];
    char buffer[100];

    int obj = 0;
    int data;

    while (matchVal > oneEightyMatch)
    {
        timer_waitMillis(100);
        servo_move(matchVal);
        timer_waitMillis(100);
        matchVal -= decrement;
        data = adc_read();
        data = (98223 * (pow(data, -1.152)))/2;
        dataArr[i] = data;
        i++;

    }
    i = 1;
    int count = 0;
    while (i <= 91)
    {
        if (dataArr[i] - 4 < dataArr[i - 1] && dataArr[i - 1] < dataArr[i] + 4
                && dataArr[i - 1] < 61)
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
                    && dataArr[i - 1] < dataArr[i] + 4 && dataArr[i - 1] < 100)
            {
                dist += dataArr[i];
                count++;
                i++;
            }
            objArr[obj - 1].dist = dist / count; //distance
            objArr[obj - 1].endAngle = (i-1) * 2; //end angle
            count = 0;
            i--;
        }
        i++;
    }

    for(i=0; i < obj; i++){
        timer_waitMillis(200);
        servo_move(zeroMatch - (((objArr[i].endAngle +objArr[i].startAngle)/2)+ scanOffset)*(decrement/2));
        timer_waitMillis(800);
        int pulse_time = ping_read();
        pulse_time = (abs(pulse_time) / (2 * 16)) * 0.034;
        objArr[i].dist = pulse_time;
        objArr[i].width = (objArr[i].dist *2* 3 *(objArr[i].endAngle -objArr[i].startAngle))/360;
    }
    char head[] = "Angle(Degrees)    Distance(m)";
    printString(head);
    for (i = 0; i <= 90; i++)
    {
        snprintf(buffer, 100, "%d                %d", i * 2, dataArr[i]);
        printString(buffer);
    }
    snprintf(buffer, 100, "%d", obj);
    printString(buffer);
    char head2[] = "Object#  Start angle      End angle      Distance     Width";
    printString(head2);
    for (i = 0; i < obj; i++)
    {
        snprintf(buffer, 100,
                 "%d            %d            %d           %d               %d",
                 objArr[i].objNum, objArr[i].startAngle, objArr[i].endAngle,
                 objArr[i].dist, objArr[i].width);
        printString(buffer);
        snprintf(buffer, 100, "%d ", (objArr[i].startAngle + objArr[i].endAngle)/2);
        printString(buffer);
        snprintf(buffer, 100, "%d", objArr[i].dist);
        printString(buffer);
        snprintf(buffer, 100, "%d", objArr[i].width);
        printString(buffer);
    }
}
