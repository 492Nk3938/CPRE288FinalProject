/*
 * servo.h
 *
 *  Created on: Apr 1, 2020
 *      Author: nicholaskrabbenhoft
 */

#include <inc/tm4c123gh6pm.h>
#include "open_interface.h"

/**
 * Function to initialize the serve, uses port b pin 5
 */
void servo_init();

/**
 * Function that takes an int and sets the angle of the servo to that int
 * The servo is designed to operate within 0 and 180 degree's
 * return -1 for error and 1 for success
 */
int servo_set_angle(int angle);

/**
 * Function to set the match value for PWM
 *
 */
void servo_set_match_val(unsigned int val);
/**
 * Function to set scaling function on the conversion from
 * angle to pwm match value ( the m in mx+b)
 */
void servo_set_scalling_for_function(int m);
/**
 * Function to set offset function on the conversion from
 * angle to pwm match value ( the b in mx+b)
 */
void servo_set_offset_for_function(int b);
/**
 * Function to return the match value
 */
unsigned int servo_get_match_val();
/**
 * Function to return the scaling value ( the m in mx+b)
 */
unsigned int servo_get_scaleing();
/**
 * Function to return the offset value ( the b in mx+b)
 */
int servo_get_offset();
