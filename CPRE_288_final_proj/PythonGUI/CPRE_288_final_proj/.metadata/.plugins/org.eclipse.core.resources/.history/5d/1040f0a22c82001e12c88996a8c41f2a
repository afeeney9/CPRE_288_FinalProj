/**
 * lab5_template.c
 * 
 * Template file for CprE 288 lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 */
#include "open_interface.h"
#include "movement.h"
#include "button.h"
#include "timer.h"
#include "lcd.h"
#include <math.h>

#include "cyBot_uart.h"  // Functions for communiticate between CyBot and Putty (via UART)
                         // PuTTy: Buad=115200, 8 data bits, No Flow Control, No Party,  COM1

#include "cyBot_Scan.h"  // For scan sensors 


//#warning "Possible unimplemented functions"
#define REPLACEME 0


// Defined in button.c : Used to communicate information between the
// the interupt handeler and main.
extern volatile int button_event;
extern volatile int button_num;

void printString(char *arr){
    int i=0;
    while(arr[i]){
        cyBot_sendByte(arr[i]);
        i++;
     }
    cyBot_sendByte('\n');
    cyBot_sendByte('\r');
}

int main(void) {
	button_init();
	lcd_init();
	//cyBot_uart_init();
	timer_init();
	init_button_interrupts();
	            // Don't forget to initialze the cyBot UART before trying to use it
	

    cyBot_uart_init_clean();  // Clean UART initialization, before running your UART GPIO init code

	// Complete this code for configuring the  (GPIO) part of UART initialization
     SYSCTL_RCGCGPIO_R |= 0x02;
     timer_waitMillis(1);            // Small delay before accessing device after turning on clock

     GPIO_PORTB_AFSEL_R |= 0x03;    //U1Rx PB0 1   U1Tx PB1  1
     GPIO_PORTB_PCTL_R &= 0xFFFFFF00;     // Force 0's in the disired locations
     GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the disired locations
     GPIO_PORTB_DEN_R |= 0x03;
     GPIO_PORTB_DIR_R &= 0b11111100;      // Force 0's in the disired locations
     GPIO_PORTB_DIR_R |= 0b00000010;      // Force 1's in the disired locataions
    
    cyBot_uart_init_last_half();  // Complete the UART device initialization part of configuration
	
	// Initialze scan sensors
     cyBOT_init_Scan(0b0100);
     right_calibration_value = 290500;
     left_calibration_value = 1235500;
     //int scanNum = 1;
     char my_data;       // Variable to get bytes from Client
     char command[100];  // Buffer to store command from Client
     int index = 0;      // Index position within the command buffer



	// YOUR CODE HERE
		
//	while(1)
//	{
	    //lab5 parts 1 and 2
//        char val = (char) button_getButton();
//        if(val != 0){
//            lcd_clear();
//            lcd_putc(val);
//            cyBot_sendByte(val);
//            val=0;
//
//        }
//        timer_waitMillis(200);

	    //lab 5 part 3

	      //getting data
//	    cyBOT_Scan_t scan;
//	    int i =0;
//	    char x = cyBot_getByte_blocking();
//	    if(x == 'm'){
//	        int sample[30];
//	        for(i =0; i < 30; i++){
//	            cyBOT_Scan(0, &scan);
//	            sample[i] = scan.IR_raw_val;
//	        }
//	        char buffer[80];
//	        for(i =0; i < 30; i++){
//	          snprintf(buffer, 100, "Scan number %d     scan value %d", scanNum, sample[i]);
//	          printString(buffer);
//	        }
//	        scanNum++;
//      Lab 5 part 3 running code
//	    cyBOT_Scan_t scan;
//	    char x = cyBot_getByte_blocking();
//	    if(x == 'm'){
//
//	        lcd_clear();
//	        char buffer[80];
//	        cyBOT_Scan(0, &scan);
//	        int IRval = scan.IR_raw_val;
//	        snprintf(buffer, 80, "scan value %d     ", IRval);
//	        lcd_puts(buffer);
//	        int dis = (10000000)*pow(scan.IR_raw_val,-1.769);
//	        snprintf(buffer, 80, "distance %d", dis);
//	        lcd_puts(buffer);
//	        snprintf(buffer, 80, "scan value %d       distance %d", IRval, dis);
//	        printString(buffer);
//	    }
	    //lab 5 part 4

//	      // Write to LCD so that we know the program is running
//	      lcd_printf("Running");
//
//	      while(1)
//	      {
//	        oi_t *sensor = oi_alloc();
//	        oi_init(sensor);
//            oi_update(sensor);
//	        index = 0;  // Set index to the beginning of the command buffer
//	        my_data = cyBot_getByte_blocking(); // Get first byte of the command from the Client
//	        if(my_data == 'w'){
//	                          move_forward(sensor, 5);
//	                      }else if(my_data == 's'){
//	                          move_backward(sensor, 5);
//	                      }else if(my_data == 'd'){
//	                          turn_ccw(sensor, 90);
//	                      }else if(my_data == 'a'){
//                              turn_clockwise(sensor, 90);
//	                      }
//	        // Get the rest of the command until a newline byte (i.e., '\n') received
//	        while(my_data != '\n' )
//	        {
//	          command[index] = my_data;  // Place byte into the command buffer
//	          index++;
//	          my_data = cyBot_getByte_blocking(); // Get the next byte of the command
//	          if(my_data == 'w'){
//	                                        move_forward(sensor, 5);
//	                                    }else if(my_data == 's'){
//	                                        move_backward(sensor, 5);
//	                                    }else if(my_data == 'd'){
//	                                        turn_ccw(sensor, 90);
//	                                    }else if(my_data == 'a'){
//	                                        turn_clockwise(sensor, 90);
//	                                    }
//	        }
//
//	        command[index] = '\n';  // place newline into command in case one wants to echo the full command back to the Client
//	        command[index+1] = 0;   // End command C-string with a NULL byte so that functions like printf know when to stop printing
//
//	        lcd_printf("Got: %s", command);  // Print received command to the LCD screen
//
//	        // Send a response to the Client (Starter Client expects the response to end with \n)
//	        // In this case I am just sending back the first byte of the command received and a '\n'
//	        cyBot_sendByte(command[0]);
//
//	        // Only send a '\n' if the first byte of the command is not a '\n',
//	        // to avoid sending back-to-back '\n' to the client
//	        if(command[0] != '\n')
//	        {
//	          cyBot_sendByte('\n');
//	        }
//
//	      }

     // Write to LCD so that we know the program is running
       lcd_printf("Running");

       while(1)
       {

         index = 0;  // Set index to the beginning of the command buffer
         my_data = cyBot_getByte_blocking(); // Get first byte of the command from the Client

         // Get the rest of the command until a newline byte (i.e., '\n') received
         while(my_data != '\n' )
         {
           command[index] = my_data;  // Place byte into the command buffer
           index++;
           my_data = cyBot_getByte_blocking(); // Get the next byte of the command
         }

         command[index] = '\n';  // place newline into command in case one wants to echo the full command back to the Client
         command[index+1] = 0;   // End command C-string with a NULL byte so that functions like printf know when to stop printing

         lcd_printf("Got: %s", command);  // Print received command to the LCD screen

         // Send a response to the Client (Starter Client expects the response to end with \n)
         // In this case I am just sending back the first byte of the command received and a '\n'
         cyBot_sendByte(command[0]);

         // Only send a '\n' if the first byte of the command is not a '\n',
         // to avoid sending back-to-back '\n' to the client
         if(command[0] != '\n')
         {
           cyBot_sendByte('\n');
         }

       }

	      return 0;

	    }






	
//	}
