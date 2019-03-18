#include "mbed.h"
//LSB.....MSB
BusOut LEDs(PA_9, LED1);

InterruptIn externalOn(PC_7); //D9
InterruptIn externalOff(PB_4);
InterruptIn userOn(PA_10);
InterruptIn userOff(PB_5);

void externalOnISR(){
    LEDs = LEDs | 0b01;
    printf("\n\rExternal on");
}

void externalOffISR(){
    LEDs = LEDs & 0b10;
    printf("\n\rExternal off");
}

void userOnISR(){
    LEDs = LEDs | 0b10;
    printf("\n\rUser on");
}

void userOffISR(){
    LEDs = LEDs & 0b01;
    printf("\n\rUser off");
}
    
int main() 
{
    __enable_irq();
    int LEDs = 0;
    externalOn.fall(&externalOnISR);
    externalOff.fall(&externalOffISR);
    userOn.fall(&userOnISR);
    userOff.fall(&userOffISR);

    __wfi();

}
