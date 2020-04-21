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
            calabrate(string_to_send);

            break;

        case '2':
            scan();
            break;

        case '3':
            drive()
            break;
        case '4':

            break;
        case 'q':
            stop = 1;
            break;

        default:
            uart_sendStr("I don't recognize that command")


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
            uart_sendStr("I don't recognize that command")

        }
    }


}


//TODO design all of this interface
void scan(){

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
            uart_sendStr("I don't recognize that command")

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
            uart_sendStr("I don't recognize that command")

        }
    }


}




