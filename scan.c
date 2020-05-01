/**
 *
 *
 *
 * April 21 2020
 *
 *
 * Author Nicholas Krabbenhoft
 */



#include "servo.h"
#include "uart.h"
#include "adc.h"
#include "pingNicholas.h"
#include <math.h>

// 22 / 7 is roughly PI
#define PI 22/7


const int increment_to_scan = 2;

const int max_IR_distance = 60;




/* After some googling it looks like the "chord length" is
 * what I want to find. This gives me the size of the object is
 * the squareroot( 2 r^2 - 2 r^2 * cos( end_angle - start_angle)
 */
/**
 * Function that takes the 2 angles and a distance and finds the
 * linear distance between the to points. The first angle given needs
 * to be smaller then the secound one or I don't know what will happen
 */
int calculate_size_of_object(int start_angle, int end_angle, int distance){
    //r for radius
    float r = (float) distance;


    // convert it to radians and find the difference
    float theta = ((float) (end_angle - start_angle)) * PI / 180;

    //TODO I am confused if sqrt takes only doubles or float. I saw some docs that said both
    return sqrt( (2 * r * r - 2 * r * r * cos( theta )));

}



/**
 * Function that uses the the adc and ping to find the size, position and distance to all objects in front of the robot
 * pass the number of objects you expect to find, bot will not find more
 * and an 2D int array of [size][4] for the data to be stored in
 * will return the number of objects found and fill the array given
 * Format of the returned array is
 * The first 2 rows will be the angles the object is first found at and the last angle it is seen at.
 * The 3rd row will then be the distance to the center of the object
 * the 4th row will be the size of the object calculated by arc length and distance
 */
int scan_for_objects(int size, int return_data[size][4]){


    int objects_found = 0;

    int angle = 0;




    int on_object = false;


    //scan and find the location of all objects
    while(angle < 180 && objects_found < size){




        servo_set_angle(angle);



        //keep tract of if the bot is first finding the object or leaving the object
        // if the adc is less then it's max then it assumes it is on an object
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

        angle += increment_to_scan;

    }



    //Loop to get the distance to each object found and size of each object
    int i = 0;
    for (i = 0; i < objects_found; i++){

        //point ping sensor at middle of object
        angle = (return_data[i][0] + return_data[i][1])/2;
        servo_set_angle(angle);

        //record distance to the middle of the object
        pingBusyWait();
        return_data[i][2] = pingGetMiliMeters()/10;


        return_data[i][3] = calculate_size_of_object(return_data[i][0], return_data[i][1], return_data[i][2]);

    }


    return objects_found;

}

