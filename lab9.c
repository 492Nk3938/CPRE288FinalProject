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


/**
 * This function will take a 2d array of 4 colums and size rows, where size is the number of objects it can find.
 * The first 2 rows will be the angles the object is first found at and the last angle it is seen at.
 * The 3rd row will then be the distance to the center of the object
 * the 4th row will be the size of the object calculated by arc length and distance
 */
int scan_for_objects(int size, int return_data[size][4]){


    int objects_found = 0;

    int angle = 0;




    int on_object = false;

    while(angle < 180 && objects_found < size){




        servo_set_angle(angle);



        if(adc_cmDistance() < max_IR_distance && !on_object){
            on_object = true;
            //set angle first found
            return_data[objects_found][0] = angle;



        } else if (adc_cmDistance() > max_IR_distance && on_object){

            on_object = false;
            //set angle last seen
            return_data[objects_found][1] = angle;


            objects_found++;


        }

        //TODO set angle increment to scan
        angle += increment_to_scan;

    }



    //Loop to get the distance to each object found and size of each object
    int i = 0;
    for (i = 0; i < objects_found; i++){

        //point ping sensor at middle of object
        angle = (return_data[i][0] + return_data[i][1])/2
        servo_set_angle(angle);

        //record distance to the middle of the object
        return_data[i][2] = ping_get_distance_busy_wait();


        return_data[i][3] = calculate_size_of_object(return_data[i][0], return_data[i][1], return_data[i][2]);

    }


    return objects_found;

}


