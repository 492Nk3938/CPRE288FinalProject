/**
 * pingMine.h
 *
 *  Created on: April 2, 2020
 *      Author: nk3
 */

#define pin3 0b1000
#define MICROS_PER_OVERFLOWS 64999UL // Number of microseconds in one timer cycle //From Timer.c
const unsigned int WAIT_TIME_MILLI = 5


#include <stdint.h>
#include "Timer.h"

/**
 * The time it took for sound to go to and back from the object the ping sensor is pointing at
 */
unsigned int time;

/**
 * global var to keep track of the times the timer overflows
 */
unsigned int _overflows;


/**
 * value to keep track of the number of clock cycles for the last call
 */
unsigned int clockCycles;

// OverView of Functions

/**
 * Functions for outside users to call. PingFire & pingBusyWait do the same thing but Fire uses inturupts.
 * GetInfo returns the last calculated distance.
 */
void pingInit();
void pingFire();
void pingBusyWait();
unsigned int pingGetInfo();

/**
 * Internal functions to help the ping functions to work
 */
void pingInturuptHandler();
void PB3ToInput();
void PB3ToOutput();
void pingInturuptHandler();

/**
 * This is the set of functions that control timer 3B.
 * TODO I may want to move this to it's owen files
 */
unsigned int clockCalcMicroSec();
void startClock();
void stopClock();
void resetClock();
void timerInturuptHandler();
unsigned int clockCalcMicroSec();

/************************************ ping callable Functions ********************************/

/**
 * This is a function that sets PB3 to an output lowers it for 5 milisec, raises it for
 *  5 milisec, then lowers it again. PB3 is re set to an input before it ends. This should
 *  cause the ping sensor to activate.
 */
void pingFire()
{

    /*************************** configure as output ************************/

    PB3ToOutput();

    /*************************** fire sensor ************************/

    timer_init();

    GPIO_PORTB_DATA_R &= ~pin3;

    timer_waitMillis(WAIT_TIME_MILLI);

    GPIO_PORTB_DATA_R |= pin3;

    timer_waitMillis(WAIT_TIME_MILLI);

    GPIO_PORTB_DATA_R &= ~pin3;

    /*************************** reconfigure as input   ************************/

    PB3ToInput();

}

/**
 * Function that uses busy waiting to get the time it takes
 * for the ping sensor to register an object. Stores the time.
 */
void pingBusyWait()
{

    pingFire(); //start the ping

    // mask inturpt
    // Note: it doesn't need to be turned back on b/c every time I need it to be on I turn it on
    GPIO_PORTB_IM_R &= ~pin3;

    //Wait until PB3 is rises to start the clock
    while (!(GPIO_PORTB_DATA_R & pin3))
    {
    }

    startClock();

    //Wait until PB3 is falls to stop the clock
    while ( GPIO_PORTB_DATA_R & pin3)
    {
    }

    stopClock();

    //record the time
    time = clockCalcMicroSec();

}

/**
 *
 * returns an unsigned int that is the mili meters away
 */
unsigned int pingGetMiliMeters()
{

    //Note : Speed of sound is 343,260 mm/sec
//              1000 mili sec per sec
//              343,260/1000 is mm/mili sec => 343.26
    return ((time * 343260) / 1000); //Function to convert milisecounds to cm's

}

/**
 * Inturupt handler that starts the clock when PB3 rises
 * and then stops the clock when it falls
 */
void pingInturuptHandler()
{

    /*************************** do checks for interrupt   ************************/

    //check if there is an inturupt
    if (GPIO_PORTB_RIS_R & pin3)
    {

        /************************ falling edge inturupt   ************************/
        if (!(GPIO_PORTB_DATA_R & pin3))
        { // check if 0 because after falling edge it would be zero

            /*************************** stop timer   ************************/

            stopClock();

            /*************************** get time   ************************/

            time = clockCalcMicroSec();

            /************************ raising edge inturupt   ************************/
        }
        else
        {

            /*************************** start timer   ************************/

            startClock();

        }

        /*************************** clear and reset inturupt   ************************/

        GPIO_PORTB_ICR_R |= pin3;

    }

}

/************************************ ping init Functions ********************************/

/**
 * set up the PB3 and the inturupts to allow the ping sensor to work. This
 * uses Timer3B and PB3
 */
