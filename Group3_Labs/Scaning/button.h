/*
 * button.h
 *
 *  Created on: Jul 18, 2016
 *      Author: Eric Middleton
 *
 * @edit: Phillip Jones 05/30/2019 : Removed uneeded helper functions
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "servo.h"
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>

//initialize the push buttons
void button_init();


uint8_t button_getButton();


#endif /* BUTTON_H_ */
