#include "objects.hpp"

enum class faction_t {
    Green;
    Yellow;
    Red;
    Blue;
    Black; // Undefined/Other
}


class player_object {
public:
    game_object object;

private:
    const faction_t belongs_to;             // designates the player who controls this object.

protected:
// Constructors and destructors
    player_object(double position_x, double position_y, 
                double speed_x, double speed_y, 
                double acceleration_x, double acceleration_y, 
                double angle, double angle_derivative, double angle_acceleration,
                object_t object_type, faction_t faction): belongs_to(faction) {
        this->object = object(position_x, position_y, 
                            speed_x, speed_y, 
                            acceleration_x, acceleration_y, 
                            angle, angle_derivative, angle_acceleration,
                            object_type);
    }
    player_object(player_object other): belongs_to(other->belongs_to) {
        this->object = other->object;
    }

    player_object(double position_x, double position_y, 
            double speed_x, double speed_y,
            double angle, double angle_derivative,
            object_t object_type, faction_t faction): belongs_to(faction) {
                this->object = object(position_x, position_y,
                                    speed_x, speed_y,
                                    angle, angle_derivative,
                                    object_type)
    }
    player_object() = delete; // No making a player object without specifying its characteristics.

    ~player_object();

public:
    faction_t get_faction() {
        return this->belongs_to; }
    /*  // FORBIDDEN! THE FACTION IS CONSTANT!
    void set_faction(faction_t new_faction) {
        this->belongs_to = new_faction; }
    */
}

