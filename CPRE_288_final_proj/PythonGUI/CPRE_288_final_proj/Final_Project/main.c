#include <stdint.h>
#include <stdbool.h>
#include <Math.h>
#include "timer.h"
#include "lcd.h"
#include "ping.h"
#include "uart.h"
#include "servo.h"
#include <inc/tm4c123gh6pm.h>

int main(void)
{
    timer_init();
    lcd_init();
    lcd_clear();
    servo_init();
    ping_init();
    uart_init();

    while(1){
        char uart_char = uart_receive();
        lcd_putc(uart_char);
    }
	return 0;
}
