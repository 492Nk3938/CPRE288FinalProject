/*
 * pingMine.h
 *
 *  Created on: Apr 2, 2020
 *      Author: nicholaskrabbenhoft
 */

#ifndef PINGNICHOLAS_H_
#define PINGNICHOLAS_H_


#include <stdint.h>

#include "Timer.h"


/**
 * set up the PB3 and the inturupts to allow the ping sensor to work. This
 * uses Timer3B and PB3
 */
void pingInit();


/**
 * This is a function that sets PB3 to an output lowers it for 5 milisec, raises it for
 *  5 milisec, then lowers it again. PB3 is re set to an input before it ends. This should
 *  cause the ping sensor to activate.
 */
void pingFire();


/**
 * Function that uses busy waiting to get the time it takes
 * for the ping sensor to register an object. Stores the time.
 */
void pingBusyWait();



/**
 *
 * returns an unsigned int that is the mili meters away
 */
unsigned int pingGetMiliMeters();


unsigned int getMilliSeconds();


unsigned int overflowTimes();

unsigned int getClockCycles();







/**
 * Internal functions to help the ping functions to work
 */
void pingInturuptHandler();
void PB3ToInput();
void PB3ToOutput();
void pingInturuptHandler();

/**
 * This is the set of functions that control timer 3B.
 * TODO I may want to move this to it's own files
 */
unsigned int timerCalcMilisec();
void startClock();
void stopClock();
void resetClock();
void timerInturuptHandler();
unsigned int clockCalcMicroSec();







#endif /* PINGNICHOLAS_H_ */
