/*
 * button.c
 *
 *  Created on: Jul 18, 2016
 *      Author: Eric Middleton, Zhao Zhang, Chad Nelson, & Zachary Glanz.
 *
 *  @edit: Lindsey Sleeth and Sam Stifter on 02/04/2019
 *  @edit: Phillip Jone 05/30/2019: Mearged Spring 2019 version with Fall 2018
 */
 


//The buttons are on PORTE 3:0
// GPIO_PORTE_DATA_R -- Name of the memory mapped register for GPIO Port E, 
// which is connected to the push buttons
#include "button.h"


/**
 * Initialize PORTE and configure bits 0-3 to be used as inputs for the buttons.
 */
void button_init() {
	static uint8_t initialized = 0;
	if(initialized){
		return;
	}

    SYSCTL_RCGCGPIO_R |= 0x10;
    GPIO_PORTE_DIR_R &= 0xF0;
    GPIO_PORTE_DEN_R |= 0x0F;
	
	initialized = 1;
}



/**
 * Returns the position of the rightmost button being pushed.
 * @return the position of the righttmost button being pushed. 4 is the rightmost button, 1 is the leftmost button.  0 indicates no button being pressed
 */
uint8_t button_getButton() {

    if(~GPIO_PORTE_DATA_R & 0x08){
        GPIO_PORTE_DATA_R |= 0xFF;
        return 0x8;
    }else if(~GPIO_PORTE_DATA_R & 0x04){
        GPIO_PORTE_DATA_R |= 0xFF;
        return 0x4;
    }else if(~GPIO_PORTE_DATA_R & 0x02){
        GPIO_PORTE_DATA_R |= 0xFF;
        return 0x2;
    }else if(~GPIO_PORTE_DATA_R & 0x01){
        GPIO_PORTE_DATA_R |= 0xFF;
        return 0x1;
    }
	
	return 0; // EDIT ME
}





