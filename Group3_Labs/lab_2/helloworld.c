#include "open_interface.h"
#include "movement.h"
#include "lcd.h"
#include "cyBot_uart.h"

void main() {

    oi_t *sensor = oi_alloc();
    oi_init(sensor);
             double sum = 0;
             while (sum < 2100) {
                 oi_setWheels(250, 250);
                 oi_update(sensor);
                 if (sensor->bumpLeft) {
                             move_backward(sensor, 15);
                             sum= sum - 15;
                             turn_ccw(sensor, 90);
                             move_forward(sensor, 25);
                             turn_clockwise(sensor, 90);
                 }else if(sensor->bumpRight){
                             move_backward(sensor, 15);
                             sum= sum - 15;
                             turn_clockwise(sensor, 90);
                             move_forward(sensor, 25);
                             turn_ccw(sensor, 90);
                 }
                 sum += sensor->distance;
             }
             oi_setWheels(0, 0); // stop
             //oi_free(sensor_data);
    oi_free(sensor);

/**

    cyBot_uart_init();
    lcd_init();
    oi_t *sensor = oi_alloc();
    oi_init(sensor);
    while(1){
        char x = cyBot_getByte();
        cyBot_sendByte(x);
        lcd_putc(x);
        if(x == 'w'){
            move_forward(sensor, 10);
        }else if(x == 's'){
            move_backward(sensor, 10);
        }else if(x == 'a'){
            turn_clockwise(sensor, 90);
            move_forward(sensor,10);
        }else if(x == 'd'){
            turn_ccw(sensor, 90);
            move_forward(sensor, 10);
        }else if(x == 't'){
            oi_free(sensor);
            break;
        }else if(x == 'm'){
            char arr[] = "\nGot an M";
            int i =0;
            while(arr[i]){
                cyBot_sendByte(arr[i]);
                i++;
            }
        }
    }
    **/
}
