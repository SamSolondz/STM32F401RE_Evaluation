#include "mbed.h"

DigitalOut myled(LED1);

int main() {
    
    printf("\n\rRTC example\n"); 
    set_time(1551824412); // Set RTC time to 5 March 2019 10:20:12 UTC
    printf("\n\rDate and time are set.\n");

    while(1) {

        time_t seconds = time(NULL);

        //printf("Time as seconds since January 1, 1970 = %d\n UTC", seconds);
        
        printf("\n\rTime as a basic string = %s UTC", ctime(&seconds));

        //char buffer[32];
        //strftime(buffer, 32, "%I:%M:%S %p\n", localtime(&seconds));
        //printf("Time as a custom formatted string = %s", buffer);

        myled = !myled;      
        wait(1);
    }
}
