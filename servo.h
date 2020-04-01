/*
 * servo.h
 *
 *  Created on: Apr 1, 2020
 *      Author: nicholaskrabbenhoft
 */




#include <inc/tm4c123gh6pm.h>
#include "interrupt.h"

void timer_inturupt();

void servo_set_angle(float angle);


void servo_init();
