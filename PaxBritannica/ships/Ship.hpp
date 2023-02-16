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
public:
    Ship() {};
    Ship(bool large, int variant, int speed, int health = 1): large{large}, variant{variant}, speed{speed}, health{health} {
        if (!variant || variant > 4)
            throw std::runtime_error("Only 4 types of ship is supported!");
    }
    
    int getVariant() { return variant; }
    
    bool isLarge() { return large; }
    
    void SetPosition(int x, int y) {
        pos.x = x;
        pos.y = y;
    }
    
    void Update() {
        pos.x -= speed;
    }
    
    wxPoint& GetPosition() { return pos; }
    
    bool GotHit(int dmg) {
        health -= dmg;
        return health > 0;
    }
    
    bool isPlayer() { return variant < 0; }
    
private:
    int speed;
    int health {1};
    bool large;
    int variant;
    wxPoint pos;
};

#endif /* Ship_hpp */
