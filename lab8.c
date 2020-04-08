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
    char uartInput = 0;


    int buttonInput = 0;
    //TODO set up uart so that something can automatically get inturupted rather then busy waiting
    while(uartInput != 5){

        servo_set_angle(angle);

        if(clockwise == 1){
            lcd_printf("Dir: clockwise \n Angle: %d\n Match Val: %d\npress 1 and 4 to exit", angle, servo_get_match_val());
        }else{
            lcd_printf("Dir: counter clockwise \n Angle: %d\n Match Val: %d\npress 1 and 4 to exit", angle, servo_get_match_val());
        }


        buttonInput = button_getButton();

        while(!buttonInput){
            buttonInput = button_getButton();
        }






        if (buttonInput == 4)
        {
            if(clockwise == 1){
                angle = 5;
            }else{
                angle = 175;
            }

        }
        else if (buttonInput == 3)
        {
            clockwise *= -1;
        }
        else if (buttonInput == 2)
        {
            angle += clockwise * 5;
        }
        else if (buttonInput == 1)
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

    }









    lcd_printf("Because 2-3 will use the putty terminal\n press any button to continue");


    uart_sendStr(" The same commands from 2-2 will be used,\n We've added 5 to adjust the scaler for the function to convert angle to time \n and 6 to adjust the offset");




    //TODO convert the 2-2 into commands and UI that uses UART to do all of the things for 2-2 and allows the user to adjust the angle to time stuff in servo

    char myString[60];
    uartInput = 0;
    while(uartInput == 's'){

        servo_set_angle(angle);



        //TODO uart send does not accept formated strings so I need to format them before I put it in.
        if (clockwise == 1)
        {

            snprintf(myString, 60,
                     "Dir: clockwise \n Angle: %d\n Match Val: %d", angle,
                     servo_get_match_val());

        }
        else
        {
            snprintf(myString, 60,
                     "Dir: counter clockwise \n Angle: %d\n Match Val: %d",
                     angle, servo_get_match_val());

        }

        uart_sendStr(myString);

        uart_sendStr(" input an int for the scalling value. ( the m in the mx+b)");
        servo_set_scalling_for_function(uart_receive_int());

        uartInput = uart_receive();


        if (uartInput == '6')
        {

            uart_sendStr(" input an int for the scalling value. ( the m in the mx+b)");
            servo_set_scalling_for_function(uart_receive_int());

        }
        else if (uartInput == '5')
        {


            uart_sendStr(" input an int for the offset value. ( the b in the mx+b)");
            servo_set_offset_for_function(uart_receive_int());




        }else if (uartInput == '4')
        {
            if(clockwise == 1){
                angle = 5;
            }else{
                angle = 175;
            }

        }
        else if (uartInput == '3')
        {
            clockwise *= -1;
        }
        else if (uartInput == '2')
        {
            angle += clockwise * 5;
        }
        else if (uartInput == '1')
        {
            angle += clockwise;
        }
        else
        {

            uart_sendStr("you didn't press a valid key");

        }


        if(angle < 0){
            angle = 0;
        }
        if(angle > 180){
            angle = 180;
        }


    }




    lcd_printf("goodbye");

    oi_free(sData);

}

