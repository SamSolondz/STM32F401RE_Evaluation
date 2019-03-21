#include "mbed.h"
#include <stdio.h>
#include <time.h>

// Configuration for ramp wave generation

#define SW_DAC_FREQUENCY            1004
#define SW_DAC_FREQUENCY_FLOAT      1004.0f
#define N_SAMPLES                   (SW_DAC_FREQUENCY + 50)
#define SW_DAC_TIME_PERIOD          ((float)(1.0f/SW_DAC_FREQUENCY))
#define SW_DAC_TIME_PERIOD_INT      (1000000/SW_DAC_FREQUENCY)
#define MAX_VOLTAGE                 3
#define SAMPLE_STEP                 ((float)(3.0f*SW_DAC_TIME_PERIOD))
#define CYCLE_COUNT                 2

#define PRINT_DAC_BUFFER

float samples[SW_DAC_TIME_PERIOD_INT*CYCLE_COUNT];
uint16_t time_stamp[SW_DAC_TIME_PERIOD_INT*CYCLE_COUNT];

AnalogIn wave(PA_0);
DigitalOut led_1(LED1);
DigitalOut dout_1(D7);

// @ref_call: generate_tone(samples, time_stamp, SW_DAC_TIME_PERIOD_INT, CYCLE_COUNT);

void generate_tone(float *samples,uint16_t *time_stamp, uint16_t samples_per_period, uint16_t cycle_count){

   unsigned int i,j;
   uint16_t time_var;
   time_var = 0;

   for(j=0;j<CYCLE_COUNT;j++){
       for(i=0;i<SW_DAC_TIME_PERIOD_INT;i++){
           samples[SW_DAC_TIME_PERIOD_INT*j + i] = (float)(i*SAMPLE_STEP);
           time_stamp[SW_DAC_TIME_PERIOD_INT*j + i] = time_var++;
           wait_us(1);
       }
   }

}

void print_buffers(float *samples,uint16_t *time_stamp, uint16_t samples_per_period, uint16_t cycle_count){
   unsigned int i,j;
   for(j=0;j<CYCLE_COUNT;j++){
       for(i=0;i<SW_DAC_TIME_PERIOD_INT;i++){
           printf("\r\n%d us\t%4.6f",time_stamp[SW_DAC_TIME_PERIOD_INT*j + i], samples[SW_DAC_TIME_PERIOD_INT*j + i]);
       }
   }
}

int main(void){

  printf("\n\r********** ECEN 5803: Mastering Embedded Systems Architecture **********");
  printf("\r\n\r\n                         Project_2 Module_4 Demo                        \r\n");

  float max = 40.0f;
  float thresh_max = 75;
  float thresh_min = 15;
  float temp;
  int pulse_count = 0;
  int flag_1 = 0;

  printf("\r\nPart-1 : Software DAC\r\n");

  printf("\r\nGenerating DAC tone @ %d Hz ...", SW_DAC_FREQUENCY);

  generate_tone(samples, time_stamp, SW_DAC_TIME_PERIOD_INT, CYCLE_COUNT);

  printf("\r\nGenerated DAC tone @ %d Hz !\r\n", SW_DAC_FREQUENCY);

#ifdef PRINT_DAC_BUFFER

  print_buffers(samples, time_stamp, SW_DAC_TIME_PERIOD_INT, CYCLE_COUNT);

#endif

  printf("\r\nPart-2 : ADC Input Frequency Calculation\r\n");

  time_t start = clock();

 while(start < 200){
 	  start = clock();
      temp = wave.read()*100.0f;
      if(temp > max)
      {
          max = temp;
      }
  }

  thresh_max = 0.75 * max;
  thresh_min = 10;

  time_t time_temp = clock();

  while((start = clock() - time_temp) < 101){
      temp = wave.read()*100.0f;
      if(temp < thresh_min){
          flag_1 = 0;
      }
      if((temp > thresh_max) && !(flag_1)){
          flag_1 = 1;
          pulse_count++;
      }
   }

   printf("\r\nADC Input Frequency: %d Hz\r\n", pulse_count);
   printf("\r\nPart-3 : Blinking LED @ (1/ %d Hz) proportional to ADC Input frequency %d Hz ...\r\n", pulse_count, pulse_count);
   printf("\r\n\r\n****************************** Demo over! ******************************\r\n\r\n");
   printf("\r\n");
   while(1){
       led_1 = !led_1;
       dout_1 = !dout_1;
       wait_ms(pulse_count);
   }

   // printf("\r\n\r\n****************************** Demo over! ******************************\r\n\r\n");

}