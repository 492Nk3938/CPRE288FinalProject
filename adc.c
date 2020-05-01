/*
 * adc.c
 *
 *  Created on: Feb 25, 2020
 *      Author: nk3
 */



//TODO - look at the calibrate function
// figure out what purpose they serve and if they don't serve
// any then remove them.

//TODO go through and remove unneeded includes


#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "button.h"
#include "movement.h"
#include "Timer.h"
#include "open_interface.h"


int inited =0;
/*
 * lookup table to be filled
 */
int* table;
/*
 * The minimum value we can acurately look up
 */
int min;
/*
 * The max value we can acurately look up
 */
int max;
/*
 * the size of the table
 */
int size;
/*
 * The increments the table values increase in cm's
 */
int inc =0;


oi_t *sensor_data;






/**
 * Initate the adc sensor
 * using port B pin 4
 */
int adc_init(oi_t *sensor_ptr){
    sensor_data = sensor_ptr;

    if(inited){
        return 1;
    }



    SYSCTL_RCGCGPIO_R |= 0b000010;
    SYSCTL_RCGCADC_R |= 0x1;
    timer_waitMillis(50);
    GPIO_PORTB_AFSEL_R |= 0b00010000;
    GPIO_PORTB_PCTL_R |= 0x00010000;
    GPIO_PORTB_DEN_R &= 0b11101111;
    GPIO_PORTB_AMSEL_R |= 0x10;
    GPIO_PORTB_ADCCTL_R = 0x00;



    ADC0_ACTSS_R &= ~0x01;
    ADC0_EMUX_R = ~0xF;

    ADC0_SSMUX0_R |= 0x000A;
    ADC0_SSCTL0_R |= (0x06);
    ADC0_SAC_R |= ADC_SAC_AVG_16X;
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;


    inited = 1;
    return 1;
}






/**
 * Function to get the raw data from the adc
 */
int adc_get_data(){

    ADC0_PSSI_R |= 0b1;
    while(!(ADC0_RIS_R & 0x1)){}

    int output = ADC0_SSFIFO0_R & 0xFFF;

    ADC0_ISC_R =0x1;


    return output;

}




int adc_calabrate(){

    ADC0_PSSI_R |= 0b1;
    while(!(ADC0_RIS_R & 0x1)){}

    int output = ADC0_SSFIFO0_R & 0xFFF;

    ADC0_ISC_R =0x1;


    return output;


}




/*
 * Function that takes the min, max and resolution size the scanner should be calabrared
 * for and creates a look up table useing movment and a wall it starts next to
 */
int adc_createTable (int localMin, int localMax, int resolution){
    min = localMin;
    max = localMax;

    inc = resolution;


    // There may be a table already there so free it to prevent
    // memory leaks
    free(table);


    size = ((max - min)/resolution) + 7; // added 7 just to be safe probaboly only needed 1
    table = malloc(size * sizeof(int));
    int i = 0;



    //point scanner at wall



    lcd_printf("Place bot against the wall at a 90 degree angle and press a button");
    while(!button_getButton()){}
    lcd_printf("Thank you, starting scan");


    // move forward the min amount
    move_backwards(sensor_data, (double) min * 10);


    //TODO this line can probably be incorporated into the loop if the loop is rearanged
    table[i++] = adc_get_data();


    /**
     * loop to fill the table with lookup values
     */
    while(i < size){
        lcd_printf("%d out of %d done", i, size);
        move_backwards(sensor_data, (double) resolution * 10);
        timer_waitMillis(250);
        table[i++] = adc_get_data();
        timer_waitMillis(250);
    }

    lcd_printf("scan complete");


    return 1;
}



/**
 * Function that takes the raw data from the sensor and uses the
 * lookup table to convert it to an int of the number of centemters
 * aways it is.
 */
int adc_cmDistance(){
    int i = 0;
    int data = adc_get_data();

    while(i< size){

        if( table[i] <= data){
            return (min + 2 + i * inc );
        }


            i++;
    }

    return -1;



}








