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


    static uint8_t badLandingSpotNumNotes = 5;
    static uint8_t badLandingSpotNotes[5] = {72,76,72,76,72} ;
    static uint8_t badLandingSpotDurations[5] = {8,8,8,8,8};

    static uint8_t scanEndSpotNumNotes = 5;
     static uint8_t scanEndSpotNotes[5] = {50,70,50,70,50};
     static uint8_t scanEndSpotDurations[5] = {16,16,16,16,16};

    static uint8_t goodLandingSpotNumNotes = 53;
    static uint8_t goodLandingSpotNotes[53] = {55,60,64,60,60,60,60,65,65,55,65,55,60,64,55,
            57,59,60,56,58,60,55,60,64,62,64,62,65,
            62,65,65,65,65,64,60,60,60,58,62,64,
            60,55,55,60,55,65,59,65,60,60,60,60,60};
    static uint8_t goodLandingSpotDurations[53] = {18, 18, 18, 18, 18, 18,  9,  9, 18, 18, 45,  9, 54, 54, 54, 9,  9,  9,  9,  9,  9, 54, 36, 18, 54, 45, 9,
                                                   54, 54, 54,  9,  9,  9,  9,  9,  9, 54, 36, 18, 54, 45, 9, 54, 54, 54, 18, 18,  9,  9, 54, 54, 54, 18};


    while(1){
        char uart_char = uart_receive();
        lcd_putc(uart_char);
        if(uart_char == 'm'){
            oi_loadSong(1,badLandingSpotNumNotes, badLandingSpotNotes, badLandingSpotDurations);
            oi_play_song(1);
            scan();
            oi_loadSong(2, scanEndSpotNumNotes, scanEndSpotNotes, scanEndSpotDurations);
            oi_play_song(2);
        }else if(uart_char == 'f'){
            move_forward(sensor_data, 575);
        }else if(uart_char == 'w'){
            uart_char = uart_receive();
            move_forward(sensor_data, uart_char*10);
        }else if(uart_char == 'b'){
            move_backwards(sensor_data, 575);
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
        }else if(uart_char == 'g'){
            oi_loadSong(0, goodLandingSpotNumNotes, goodLandingSpotNotes, goodLandingSpotDurations);
            oi_play_song(0);
        }
    }
    return 0;
}
