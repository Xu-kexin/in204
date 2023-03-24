#pragma once

#include "exceptions.hpp"
#include <boost/asio.hpp> // timers


// For each ship there is a collection of data that allows the ship to take a decision according to an AI. 
// The AI is NOT stored in the ship, only the data.

/* // Uninspiring potential. //
class enum AI_t {
    Fighter_AI;
    Bomber_AI;
    Frigate_AI;
    Missile_AI;
    Factory_AI;
    Dead_AI;
}
*/
enum class 


class AI_data_t {
    // const int AI_sort; // == ship type
    AI_state_t AI_state;
    double timer; // Much like lifespan, in seconds
}

AI_data_t starting_AI_data(ship_type) {
    AI_data_t this_data;
    switch (ship_type) {
        case Fighter:
            return Fighter_AI;
        case Bomber:
            return Bomber_AI;
        case Frigate:
            return Frigate_AI;
        case Missile:
            return Missile_AI;
        case Factory:
            return Factory_AI;
        default:
            throw Exception ship_not_recognized;
            return Dead_AI; // ERROR
    }
}