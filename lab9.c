/**
 * lab9.c
 *
 * lab 9
 *
 * @author Nicholas Krabbenhoft
 */

#include <stdio.h>
#include <string.h>

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "open_interface.h"
#include "movement.h"
#include "button.h"
#include "open_interface.h"
#include "movement.h"
#include "scan.h"
#include "servo.h"
#include "uart.h"
#include "adc.h"

//#warning "Possible unimplemented functions"
#define REPLACEME 0


void drive();

void scan();

void calabrate();


/**
 * Implement the data collection and analysis functionality specified in Part 1 to detect at least one object
 * and estimate object width. Be sure to walk through your code before submitting it.
 * Note: If you completed extra credit parts for Lab 8 supporting user inputs and/or user-assisted calibration,
 * your implementation may include those parts. Be sure to include brief instructions for the user to operate
 * your system.
 */





int main(void)
{

    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    uart_init();
    button_init();

    oi_t *sData = oi_alloc(); // do this only once at start of main()
    oi_init(sData); // do this only once at start of main()
    adc_init(sData);



    lcd_printf("This uses the UART for all commands, press any button to start the program");

    while(button_getButton() == 0){}


    char uartInput;
    int stop = 0;
    while(!stop){


        //Instructions
        uart_sendStr("");


        uartInput = uart_receive();

        switch (uartInput){

        case '1':
            calabrate();

            break;

        case '2':
            scan();
            break;

        case '3':
            drive();
            break;
        case '4':

            break;
        case 'q':
            stop = 1;
            break;

        default:
            uart_sendStr("I don't recognize that command");


        }

    }




    lcd_printf("goodbye");

    oi_free(sData);

}


//TODO design all of this interface
void calabrate(){

    int stop = 0;

    while (!stop)
    {

        uart_sendStr("The commands are:\r\n \t 1: give a int to set the servo to");

        //Directions for this sub menu
        uart_sendStr("");

        char uartInput = uart_receive();

        switch (uartInput)
        {

        case '1':


            uart_sendStr("please give an int to set the servo to\r\n");



            servo_set_angle(uart_receive_int());



            char string_to_send[100];

            snprintf(
                    string_to_send,
                    100,
                    "Match value is %d\r\n",
                    servo_get_match_val);

            uart_sendStr(string_to_send);






            break;

        case '2':
            break;

        case '3':
            break;
        case '4':

            break;
        case 'q':
            break;

        default:
            uart_sendStr("I don't recognize that command");

        }
    }


}


//TODO design all of this interface
void scan(){

    int stop = 0;

    while (!stop)
    {

        //Directions for this sub menu
        uart_sendStr("Here are the instructions \r\n    Press 1: To output a scan of all objects in front of you");

        char uartInput = uart_receive();

        switch(uartInput)
        {

        case '1':
        {

            //TODO do we want to be able to make this a global
            //or function wide in order to keep track of it and use it for the other functions
            uart_sendStr("How many objects do you want to be able to find\r\n");

            int size = uart_receive_int();

            int data_from_scan[size][4];

            //This returns the data array full of information on where the scans are
            // and returns an int for the number of objects found
            int number_of_objects = scan_for_objects(size, data_from_scan);


            uart_sendStr("\r\n\n");

            uart_sendStr("Here is a list of objects found, given with the angle to them, their distance, and their size\r\n");


            char string_to_send[100];
            int i = 0;
            for (i = 0; i < number_of_objects; i++)
            {

                snprintf(
                        string_to_send,
                        100,
                        "object %d is at angle %d, %d cms away and is %d cms large\r\n",
                        i, (data_from_scan[i][0] + data_from_scan[i][1]) / 2,
                        data_from_scan[i][2], data_from_scan[i][2]);

                uart_sendStr(string_to_send);

            }


            break;
        }



        case 'q':
            return;


        default:
            uart_sendStr("I don't recognize that command");

        }
    }


}


//TODO design all of this interface
void drive(){

    int stop = 0;

    while (!stop)
    {

        //Directions for this sub menu
        uart_sendStr("");

        char uartInput = uart_receive();

        switch (uartInput)
        {

        case '1':

            break;

        case '2':
            break;

        case '3':
            break;
        case '4':

            break;
        case 'q':
            break;

        default:
            uart_sendStr("I don't recognize that command");

        }
    }

}


