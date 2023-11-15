#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include <driverlib/interrupt.h>
#include "Timer.h"
void ping_init(void);
void TIMER3B_Handler(void);
void sendTrigger(void);
unsigned int ping_read();
