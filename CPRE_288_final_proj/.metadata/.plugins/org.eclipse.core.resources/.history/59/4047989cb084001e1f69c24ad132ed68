
#include "ping.h"

volatile enum
{
    LOW, HIGH, DONE
} state;
volatile unsigned int rising_time;
volatile unsigned int falling_time;

void ping_init()
{
    //Enable the GPIO Register
    SYSCTL_RCGCGPIO_R |= 0x02;
    timer_waitMillis(1); // Small delay before accessing device after turning on clock
    GPIO_PORTB_DEN_R |= 0x08; //digital function
    GPIO_PORTB_DIR_R |= 0x08; //set pin to be an output


    SYSCTL_RCGCTIMER_R |= 0x08; //enable clk
    TIMER3_CTL_R &= 0xFFFFFEFF; //disable B
    TIMER3_CFG_R |= 0x4;   //set to 16 bit
    TIMER3_TBMR_R = 0x00000007;   //set to mode
    TIMER3_CTL_R |= 0x0D00; //enable event mode to capture both edges
    TIMER3_TBPR_R = 0xFF; //set timer prescaler
    TIMER3_TBILR_R = 0xFFFF;  //set period
    TIMER3_ICR_R |= 0xFFFF; //clear Interrupts
    TIMER3_IMR_R |= 0x0600; //enable interrupt capture mode event interrupt mask
    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    //NVIC 36
    NVIC_EN1_R |= 0x0010; //enable Timer B interrupts

    IntMasterEnable();
    TIMER3_CTL_R |= 0x100;
}

void sendTrigger()
{
    GPIO_PORTB_DIR_R |= 0x08; //set pin to be an output
    GPIO_PORTB_AFSEL_R &= 0xF7; //disable alternative function
    GPIO_PORTB_DIR_R |= 0x08;    //set pin as output
    GPIO_PORTB_DATA_R &= 0xF7;   //set output Low
    timer_waitMicros(5);         //wait
    GPIO_PORTB_DATA_R |= 0x08;   //set output high
    timer_waitMicros(5);         //wait
    GPIO_PORTB_DATA_R &= 0xF7;   //set output low
    GPIO_PORTB_DIR_R &= 0xF7;    //set pin as input
    GPIO_PORTB_AFSEL_R |= 0x08; //turn on alternative select in pin 3 disable to send output
    GPIO_PORTB_PCTL_R |= 0x7000; //select timer3 B as function
    TIMER3_ICR_R |= 0xFFFFFFFF; //clear interrupts
    state = LOW;


}

unsigned int ping_read(){
    sendTrigger();
    while(state != DONE);
    return rising_time - falling_time;
}


void TIMER3B_Handler()
{
    //check that a Match interrupt occured
    if (TIMER3_MIS_R & 0x0600)
    {
        //clear interrupt flag
        TIMER3_ICR_R |= 0x0600;
        if(state == LOW){
            rising_time = TIMER3_TBR_R;
        state = HIGH;
        }else if(state == HIGH){
          falling_time = TIMER3_TBR_R;
          state = DONE;
        }
    }
}
