/*
 * movement.h
 *
 *  Created on: Jan 28, 2020
 *      Author: hmajeed
 */
#include "open_interface.h"
#ifndef LAB2_CODE_FILES_MOVEMENT_H_
#define LAB2_CODE_FILES_MOVEMENT_H_




/**
 * Function to move forward a number of mm and if the bump
 * sensors are triggered it will back up and turn to avaoid the object
 */
double move_forward(oi_t *sensor_data, double distance_mm);



/**
 * Function to move forward an amount of mm
 */
double turn_right(oi_t *sensor_data, double degrees);



/**
 * Function to turn right some amount of degrees
 */
double turn_left(oi_t *sensor_data, double degrees);


/**
 * Function to turn left some amount of degrees
 */
double move_forward_with_bump(oi_t *sensor_data, double distance_mm);

/**
 * Function to move backwards a certain number of mm
 */
double move_backwards(oi_t *sensor_data, double distance_mm);

/**
 * Function to move in a square turning right at the corners
 */
int right_square(oi_t *sensor_data, double size);

/**
 * Function to move in a square turning left at the corners
 */
int left_square(oi_t *sensor_data, double size);

#endif /* LAB2_CODE_FILES_MOVEMENT_H_ */
