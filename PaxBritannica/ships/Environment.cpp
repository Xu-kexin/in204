//
//  Environment.cpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2023/2/15.
//


#include "Environment.hpp"

const char* player_ship_icon="res/player%d.png";
const char* small_ship_icon = "res/bomberp%d.png";
const char* large_ship_icon = "res/frigatep%d.png";

// Constructor of the Environment class
Environment::Environment(wxSize size): size(size), small_ship_imgs(4), large_ship_imgs(4), player_imgs(2) {
    wxLogNull AD;
    wxInitAllImageHandlers();
    char temp[20] = {0};
    bool f;
    // Load image files for small and large bot ships
    for (int i=1; i<=4; i++) {
        snprintf(temp, 20, small_ship_icon, i);
        f = small_ship_imgs[i-1].LoadFile(temp, wxBITMAP_TYPE_ANY);
        snprintf(temp, 20, large_ship_icon, i);
        f = large_ship_imgs[i-1].LoadFile(temp, wxBITMAP_TYPE_ANY);
    }
    // Load image files for player ships
    snprintf(temp, 20, player_ship_icon, 1);
    f = player_imgs[0].LoadFile(temp, wxBITMAP_TYPE_ANY);
    snprintf(temp, 20, player_ship_icon, 2);
    f = player_imgs[1].LoadFile(temp, wxBITMAP_TYPE_ANY);
}
// Add player ships to the game environment
void Environment::AddPlayer(int cnt) {
    int dis = size.GetHeight()/(cnt+1);
    int x = dis;
    for (int i=1; i<=cnt; i++) {
        Ship s(true, -i, 3, 5);
        s.SetPosition(0, x-player_imgs[0].GetHeight()/2);
        ships.push_back(s);
        x += dis;
    }
}
// Add a bot ship to the game environment
void Environment::AddBot() {
    // Randomly decide whether to add a large or small bot ship
    bool large = rand()%10 >= 9;
    int variant = rand()%4+1;
    auto img = large ? large_ship_imgs.begin() : small_ship_imgs.begin();
    Ship s(large, variant, 1+!large, 1+large);
    // Set the position of the bot ship to a random location on the right side of the screen
    s.SetPosition(size.GetWidth()-img->GetWidth(), rand()%(size.GetHeight()-img->GetHeight()));
    ships.push_back(s);
}

// Update the game environment
void Environment::Step() {
    for(auto& s: ships) {
        if (!s.isPlayer())
            s.Update();
    }
}

// Check for collisions between ships
void Environment::CheckCollision() {
    for (auto& s: ships) {
        for (auto& ss: ships) {
            if (!s.isPlayer() && !ss.isPlayer())
                continue;
            //TODO: 检查碰撞
        }
    }
}

// Draw the ships on the screen
void Environment::DrawShips(wxPaintDC& dc) {
    for (auto& s: ships) {
        wxBitmap img;
        if (s.isPlayer()) {
            // Use the player ship image if the ship is a player ship
            img = player_imgs[-s.getVariant()-1];
        } else {
            // Use the bot ship image if the ship is a bot ship
            if (s.isLarge())
                img = large_ship_imgs[s.getVariant()-1];
            else
                img = small_ship_imgs[s.getVariant()-1];
        }
        dc.DrawBitmap(img, s.GetPosition());
    }
}
