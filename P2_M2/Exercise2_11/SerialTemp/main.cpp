/*----------------------------------------------------------------------------
LAB EXERCISE 11.3 - I2C interface
SERIAL COMMUNICATION
 ----------------------------------------
    Access the virtual temperature sensor via I2C interface, print the current temperature
    to the PC via UART
    
    Input: temperature sensor
    Output: PC
    
    GOOD LUCK!
 *----------------------------------------------------------------------------*/
#include "mbed.h"
#include "pindef.h"

//I2C interface
I2C temp_sensor(I2C_SDA, I2C_SCL);
Serial pc(UART_TX, UART_RX);

//I2C address of temperature sensor DS1631
const int temp_addr = 0x90;

char cmd[] = {0x51, 0xAA};
char read_temp[2];

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

#define start_convert   0x51
#define stop_convert    0x22
#define read_sensor     0xaa

int main(){
    pc.baud(9600);
    pc.printf("\n\rHello mbed!");
    while(1){
        /*
        Write the Start Convert T command to the sensor
        Write the Read Temperature command to the sensor
        Read the 16-bit temperature data
        */

        temp_sensor.write(temp_addr, cmd, 2);   //start convertsion
        temp_sensor.write(temp_addr, cmd+1, 1);   //issue read command
        temp_sensor.read(temp_addr, read_temp, 2); //Read temperature 
        
    
        //Convert temperature to Celsius
        float temp = (float((read_temp[0] << 8) | read_temp[1]) / 256);
        
        //Print temperature to the serial monitor
        pc.printf("\n\rTemperature = %f C", temp);
        
        
        
    }
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
