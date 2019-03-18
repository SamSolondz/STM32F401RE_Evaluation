#include "mbed.h"


//PB_5/D4
//PA_3/D0

//LSB.....MSB
BusIn Buttons(PC_7, PB_4, PA_10, PB_5);
BusOut LEDs(PA_9, LED1);

int main() 
{
    int state = 0;
    while(1){
        switch(Buttons) {
            case 0b1110:      //PB_4/D5 is pressed
               state |= 0b01;    
               printf("\n\rExternal on");
               break;
            case 0b1101:       //PC_7/D9 is pressed
                state &= 0b10;
                printf("\n\rExternal off");
                break;
            case 0b1011:      //PA10/D2  is pressed
               state |= 0b10;
               printf("\n\rUser on");
               break;
            case 0b0111:       //PB_5/D4 is pressed
                state &= 0b01;
                printf("\n\ruser off");
                break;
            
        }
        LEDs = state;
    }
}
