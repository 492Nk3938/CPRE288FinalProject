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

//#warning "Possible unimplemented functions"
#define REPLACEME 0

char* receive_string(char str[], int size)
{
    int i = 0;
    while (i < size - 1)
    {
        str[i] = uart_receive();
        if (str[i] == '\n' || str[i] == '\r')
        {
            break;
        }
        i++;
    }
    str[i] = '\0';

    return str;

}

int main(void)
{

    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    uart_init();
    button_init();

    oi_t *sData = oi_alloc(); // do this only once at start of main()
    oi_init(sData); // do this only once at start of main()
    adc_init(sData);

    createTable(9, 50, 2);

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