void pingInit()
{

    /*************************** configure ping ************************/

    // Turn on GPIO port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_DC4_GPIOB;

    while ((SYSCTL_PRGPIO_R & SYSCTL_DC4_GPIOB))
    {
    };

    /*************************** configure timer ****************************/

//Set up requirements for the timer
    /*
     //  This section is commented out becuase the reset clock function that is called before every use of the clock
     //  does this job. Feel free to skip to the configure inturupt section.


     //    Specifically, for this lab, you will initialize Timer 3B as follows:
     //          • input edge-time mode
     //          • default 16-bit timer
     //          • count-down direction
     //          • use of 8-bit prescaler as an extension to get a 24-bit timer (need to load the PR and ILR registers
     //                    with 0xFF and 0xFFFF, respectively)
     //          • both rising and falling edges as input capture events being detected on the CCP pin
     //          • interrupts are enabled for input capture events (an edge generates an interrupt)
     // Unsure with my set up why I need inturupts or input capture events because
     // they have been set up with the GPIO
     */



// This code is commented out becuase I relised the counter would need to be initiated every time I used it,
// so I just moved it to it's own function, resetClock
    /*
     //    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3; //Turn on the clock
     //    TIMER3_CTL_R &= &= ~TIMER_CTL_TAEN; //disable for set up, wait un till I want it to start counting to enable
     //
     //    TIMER3_CFG_R = TIMER_CFG_16_BIT; // set to 16 bit
     //
     //
     //
     //    TIMER3_TBPR_R &= ~0xFFFF;    //clear all bits from the unreserved parts of the PR register
     //    TIMER3_TBPR_R |= 0xFF;       // Set the bits I want
     //
     //
     //
     //    TIMER3_TBILR_R = 0xFFFF     //ILR reg has no reserved bits or other values so just equal it to what is wanted
     //
     //
     //
     //    TIMER3_TBMR_R &= ~0x10 //  set to count down
     //
     //
     */

    /******************************** Set up GPIOB inturupt registers ******************************/
    // mask the inturupts
    GPIO_PORTB_IM_R &= ~pin3;

//          GPIO Interrupt Sense - set if inturupt is trigered on edge or level ( I want edge )
    GPIO_PORTB_IS_R &= ~pin3;

    GPIO_PORTB_IBE_R |= pin3; //Set inturupts on falling and rissing edges

    /******************************** Set up NVIC registers ******************************/

    // set bits 13:15 in PRI4 register because 4n+1 = 17 => n=4
    NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFF1FFF) | 0x0008000; // set bits 12:15 = 0b0100 => 8

    //enable inturupt for GPIOB
    NVIC_EN0_R |= INT_GPIOB;

    IntRegister(INT_GPIOB, pingInturuptHandler);

    IntMasterEnable();

    GPIO_PORTB_IM_R |= pin3; //unMask inturupts

}

void PB3ToInput()
{

    /*************************** change to input ************************/

    // clear bit 3 to set as input
    GPIO_PORTB_DIR_R &= ~pin3;

    /*************************** Enable AFSL ************************/

    //turn on alternate function
    GPIO_PORTB_AFSEL_R |= pin3;

    // bits 15:12 control alternate function for pin3
    // on PB3 3 = I2C0SDA & 7 = T3CCP1
    // T3CCP1 is for the ping sensor
    GPIO_PORTB_PCTL_R |= 0x7000;

    /*************************** unmask inturupt ************************/

    GPIO_PORTB_IM_R |= pin3;

}

void PB3ToOutput()
{

    /*************************** mask interrupt & disable AFSL ************************/

    // Turn AF off
    GPIO_PORTB_AFSEL_R &= ~pin3;

    // mask inturupt
    GPIO_PORTB_IM_R &= ~pin3;

    /*************************** change to output ************************/

    GPIO_PORTB_DIR_R |= pin3;

}

/************************************ Clock Functions ********************************/

/**
 * Function that stops the clock and returns the value in micro secounds that it contained
 */
unsigned int clockCalcMicroSec()
{

    stopClock();
    unsigned int timerReg = MICROS_PER_OVERFLOWS - TIMER3_TBV_R & 0xFFFF;


    //Number of clock cycles is the number of overflows * clock cycles per overflow + cycles curently in the register
    clockCycles = _overflows * 0xFFFF + TIMER3_TBV_R;



    return _overflows * MICROS_PER_OVERFLOWS + timerReg;

}



/**
 * Starts the clock
 */
void startClock()
{
    TIMER3_CTL_R |= TIMER_CTL_TAEN;
}

/**
 * Pauses the clock
 */
void stopClock()
{
    TIMER3_CTL_R &= ~TIMER_CTL_TAEN;
}

/**
 * Function to reset the clock to 0. The timer does not start untill startClock is called
 */
void resetClock()
{
    SYSCTL_RCGCTIMER_R &= ~SYSCTL_RCGCTIMER_R3; //Turn off clock to reset values

    // loop that makes sure all of  the capacitors have fully discharged to reset all of the values
    // Not sure if this is needed but figured I would throw it in anyway
    int i;
    for (i = 0; i < 20; i++)
    {

    }

    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3; //Turn on the clock
    TIMER3_CTL_R &= ~TIMER_CTL_TAEN; //disable for set up, wait un till I want it to start counting to enable

    TIMER3_CFG_R = TIMER_CFG_16_BIT; // set to 16 bit

    TIMER3_TBPR_R &= ~0xFFFF; //clear all bits from the unreserved parts of the PR register
    TIMER3_TBPR_R |= 0xFF;       // Set the bits I want

    TIMER3_TBILR_R = 0xFFFF; //ILR reg has no reserved bits or other values so just equal it to what is wanted

    TIMER3_TBMR_R &= ~0x10; //  set to count down

    _overflows = 0;

    //This is the inturupt configureations from Timer.c, changed from timer 5 to 3
    TIMER3_ICR_R |= TIMER_ICR_TBTOCINT; // Clear timeout interrupt status
    TIMER3_TBPR_R = 0x0F;               // 15 gives a period of 1us
    TIMER3_IMR_R |= TIMER_IMR_TBTOIM;   // Allow TIMER3 timeout interrupts

    NVIC_PRI9_R |= 0b11100000;  // Priority 7 (lowest)

    // Enable TIMER3B interrupts set bit 36 in the inturupt registers or bit 4 on regiter 2
    NVIC_EN2_R |= 0x10;

    IntRegister(INT_TIMER3B, timerInturuptHandler);

    IntMasterEnable();

}

/**
 * Function that keeps track of how many times the timer overflows
 */
void timerInturuptHandler()
{
    TIMER3_ICR_R |= TIMER_ICR_TBTOCINT;
    _overflows++;

}



// Display the PING))) echo pulse width in clock cycles and milliseconds,
//  the distance to the object in centimeters,
//  and a running count of the number of timer overflows.


unsigned int getMilliSeconds(){
    return time;
}


unsigned int overflowTimes(){
    return _overflows;
}

unsigned int getClockCycles(){
    return clockCycles;
}


