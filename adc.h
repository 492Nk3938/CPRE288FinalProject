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


int get_data();
int adc_init(oi_t *sensor_data);
int createTable (int localMin, int localMax, int resolution);
int cmDistance();


#endif /* ADC_H_ */
