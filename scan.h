/**
 *
 *
 *
 * April 21 2020
 *
 *
 * Author Nicholas Krabbenhoft
 */





#include "servo.h"
#include "uart.h"
#include "adc.h"





/**
 * Function that uses the the adc and ping to find the size, position and distance to all objects in front of the robot
 * pass the number of objects you expect to find, bot will not find more
 * and an 2D int array of [size][4] for the data to be stored in
 * will return the number of objects found and fill the array given
 * Format of the returned array is
 * The first 2 rows will be the angles the object is first found at and the last angle it is seen at.
 * The 3rd row will then be the distance to the center of the object
 * the 4th row will be the size of the object calculated by arc length and distance
 */
int scan_for_objects(int size, int return_data[size][4]);





