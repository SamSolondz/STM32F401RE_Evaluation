/***************************************************************************************************

    ECEN 5803: Mastering Embedded Systems Architecture 
    Project 2 Module 2
    
    @date: March 14, 2019.
    
    @author: Shivam Khandelwal and Samuel Solondz
    
    @brief: Generates audio tone as PWM output whose pitch and volume is controlled by ADC input.

****************************************************************************************************/

#include "mbed.h"
 
AnalogIn pitch(PA_0);
AnalogIn volume(PA_1); 
PwmOut speaker(D6);

int main() {
    while(1){
        speaker.period(1.0f*pitch.read());  
        speaker.write(1.0f*volume.read());
        wait_ms(20);
    }
}
