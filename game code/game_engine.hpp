#pragma once

#include "objects.hpp"
#include "player_objects.hpp"

double delta_time = 0.01; // in seconds
// TODO: have delta_time be the inverse of the frame_rate. 
double boundary_x = 1000;
double boundary_y = 1000;
// TODO: sync boundaries with game window
double boundary_angle = 360;


// Formulas : v = d/t

void update_position(game_object &obj){
    obj.set_position_x(obj.get_position_x() + obj.get_speed_x()*delta_time);
    obj.set_position_y(obj.get_position_y() + obj.get_speed_y()*delta_time);
}

// game_object s don't update their speed by default. Only ship s do.  
void update_speed(game_object &obj){

    throw Exception asked_strange_calculation;

    obj.set_speed_x(obj.get_speed_x() + obj.get_acceleration_x()*delta_time);
    obj.set_speed_y(obj.get_speed_y() + obj.get_acceleration_y()*delta_time);
}

// game_object s don't update their acceleration by default. Only ship s do.  
//void update_acceleration(game_object &obj){
//
//}

void update_angle(game_object &obj){
    obj.set_angle(obj.get_angle + obj.get_angle_speed)
}

void update_angle_speed(game_object &obj){

}

void update_angle_speed(game_object &obj){

}

int check_collision(game_object &obj1, game_object &obj2) {

}

void do_collision(game_object &obj1, game_object &obj2) {
    if(check_collision(obj1, obj2)) {

    } else {
        throw Exception asked_false_collision
    }
}