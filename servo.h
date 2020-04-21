/*
 * servo.h
 *
 *  Created on: Apr 1, 2020
 *      Author: nicholaskrabbenhoft
 */




#include <inc/tm4c123gh6pm.h>
#include "open_interface.h"


int servo_set_angle(int angle);


void servo_init();


unsigned int servo_get_match_val();





void servo_set_match_val(unsigned int val);

void servo_set_scalling_for_function(int m);

void servo_set_offset_for_function(int b);

unsigned int servo_get_match_val();

unsigned int servo_get_scaleing();

int servo_get_offset();
