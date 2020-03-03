/*
 * movement.c
 *
 *  Created on: Jan 28, 2020
 *      Author: hmajeed
 */
#include "open_interface.h"


/************************* Definitions **************************************/
#define robot_speed 200
#define robot_turn_speed 180
#define amount_to_backup_mm 150
#define amount_to_move_to_avoid_mm 250



/************************* Declarations **************************************/
double move_forward(oi_t *sensor_data, double distance_mm);
double turn_right(oi_t *sensor_data, double degrees);
double turn_left(oi_t *sensor_data, double degrees);
double move_forward_with_bump(oi_t *sensor_data, double distance_mm);
double move_backwards(oi_t *sensor_data, double distance_mm);
int right_square(oi_t *sensor_data, double size);
int left_square(oi_t *sensor_data, double size);







double move_forward_with_bump(oi_t *sensor_data, double distance_mm){
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(robot_speed, robot_speed); //move forward at reduced speed
    while (sum < distance_mm)
    {
        oi_update(sensor_data);
        sum += sensor_data->distance; // use -> notation since pointer

        /* This chunk handles Collision to allow robot to move around object if it bumpps into it*/
        if(sensor_data-> bumpLeft ||sensor_data-> bumpRight){
            oi_setWheels(0, 0);
            move_backwards(sensor_data, amount_to_backup_mm);
                    if(sensor_data-> bumpLeft){
                        turn_right(sensor_data, 90);
                        move_forward(sensor_data, amount_to_move_to_avoid_mm);
                        turn_left(sensor_data, 90);
                    }else {
                        turn_left(sensor_data, 90);
                        move_forward(sensor_data, amount_to_move_to_avoid_mm);
                        turn_right(sensor_data, 90);
                    }
            oi_setWheels(robot_speed, robot_speed);
        }
    }
    oi_setWheels(0, 0);
    return 0;
}





double move_forward(oi_t *sensor_data, double distance_mm)
{
    if(distance_mm < 0){
        move_backwards(sensor_data, -1*distance_mm);
    }
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(robot_speed, robot_speed); //move forward at reduced speed
    while (sum < distance_mm)
    {
        oi_update(sensor_data);
        sum += sensor_data->distance; // use -> notation since pointer
    }
    oi_setWheels(0, 0);
    return 0;
}

double turn_right(oi_t *sensor_data, double degrees)
{
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(-robot_turn_speed, robot_turn_speed); //move forward at reduced speed
    while (sum > degrees*-1)
    {
        oi_update(sensor_data);
        sum += sensor_data->angle; // use -> notation since pointer
    }
    oi_setWheels(0, 0);
    return 0;
}

double turn_left(oi_t *sensor_data, double degrees)
{

    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(robot_turn_speed, -robot_turn_speed); //move forward at reduced speed
    while (sum < degrees)
    {
        oi_update(sensor_data);
        sum += sensor_data->angle; // use -> notation since pointer
    }
    oi_setWheels(0, 0);
    return 0;
}

double move_backwards(oi_t *sensor_data, double distance_mm){
    if(distance_mm < 0){
        move_forward(sensor_data, -1*distance_mm);
    }
	oi_setWheels(-robot_speed/4, -robot_speed/4); //back up slowly
	int sum = distance_mm;
	while(sum > 0){
		oi_update(sensor_data);
		sum += sensor_data->distance; //point to distance and add to sum to know when to stop.
	}
	oi_setWheels(0,0);
	return 0;
}







int right_square(oi_t *sensor_data, double size){
     move_forward(sensor_data, size);
     turn_right(sensor_data, 90);
     move_forward(sensor_data, size);
     turn_right(sensor_data, 90);
     move_forward(sensor_data, size);
     turn_right(sensor_data, 90);
     move_forward(sensor_data, size);



     return 0;
 }

 int left_square(oi_t *sensor_data, double size){
     move_forward(sensor_data, size);
     turn_left(sensor_data, 90);
     move_forward(sensor_data, size);
     turn_left(sensor_data, 90);
     move_forward(sensor_data, size);
     turn_left(sensor_data, 90);
     move_forward(sensor_data, size);


     return 0;
 }


