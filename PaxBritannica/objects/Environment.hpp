//
//  Environment.hpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2023/2/15.
//

/*
The constructor of the Environment class loads image files for player and bot ships, and stores them in member variables. The AddPlayer method adds player ships to the game environment. The AddBot method adds a bot ship to the game environment. The Step method updates the state of the game environment. The CheckCollision method checks for collisions between ships. The DrawShips method draws the ships on the screen.
*/


#ifndef Environment_hpp
#define Environment_hpp

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <vector>
#include <list>
#include <random>

#include "Ship.hpp"
#include "Bullet.hpp"

enum MoveDirection {
    UP      = 1<<1,
    DOWN    = 1<<2,
    LEFT    = 1<<3,
    RIGHT   = 1<<4
};

class Environment {
public:
    Environment(wxSize size, wxPoint offset);
    
    void AddPlayer();
    
    void AddBot(bool large);
    
    void Shoot(int player_id);
    
    bool Step();
    
    int CheckCollision(Ship& s, bool detect_only);
    
    void Draw(wxPaintDC& dc);
    
    int GetScore(int player_id);
    
    unsigned int GetHp(int player_id);
    
    void MovePlayer(int player_id, MoveDirection dir);
    
private:
    std::vector<wxBitmap> ship_imgs[2] {std::vector<wxBitmap>(4), std::vector<wxBitmap>(4)};
    std::vector<wxBitmap> player_imgs;
    wxBitmap bullet_img;
    
    std::list<Ship> ships;
    Ship* player_ref[2] {nullptr, nullptr};
    std::list<Bullet> bullets[2];
    
    // Game area parameters
    wxSize size;
    wxPoint offset;
    
    int player_cnt {0};
    unsigned int counter {1};
    
    void DestoryShip(int by_player, Ship& ship);
};

#endif /* Environment_hpp */
