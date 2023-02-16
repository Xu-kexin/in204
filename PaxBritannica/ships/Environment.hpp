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

class Environment {
public:
    Environment(wxSize size);
    
    void AddPlayer(int cnt);
    
    void AddBot();
    
    void Step();
    
    void CheckCollision();
    
    void DrawShips(wxPaintDC& dc);
    
private:
    std::vector<wxBitmap> small_ship_imgs;
    std::vector<wxBitmap> large_ship_imgs;
    std::vector<wxBitmap> player_imgs;
    
    std::list<Ship> ships;
    wxSize size;
    
    int player_cnt {0};
};

#endif /* Environment_hpp */
