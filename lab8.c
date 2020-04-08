/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 */
#include <stdio.h>
#include <string.h>

#include "Timer.h"
#include "adc.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart.h"
#include "open_interface.h"
#include "movement.h"
#include "button.h"
#include "open_interface.h"
#include "movement.h"
#include "servo.h"

//#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void)
{

    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    uart_init();
    button_init();

    oi_t *sData = oi_alloc(); // do this only once at start of main()
    oi_init(sData); // do this only once at start of main()
    adc_init(sData);


/**
     2-1 Functional milestone: Moving the servo using PWM (accuracy and inputs not required)
     2-2 Extra credit 1: Using specified pushbutton inputs to move the servo (2 points)
     2-3 Extra credit 2: Using team-designed inputs to move the servo (3 points)
     2-4 Extra credit 3: Using user-assisted calibration for accurate positioning (5 points)
     */





    //2-1 Functional milestone: Moving the servo using PWM (accuracy and inputs not required)
    servo_init();
    lcd_printf(" Functional milestone 2-1 \n The servo should have moved \n Press any button to continue");

    while (button_getButton() == 0){}

    lcd_printf("Because 2-2 needs all buttons, extra input will be from the putty terminal\n press any button to continue\n send s on putty to stop");

    while (button_getButton() == 0){}


//    Expand your API from part 2-1 with the following features:
//          1) Use pushbutton switches to adjust the match value to move the servo some number of degrees, as
//                  follows:
//              a. SW1: Move the servo 1 degree in the current direction
//              b. SW2: Move the servo 5 degrees in the current direction
//              c. SW3: Switch between clockwise and counterclockwise movement of the servo
//              d. SW4: Move the servo to 5 degrees, when in clockwise mode; move the servo to 175
//                  degrees when in counterclockwise mode.
//          2) The servo should have an initial position of 90 degrees, and an initial direction of
//                  counterclockwise.
//          3) Display the match value and the current direction on the LCD.
//          4) Operate within the bounds of 0 to 180 degrees.


    //TODO make sure the angles is right, I don't know if it is moving clockwise or
    // counter clockwise when clockwise = -1
    int clockwise = -1;
    int angle = 90;
    int char_array_size =40;
    char myString[char_array_size];
    myString[0] = 0;



    //TODO set up uart so that something can automatically get inturupted rather then busy waiting
    while(myString[0] == 's'){

        servo_set_angle(angle);

        if(clockwise == 1){
            lcd_printf("Dir: clockwise \n Angle: %d\n Match Val: %d", angle, servo_get_match_val());
        }else{
            lcd_printf("Dir: counter clockwise \n Angle: %d\n Match Val: %d", angle, servo_get_match_val());
        }





        int input = button_getButton();

        while(! input){
            input = button_getButton();
        }






        if (input == 4)
        {
            if(clockwise == 1){
                angle = 5;
            }else{
                angle = 175;
            }

        }
        else if (input == 3)
        {
            clockwise *= -1;
        }
        else if (input == 2)
        {
            angle += clockwise * 5;
        }
        else if (input == 1)
        {
            angle += clockwise;
        }
        else
        {

            lcd_printf("not sure which button you pressed, that's odd");

        }


        if(angle < 0){
            angle = 0;
        }
        if(angle > 180){
            angle = 180;
        }



        //TODO this function doesn't exist and needs to be created using inturupts so there is no need to busy wait
        myString[0] = getInturuptChar();


    }









    lcd_printf("Because 2-3 will use the putty terminal\n press any button to continue");


    uart_sendStr(" The same commands from 2-2 will be used,\n We've added 5 to adjust the scaler for the function to convert angle to time \n and 6 to adjust the offset");




    //TODO convert the 2-2 into commands and UI that uses UART to do all of the things for 2-2 and allows the user to adjust the angle to time stuff in servo







    lcd_printf("press 4 to end and 1,2, or 3 to get new scan");

    while (1)
    {


//        while (!(button_getButton()))
//        {
//            if (button_getButton() == 4)
//            {
//                break;
//            }
//        }
        if (button_getButton() == 4)
        {
            break;
        }

        lcd_printf("Distance in cm is %d\n press 4 to end and 1, 2, or 3 to get new scan", cmDistance());
        timer_waitMillis(250);

    }

    lcd_printf("goodbye");

    oi_free(sData);

}

