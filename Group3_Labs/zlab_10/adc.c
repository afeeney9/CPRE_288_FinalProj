#include "adc.h"

void adc_init(void){
    //Enable the GPIO Register
        SYSCTL_RCGCGPIO_R |= 0x02;
        timer_waitMillis(1); // Small delay before accessing device after turning on clock

        GPIO_PORTB_AFSEL_R |= 0x10; //turn on alternative select in pin 4
        GPIO_PORTB_ADCCTL_R |= 0x00; //set the alternative selection to AIN10
        GPIO_PORTB_DEN_R &= 0xEF; //disable digital function
        GPIO_PORTB_AMSEL_R |= 0x10; //enable analog on pin 4
        GPIO_PORTB_DIR_R &= 0xEF; //set pin to be an input

    //set up ADC
        SYSCTL_RCGCADC_R |= 0x1;
        //enable the clk for ADC module 0
        timer_waitMillis(1); // Small delay before accessing device after turning on clock
        ADC0_ACTSS_R &= 0xFFFFFFFE;
        ADC0_EMUX_R &= 0x00000000;
        ADC0_SSMUX0_R |= 0x0000000A; //set AIN10 as sample src
        ADC0_SSCTL0_R &= 0x00000000; //clear reg
        ADC0_SSCTL0_R |= 0x00006444; //set sample 4 as end sample
        ADC0_SAC_R |= 0x4;
        ADC0_ACTSS_R |= 0x00000001;  //enable ADC
}

int adc_read(void){
    int data;
    ADC0_PSSI_R |= 0x01;
    while(~ADC0_RIS_R & 0x01);
    data = ADC0_SSFIFO0_R;
    return data;
}
