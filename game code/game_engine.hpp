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
    obj.set_speed_x(obj.get_speed_x() + obj.get_acceleration_x()*delta_time);
    obj.set_speed_y(obj.get_speed_y() + obj.get_acceleration_y()*delta_time);
}

// game_object s don't update their acceleration by default. Only ship s do.  
//void update_acceleration(game_object &obj){
//
//}

void update_angle(game_object &obj){
    obj.set_angle(obj.get_angle() + obj.get_angle_speed()*delta_time);
}

void update_angle_speed(game_object &obj){
    obj.set_angle_speed(obj.get_angle_speed() + obj.get_angle_acceleration()*delta_time);
}

bool check_collision(game_object &obj1, game_object &obj2) {
    double square_distance = square_euclidean_distance(obj1.get_position_x(), obj1.get_position_y(), obj2.get_position_x(), obj2.get_position_y());
    double square_size = square(obj1.get_size() + obj2.get_size());
    return (square_distance <= square_size)
}

void do_collision(game_object &obj1, game_object &obj2) {
    if (/*check_collision(obj1, obj2)*/ true) { // Redundant calculation can go away!
        // Calculate the unit normal vector pointing away from obj1
        double dx = obj2.get_position_x() - obj1.get_position_x();
        double dy = obj2.get_position_y() - obj1.get_position_y();
        double distance = euclidean_distance(obj1.get_position_x(), obj1.get_position_y(), obj2.get_position_x(), obj2.get_position_y());
        // Calculate relative distance
        dx /= distance;
        dy /= distance;
        
        // Calculate the relative velocity
        double dvx = obj2.get_speed_x() - obj1.get_speed_x();
        double dvy = obj2.get_speed_y() - obj1.get_speed_y();
        
        double dot_product = dvx * dx + dvy * dy;
        // If the objects are moving towards each other
        if (dot_product < 0) {
            // Calculate the impulse
            double impulse = 2 * dot_product / (obj1.get_mass() + obj2.get_mass());

            // Apply the impulse to the objects i.e. "bounce" them
            obj1.set_speed_x(obj1.get_speed_x() - obj2.get_mass() * impulse * dx);
            obj1.set_speed_y(obj1.get_speed_y() - obj2.get_mass() * impulse * dy);
            obj2.set_speed_x(obj2.get_speed_x() + obj1.get_mass() * impulse * dx);
            obj2.set_speed_y(obj2.get_speed_y() + obj1.get_mass() * impulse * dy);

            // Translate the objects so they're not colliding anymore
            double separation = (obj1.get_size() + obj2.get_size() - distance) / 2;
            obj1.set_position_x(obj1.get_position_x() - separation * dx);
            obj1.set_position_y(obj1.get_position_y() - separation * dy);
            obj2.set_position_x(obj2.get_position_x() + separation * dx);
            obj2.set_position_y(obj2.get_position_y() + separation * dy);
        }
    }
}

void run_simulation_step(std::vector<game_object> &interactive_objs, std::vector<game_object> &phantom_objs) {
    // Check for collisions among interactive objects
    for (auto& obj1 : interactive_objs) {
        for (auto& obj2 : interactive_objs) {
            if (obj1 == obj2) {
                continue;  // Skip if same object
            }
            if (check_collision(obj1, obj2)) {
                // Do funny things like explosions and hp deduction
                if (dynamic_cast<player_object*>(&obj1) != nullptr && dynamic_cast<player_object*>(&obj2) != nullptr) { // Unsure, possibly flawed?
                    interact(dynamic_cast<player_object&>(obj1), dynamic_cast<player_object&>(obj2)); // From player_objects.hpp
                }
                // Then resolve collision physically
                do_collision(obj1, obj2);
            }
        }
    }

    // Update position and speed of interactive objects
    for (auto& obj : interactive_objs) {
        update_position(obj);
        update_speed(obj);
        update_angle(obj);
        update_angle_speed(obj);
        obj.tick_lifespan();
    }

    // Update position of non-interactive objects
    for (auto& obj : phantom_objs) {
        update_position(obj);
        update_speed(obj);
        update_angle(obj);
        update_angle_speed(obj);
        obj.tick_lifespan();
    }
}

void run_AI_step() {
    // Check for each ship if they want to change their acceleration, possibly create a projectile or wink out of existence...
    // Update the AI's state and timer
    continue;
}