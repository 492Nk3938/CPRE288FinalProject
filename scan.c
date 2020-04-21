/**
 *
 *
 *
 * April 21 2020
 *
 *
 * Author Nicholas Krabbenhoft
 */






/**
 * This function will take a 2d array of 4 colums and size rows, where size is the number of objects it can find.
 * The first 2 rows will be the angles the object is first found at and the last angle it is seen at.
 * The 3rd row will then be the distance to the center of the object
 * the 4th row will be the size of the object calculated by arc length and distance
 */


#include "servo.h"
#include "uart.h"
#include "adc.h"
#include "pingNicholas.h"




const int increment_to_scan = 2;

const int max_IR_distance = 80;



//TODO make function to calculate size of the object
//look in lecture slides for formula
int calculate_size_of_object(int start_angle, int end_angle, int distance){


    return -1;

}




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
        angle = (return_data[i][0] + return_data[i][1])/2;
        servo_set_angle(angle);

        //record distance to the middle of the object
        pingBusyWait();
        return_data[i][2] = pingGetMiliMeters()/10;


        return_data[i][3] = calculate_size_of_object(return_data[i][0], return_data[i][1], return_data[i][2]);

    }


    return objects_found;

}

