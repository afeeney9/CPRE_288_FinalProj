#include <stdint.h>
#include <stdbool.h>
#include <Math.h>
#include "timer.h"
#include "lcd.h"
#include "ping.h"
#include "uart.h"
#include "servo.h"
#include "scan.h"
#include "adc.h"
#include "movement.h"
#include <inc/tm4c123gh6pm.h>

int main(void)
{
    timer_init();
    lcd_init();
    lcd_clear();
    servo_init();
    ping_init();
    uart_init();
    adc_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    init_pos();

    while(1){
        char uart_char = uart_receive();
        lcd_putc(uart_char);
        if(uart_char == 'm'){
            scan();
        }else if(uart_char == 'f'){
            move_forward(sensor_data, 550);
        }else if(uart_char == 'w'){
            uart_char = uart_receive();
            move_forward(sensor_data, uart_char*10);
        }else if(uart_char == 'b'){
            move_backwards(sensor_data, 550);
        }else if(uart_char == 's'){
            uart_char = uart_receive();
            move_backwards(sensor_data, uart_char*10);
        }else if(uart_char == 'l'){
            turn_cclockwise(sensor_data, 90);
        }else if(uart_char == 'a'){
            uart_char = uart_receive();
            turn_cclockwise(sensor_data, uart_char);
        }else if(uart_char == 'r'){
            turn_clockwise(sensor_data, 90);
        }else if(uart_char == 'd'){
            uart_char = uart_receive();
            turn_clockwise(sensor_data, uart_char);
        }
    }
	return 0;
}

