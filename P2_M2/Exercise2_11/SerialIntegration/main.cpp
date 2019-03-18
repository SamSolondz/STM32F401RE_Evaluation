/*----------------------------------------------------------------------------
LAB EXERCISE 11.4- SPI and I2C interface
SERIAL COMMUNICATION
 ----------------------------------------
 Display the temperature from the virtual DS1631 temperature sensor on the 
      virtual LCD
 
 Input: virtual DS1631 temperature sensor
 Output: virtual LCD display
	
	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "NHD_0216HZ.h"
#include "DS1631.h"
#include "pindef.h"
#include <stdlib.h>

//Define the LCD and the temperature sensor
NHD_0216HZ lcd(SPI_CS, SPI_MOSI, SPI_SCLK);
DS1631 tempSensor(I2C_SDA, I2C_SCL, 0x91);

//Define a variable to store temperature measurement
float temp;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main() {
	//Initialise the LCD
    lcd.init_lcd();
    lcd.clr_lcd();
    lcd.set_cursor(0,0);
    
    lcd.printf("Do you even");
    lcd.set_cursor(0,1);
    lcd.printf("mbed, bro?");
	
	//Write your code here
	while(1){
		/*
		Read the temperature from the DS1631
		Update the LCD with new temperature measurement
		*/
		float temp = tempSensor.read();
		char buffer[10];
		snprintf(buffer, sizeof(buffer), "%.2f", temp);
		
		lcd.clr_lcd();
		lcd.set_cursor(0,0);
		lcd.printf("Temperature:");
		lcd.set_cursor(0,1);
		lcd.printf(buffer);
		lcd.printf(" C");
		
		
		wait(0.1);
		
		
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
