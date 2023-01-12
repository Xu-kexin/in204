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



class ship {
public:
    class player_object;
private:
    // ship stats   
    // int maximum_health; 
    int remaining_health;
    AI_data_t AI_data;                    // -> ship AI + current AI state
    const ship_t ship_type;
    

    // ship specialty // OPTIONAL; TODO IF WE HAVE THE TIME
    //int specialty; // Index -> see specialty array

public:

    int get_health() {
        return this->remaining_health;
    }
    void set_health(int new_health) {
        this->remaining_health = new_health;
    }
    int get_faction() {
        return this->belongs_to;
    }

    int get_max_health() {
        return default_health(this->ship_type);
    }



    // Constructors and destructors.
    explicit ship(  int faction, ship_t ship_type,
                    double position_x, double position_y, double speed_x, double speed_y, double angle) {
        this->ship_type = ship_type;
        this->remaining_health = default_health(ship_type);
        this->AI = starting_AI(ship_type);
    }


}



