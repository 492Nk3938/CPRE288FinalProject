/*
 * servo.c
 *
 *  Created on: Apr 1, 2020
 *      Author: Adamson, Bryanna M
 *      Additions and edits by Nicholas Krabbenhoft
 */

#include <inc/tm4c123gh6pm.h>
#include "open_interface.h"


float scaler;
float offset;
unsigned int matchVal;

const int clock_cycle_per_mili_sec = 16000;



/**
 * Function to initialize the serve, uses port b pin 5
 */
void servo_init(){
  //Enable clock for port b
   SYSCTL_RCGCGPIO_R |= 0x02;
   //Enable alternate function
   GPIO_PORTB_AFSEL_R |= 0x20;
   //Select alternate function
   GPIO_PORTB_PCTL_R |= 0x00700000;
   //Enable PB5
   GPIO_PORTB_DEN_R |= 0x20;
   //Set PB5 as an output
   GPIO_PORTB_DIR_R |= 0x20;
   //Enable clock for TIMER 1B
   SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;
   //Disable the TIMER for config
   TIMER1_CTL_R &= ~TIMER_CTL_TBEN;
   //Select TIMER configuration
   TIMER1_CFG_R |= 0x04;
   //Set TIMER mode, PWM mode with periodic count
   TIMER1_TBMR_R |= 0xA;


   // start value in clock cycles (ms to clock cycles)
   unsigned int pwm_period;
   pwm_period = 20 * clock_cycle_per_mili_sec;

   // lower 16 bits of start value
   TIMER1_TBILR_R = pwm_period & 0xFFFF; //This register can be completly over written
   // next 8 bits of the start value
   TIMER1_TBPR_R = pwm_period >> 16;


   //match value
   TIMER1_TBMATCHR_R = 18.5 * clock_cycle_per_mili_sec;
   TIMER1_TBPMR_R = ((TIMER1_TBMATCHR_R) >> 16);



   //Enable the TIMER
   TIMER1_CTL_R |= TIMER_CTL_TBEN;


   //set the offsets to default
   offset = 17;
   scaler = 1/60 ; //


}



/**
 * Function that takes an int and sets the angle of the servo to that int
 * The servo is designed to operate within 0 and 180 degree's
 * return -1 for error and 1 for success
 */
int servo_set_angle(int angle){
    if(angle < 0 || angle > 180){
        return -1;
    }






    /*********** Trouble spot ***************/
    // This is an area I struggled with a lot and may cause bugs in the future

    // documentation states that I should be able to convert angle to
    // amount of time to by high and low by a linear function.
    // This is an attempt to do that. The angle is multiplied by the scaller
    // which should be 1/60th I beleve and then added to the offset of 17.
    // This means if the angle is 180 then scaler * angle + offset should be
    // 20 so the match value is 0
    matchVal = (20 - (scaler * angle + offset)) * clock_cycle_per_mili_sec;


    TIMER1_TBILR_R = (matchVal) & 0xFFFF;
    TIMER1_TBPR_R = (matchVal) >> 16;

    return 1;

}

/**
 * Function to set the match value for PWM
 *
 */
void servo_set_match_val(unsigned int val){
    matchVal = val;
}

/**
 * Function to set scaling function on the conversion from
 * angle to pwm match value ( the m in mx+b)
 */
void servo_set_scalling_for_function(int m){
    scaler = m;
}

/**
 * Function to set offset function on the conversion from
 * angle to pwm match value ( the b in mx+b)
 */
void servo_set_offset_for_function(int b){
    offset = b;
}

/**
 * Function to return the match value
 */
unsigned int servo_get_match_val(){
    return matchVal;
}

/**
 * Function to return the scaling value ( the m in mx+b)
 */
unsigned int servo_get_scaleing(){
    return scaler;
}

/**
 * Function to return the offset value ( the b in mx+b)
 */
int servo_get_offset(){
    return offset;
}


