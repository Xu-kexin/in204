#pragma once

//#define EPSILON 0.01

#include "exceptions.hpp"
#include "math_functions.hpp"

double boundary_x = 1000;
double boundary_y = 1000;
double boundary_speed = 500;
// TODO: sync boundaries with game window
double boundary_angle = 360;
double boundary_angle_speed = 360;

double boundary_size = min(boundary_x, boundary_y);


using object_t = char[40];

class game_object {
private:
    // geographical data
    double position_x;          // Arbitrary units.
    double position_y;
    double speed_x;
    double speed_y;
    double acceleration_x;
    double acceleration_y;
    double angle;               // In degrees, how the ship is oriented: front towards that direction
    double angle_speed;         // In degrees per second
    double angle_acceleration;

    double size;
    double mass;

    double lifespan;            // Seconds left to live. <-1.0 (recommended: -2.0) if it must not expire

    object_t object_type;       // Name of the art file

protected:

    bool check_inside_bound_x(double some_x){
        if(some_x<0 || some_x>boundary_x) {
            return false;
        } else {
            return true;
        }
    }
    bool check_inside_bound_y(double some_y){
        if(some_y<0 || some_y>boundary_y) {
            return false;
        } else {
            return true;
        }
    }
    bool check_inside_bound_angle(double some_angle){
        if(some_angle<0 || some_angle>boundary_angle) {
            return false;
        } else {
            return true;
        }
    }
    bool check_inside_bound_speed(double some_speed_x, double some_speed_y){
        if(square(some_speed_x) + square(some_speed_y)>square(boundary_speed)) {
            return false;
        } else {
            return true;
        }
    }
    bool check_inside_bound_angle_speed(double some_angle_speed){
        if(abs(some_angle_speed)>boundary_angle_speed) {
            return false;
        } else {
            return true;
        }
    }
    bool check_inside_bound_size(double some_size){
        if(some_size<0 || some_size>boundary_size) {
            return false;
        } else {
            return true;
        }
    }

    bool check_inside_bound_mass(double some_mass){
        return some_mass>0;
    }

    bool check_finite_lifespan(double some_time){
        return (some_time+1 >= 0);
    }

    // BASIC FUNCTIONS
    double get_position_x() const {
        return this->position_x; }
    double get_position_y() const {
        return this->position_y; }
    double get_speed_x() const {
        return this->speed_x; }
    double get_speed_y() const {
        return this->speed_y; }
    double get_acceleration_x() const {
        return this->acceleration_x; }
    double get_acceleration_y() const {
        return this->acceleration_y; }
    double get_angle() const {
        return this->angle; }
    double get_angle_speed() const {
        return this->angle_speed; }
    double get_angle_acceleration() const {
        return this->angle_acceleration; }

    double get_size() const {
        return this->size; }
    double get_mass() const {
        return this->mass; }

    double get_lifespan() const {
        return this->lifespan; }

    void set_position_x(double new_x) {
        if(check_inside_bound_x(new_x)) {
            this->position_x = new_x; 
        } //else {
            //throw Exception out_of_bounds; // Graceful failure: stopped at boundary
        //}
    }
    void set_position_y(double new_y) {
        if(check_inside_bound_y(new_y)) {
            this->position_y = new_y; 
        } //else {
            //throw Exception out_of_bounds; // Graceful failure: stopped at boundary
        //}
    }
    void set_speed_x(double new_x) {
        if(check_inside_bound_speed(new_x, this->speed_x)) {
            this->speed_x = new_x; 
        } else {
            this->speed_x = abs_min(this->speed_x, new_x);
        }
    }
    void set_speed_y(double new_y) {
        if(check_inside_bound_speed(new_y, this->speed_y)) {
            this->speed_y = new_y; 
        } else {
            this->speed_y = abs_min(this->speed_y, new_y);
        }
    }
    void set_acceleration_x(double new_x) {
        this->acceleration_x = new_x; }
    void set_acceleration_y(double new_y) {
        this->acceleration_y = new_y; }
    void set_angle(double new_angle) {
        if(check_inside_bound_angle(new_angle)) {
            this->angle = new_angle; 
        } else {
            this->angle = mod(new_angle, boundary_angle); // Spin around
        }
    }
    void set_angle_speed(double new_angle_speed) {
        if(check_inside_bound_angle_speed(new_angle_speed)) {
            this->angle_speed = new_angle_speed; 
        } else {
            this->angle_speed = abs_min(this->angle_speed, new_angle_speed);
        }
    }
    void set_angle_acceleration(double new_angle_acceleration) {
        this->angle_acceleration = new_angle_acceleration; }

    void set_size(double new_size) {
        if(check_inside_bound_size(new_size)) {
            this->size = new_size;
        } else {
            this->size = abs_min(this->size, new_size);
        }
    }
    void set_mass(double new_mass) {
        if(check_inside_bound_mass(new_mass)) {
            this->size = new_mass;
        }
    }

    void set_lifespan(double new_lifespan) {
        this->lifespan = new_lifespan;
    }

    void tick_lifespan(double delta_time) {
        if check_finite_lifespan(this->lifespan) {
            this->lifespan = this->lifespan -= delta_time;
        } // If it doesn't expire, ticking down does nothing
    }

    

// Constructors and destructors
    explicit game_object(double position_x, double position_y, 
                double speed_x, double speed_y, 
                double acceleration_x, double acceleration_y, 
                double angle, double angle_speed, double angle_acceleration,
                double size, double mass,
                double lifespan;
                object_t object_type) {
        
        this->position_x = position_x; this->position_y = position_y; 
        this->speed_x = speed_x; this->speed_y = speed_y; 
        this->acceleration_x = acceleration_x; this->acceleration_y = acceleration_y
        this->angle = angle; this->angle_speed = angle_speed; this->angle_acceleration = angle_acceleration;
        this->size = size; this->mass = mass;
        this->lifespan = lifespan;
        this->object_type = object_type;
        // Still the object?
        //this->acceleration_x = 0; this->acceleration_y = 0; this->angle_speed = 0;
    }
    game_object(const game_object& other) { // HE WHO COPIES NOTHING CREATES NOTHING
        this->position_x = other->position_x + other->size; this->position_y = other->position_y + other->size; // No collision
        this->speed_x = other->speed_x; this->speed_y = other->speed_y; 
        this->acceleration_x = other->acceleration_x; this->acceleration_y = other->acceleration_y
        this->angle = other->angle; this->angle_speed = other->angle_speed; this->angle_acceleration = other->angle_acceleration;
        this->size = other->size; this->mass = other->mass;
        this->lifespan = mass->lifespan;
        this->object_type = other->object_type;
    }

    explicit game_object(double position_x, double position_y, 
            double speed_x, double speed_y,
            double angle, double angle_speed,
            double size, double mass,
            object_t object_type) { // default objects are floating in the void with no acceleration.
        game_object(position_x, position_y, speed_x, speed_y, 0, 0, angle, angle_speed, 0, size, mass, -2.0, object_type);
        }
    
    game_object() = delete; // don't create empty objects


    ~game_object();


}