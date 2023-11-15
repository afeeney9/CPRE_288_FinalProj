/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Describtion: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include "string.h"


int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen fucntions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	//lcd_init();   // Initialize the the LCD screen.  This also clears the screen.

	// Clear the LCD screen and print "Hello, world" on the LCD
	while(1){
	    char arr[] = "                    Microcontrollers are lots of fun!";
	    char arr2[21];
        int i = 0;
        lcd_init();
        for(i=0; i < strlen(arr); i++){
            strcpy(arr2, arr +i);
            arr2[20]='\0';
            timer_waitMillis(300);
            lcd_init();
            lcd_puts(arr2);
        }
        timer_waitMillis(300);
        for(i=0; i < 20; i++){
            arr2[i]=' ';
            lcd_puts(arr2);
        }
        timer_waitMillis(300);
	}


	// lcd_puts("Hello, world");// Replace lcd_printf with lcd_puts
                                 // step through in debug mode
                                 // and explain to TA how it
                                 // works


    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
    // NOTE: For time fuctions see Timer.h

	return 0;
}
