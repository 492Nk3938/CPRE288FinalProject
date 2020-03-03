/*
 * movement.h
 *
 *  Created on: Jan 28, 2020
 *      Author: hmajeed
 */
#include "open_interface.h"
#ifndef LAB2_CODE_FILES_MOVEMENT_H_
#define LAB2_CODE_FILES_MOVEMENT_H_


double move_forward(oi_t *sensor_data, double distance_mm);
double turn_right(oi_t *sensor_data, double degrees);
double turn_left(oi_t *sensor_data, double degrees);
double move_forward_with_bump(oi_t *sensor_data, double distance_mm);
double move_backwards(oi_t *sensor_data, double distance_mm);
int right_square(oi_t *sensor_data, double size);
int left_square(oi_t *sensor_data, double size);

#endif /* LAB2_CODE_FILES_MOVEMENT_H_ */
