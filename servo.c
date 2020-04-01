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

    //enable port 5b as output

    // may need to do an alternate selection to make it point to the servo (check pre lab)






    //configure timer 1b to count down



    //configure interrupt to be caused when timer 1b hits 0

    // if possible make it so timer 1b needs to be triggered before it begins counting down


    //set interrupt to point to void timer_inturupt()









}




void servo_set_angle(float angle){


    //TODO

    //time_to_be_1 = convert angle to time //Note this may be impossible without access to the bot


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







