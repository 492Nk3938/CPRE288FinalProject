/*
 * servo.h
 *
 *  Created on: Apr 1, 2020
 *      Author: nicholaskrabbenhoft
 */




#include <inc/tm4c123gh6pm.h>
#include "open_interface.h"


void servo_set_angle(int angle);


void servo_init();


unsigned int servo_get_match_val();
