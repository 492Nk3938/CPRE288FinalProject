/*
 * servo.c
 *
 *  Created on: Apr 1, 2020
 *      Author: nicholaskrabbenhoft
 */

#include <inc/tm4c123gh6pm.h>
#include "interrupt.h"

int time_to_be_1;






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
   pwm_period = 20 * 1000 * 16;
   // lower 16 bits of start value
   TIMER1_TBILR_R = pwm_period & 0xFFFF;
   // next 8 bits of the start value
   TIMER1_TBPR_R = pwm_period >> 16;
   //match value
   TIMER1_TBMATCHR_R = (195 * 100 * 16);
   TIMER1_TBPMR_R = (195 * 100 * 16) >> 16;
   //Enable the TIMER
   TIMER1_CTL_R |= TIMER_CTL_TBEN;

    //enable port 5b as output

    // may need to do an alternate selection to make it point to the servo (check pre lab)






    //configure timer 1b to count down



    //configure interrupt to be caused when timer 1b hits 0

    // if possible make it so timer 1b needs to be triggered before it begins counting down


    //set interrupt to point to void timer_inturupt()









}




void servo_set_angle(float angle){


    //TODO

    //time_to_be_1 = convert angle to time //Note this may be impossible to do accurately without access to the bot


}



void timer_inturupt(){


    // do we need to do any checks before the interrupt???



    if(0b100000 & /*GPIO port B data*/){ // check if it is outputting a 1 on PB5


        //set timer to 20 ms



        /*GPIO port B data*/ |= 0b100000



    } else{ // if GPIO PB5 is a 0 at beginning of the interrupt.


        //set timer to time_to_be_1;



        /*GPIO port B data*/ &= ~0b100000



    }

    // start timers


    //clear interrupts







}
