/*----------------------------------------------------------------------------
LAB EXERCISE 12 - Real-Time Operating System
 ----------------------------------------
    Integrate functions developed in previous modules and run then concurrently
    in the mbed RTOS. The following four threads have to be implemented:
    
    1. Display the temperature on the LCD and to the PC
    2. Adjust the brightness of the RGB LED using a potentiometer
    3. Display an incrementing counter on the LCD and to the PC
    4. Blink an LED
  
  NOTE:  For this lab, the LCD, temp sensor and POT are virtual devices.

    GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"
#include "DS1631.h"
#include "NHD_0216HZ.h"
#include "pindef.h"

/*
Define the mutex
Define the LCD display and the temperature sensor
Define other inputs and outputs
*/

Mutex lcd_mutex;
NHD_0216HZ lcd(SPI_CS, SPI_MOSI, SPI_SCLK);
DS1631 tempSensor(I2C_SDA, I2C_SCL, 0x91);
AnalogIn dimmer(PA_0);
PwmOut LED(PC_7);
DigitalOut LD2(LED1);

Thread thread1;
Thread thread2;
Thread thread3;
Thread thread4;
//signed int count = 0;

//Display temperature on the LCD
void temp_thread(){
        while(1){           
            float temp = tempSensor.read();
            char tempBuffer[10];
            snprintf(tempBuffer, sizeof(tempBuffer), "%.2f", temp);
    
            lcd_mutex.lock();
            lcd.set_cursor(0,0);     
            lcd.printf("Temp: ");
            lcd.printf(tempBuffer);
            lcd.printf(" C");
            lcd_mutex.unlock();
        }
    
}

//Adjust the brightness of the RGB LED
void adjust_brightness(){
    while(1){
        LED.period(0.01f); 
        LED.write(1.0f * dimmer.read());
        wait_ms(20);
    }
}

//Blink an LED
void led1_thread(){
    while(1){
        LD2 = !LD2;
        wait_ms(40);
    }
    
}

//Display a counter on the LCD
void count_thread(){
        while(1){
            static unsigned int count = 0;
            static char countBuffer[5];
            sprintf(countBuffer, "%d", count);
            lcd_mutex.lock(); 
            lcd.set_cursor(0,1);
            lcd.printf("Count: ");
            lcd.printf(countBuffer);
            count+= 1;
            lcd_mutex.unlock();
        }
}


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
    /*
    Initialise and clear the LCD display
    Start all threads
    Wait for timer interrupt
    */
    //write your code here
    lcd.init_lcd();
    lcd.clr_lcd();
    lcd.set_cursor(0,0);
        
    lcd.printf("Start");
    lcd.set_cursor(0,1);
    lcd.printf("Sequence");

    thread1.start(temp_thread);
    thread2.start(adjust_brightness);
    thread3.start(led1_thread);
    thread4.start(count_thread);
    
    __enable_irq();
    __wfi();
        
    
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
