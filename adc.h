/*
 * adc.h
 *
 *  Created on: Feb 25, 2020
 *      Author: nk3
 */

#ifndef ADC_H_
#define ADC_H_

#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "button.h"

#include "Timer.h"
#include "open_interface.h"


/**
 * Initate the adc sensor
 * using port B pin 4
 */
int adc_init(oi_t *sensor_data);


/*
 * Function that takes the min, max and resolution size the scanner should be calabrared
 * for and creates a look up table useing movment and a wall it starts next to
 */
int adc_createTable (int localMin, int localMax, int resolution);

/**
 * Function that takes the raw data from the sensor and uses the
 * lookup table to convert it to an int of the number of centemters
 * aways it is.
 */
int adc_cmDistance();


#endif /* ADC_H_ */
