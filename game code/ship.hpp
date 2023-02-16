#pragma once


#include "ship_AI.hpp"
#include "exceptions.hpp"
#include "player_objects.hpp"

enum class ship_t { // All sorts of ship_types
    Fighter;
    Bomber;
    Frigate;
    Missile;
    Factory;
}

int default_health(ship_t ship_type) {
    switch (ship_type) {
        case Fighter:
            return 10;
            break;
        case Bomber:
            return 50;
            break;
        case Frigate:
            return 200;
            break;
        case Missile:
            return 1;
            break;
        case Factory:
            return 3000;
            break;
        default:
            throw Exception ship_not_recognized;
            return -1; // ERROR

    }
}

class ship : public player_object {
private:
    // Ship stats   
    int remaining_health;
    AI_data_t AI_data;                    // -> ship AI + current AI state
    const ship_t ship_type;         // Describes the kind of ship it is for purposes of finding AI or health. Not to be confused with object_type (image).

public:

    int get_health() const {
        return this->remaining_health;
    }

    void set_health(int new_health) {
        this->remaining_health = new_health;
    }

    int get_max_health() const {
        return default_health(this->ship_type);
    }

    // Constructors and destructors.
    explicit ship(player_object& player_obj, ship_t ship_type) 
    : player_object(player_obj), ship_type(ship_type) 
    {
        this->remaining_health = default_health(ship_type);
        this->AI_data = starting_AI(ship_type);
    }

    ship(const ship& other) 
    : player_object(other), ship_type(other->ship_type), 
      remaining_health(other->remaining_health) 
    { this->AI_data = other->AI_data; }

    ship() = delete; // No making empty ships

    ~ship();

    // TODO: implement everything needed here
};

class ship : player_object {
private:
    // ship stats   
    // int maximum_health; 
    int remaining_health;
    AI_data_t AI_data;                    // -> ship AI + current AI state
    const ship_t ship_type;         // Describes the kind of ship it is for purposes of finding AI or health. Not to be confused with object_type (image).
    

    // ship specialty // OPTIONAL; TODO IF WE HAVE THE TIME
    //int specialty; // Index -> see specialty array

public:

    int get_health() {
        return this->remaining_health;
    }
    void set_health(int new_health) {
        this->remaining_health = new_health;
    }

    int get_max_health() {
        return default_health(this->ship_type);
    }



    // Constructors and destructors.
    explicit ship(  player_object &player_obj, ship_t ship_type) {

        this->ship_type = ship_type;
        this->remaining_health = default_health(ship_type);
        this->AI = starting_AI(ship_type);
    }

    // TODO: finish that!!!!!

}


void interact(player_object &obj1, player_object &obj2) {
    // Assumption: there is a collision.
    // Check faction
    

    // Delete an object, deduce hitpoints, etc.

}
