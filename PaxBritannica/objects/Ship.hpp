//
//  Ship.hpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2023/2/15.
//

/*
 The Ship class represents a ship in the game. It has several member variables that store information about the ship's characteristics, including whether it is a large or small ship, its variant, speed, health, and position on the screen.
 */

#ifndef Ship_hpp
#define Ship_hpp

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <stdexcept>


class Ship {
    friend class Environment;
    friend bool operator==(const Ship& s1, const Ship& s2) {
        return s1.id == s2.id;
    }
    friend bool operator!=(const Ship& s1, const Ship& s2) {
        return s1.id != s2.id;
    }
public:
    Ship() {};
    // constructor with parameters
    Ship(unsigned int id, bool large, int variant, int speed, int health): id(id), large{large}, variant{variant}, speed{speed}, health{health} {
        if (!variant || variant > 4)
            throw std::runtime_error("Only 4 types of ship is supported!");
    }
    
    // set the position of the ship
    void SetPosition(int x, int y) {
        pos.x = x;
        pos.y = y;
    }
    
    // update the ship's position by moving it to the left
    void Update() {
        pos.x -= speed;
    }
    
    // reduce the ship's health by dmg, and return whether the ship has been destroyed
    bool GotHit(int dmg) {
        health -= dmg;
        if (health < 0)
            health = 0;
        return health == 0;
    }
    
    bool isPlayer() { return variant < 0; }
    
private:
    unsigned int id;
    bool large;
    int variant;
    int speed;
    int health {1};
    int score {0};
    
    wxPoint pos;
};

#endif /* Ship_hpp */
