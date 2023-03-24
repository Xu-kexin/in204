//
//  Environment.cpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2023/2/15.
//

#include <stdexcept>

#include "Environment.hpp"

const char* player_ship_icon="res/player%d.png";
const char* small_ship_icon = "res/bomberp%d.png";
const char* large_ship_icon = "res/frigatep%d.png";

#define PLAYER_SPEED        6
#define PLAYER_HP           5
#define LARGE_SHIP_SPEED    3
#define LARGE_SHIP_HP       3
#define SMALL_SHIP_SPEED    5
#define SMALL_SHIP_HP       1
#define BULLET_SIZE         8

// Constructor of the Environment class
Environment::Environment(wxSize size, wxPoint offset): player_imgs(2), size(size), offset(offset) {
    wxLogNull AD;
    wxInitAllImageHandlers();
    char temp[20] = {0};
    // Load image files for small and large bot ships
    for (int i=1; i<=4; i++) {
        snprintf(temp, 20, small_ship_icon, i);
        ship_imgs[0][i-1].LoadFile(temp, wxBITMAP_TYPE_ANY);
        snprintf(temp, 20, large_ship_icon, i);
        ship_imgs[1][i-1].LoadFile(temp, wxBITMAP_TYPE_ANY);
    }
    // Load image files for player ships
    snprintf(temp, 20, player_ship_icon, 1);
    player_imgs[0].LoadFile(temp, wxBITMAP_TYPE_ANY);
    snprintf(temp, 20, player_ship_icon, 2);
    player_imgs[1].LoadFile(temp, wxBITMAP_TYPE_ANY);
    // Draw image file for bomb
    wxBrush b(RED);
    wxMemoryDC dc;
    
    bullet_img[0].Create(BULLET_SIZE, BULLET_SIZE);
    dc.SelectObject(bullet_img[0]);
    dc.SetBrush(b);
    dc.DrawCircle(BULLET_SIZE/2, BULLET_SIZE/2, BULLET_SIZE/2);

    bullet_img[1].Create(BULLET_SIZE, BULLET_SIZE);
    dc.SelectObject(bullet_img[1]);
    b.SetColour(BLUE);
    dc.SetBrush(b);
    dc.DrawCircle(BULLET_SIZE/2, BULLET_SIZE/2, BULLET_SIZE/2);
    dc.SelectObject(wxNullBitmap);
}

// Add player ships to the game environment
void Environment::AddPlayer() {
    if (player_cnt >= 2)
        throw std::runtime_error("Only 2 players maximum");
    
    player_cnt++;
    for (int i=0; i<2; i++) {
        if (player_ref[i] == nullptr) {
            Ship s(counter++, true, -(i+1), PLAYER_SPEED, PLAYER_HP);
            s.SetPosition(0, size.GetHeight()/2 - player_imgs[0].GetHeight()*(player_cnt==2));
            ships.push_back(s);
            player_ref[i] = &ships.back();
            break;
        }
    }
}

// Add a bot ship to the game environment
void Environment::AddBot(bool large) {
    int variant = rand()%4+1;
    int speed = large ? LARGE_SHIP_SPEED : SMALL_SHIP_SPEED;
    int hp = large ? LARGE_SHIP_HP : SMALL_SHIP_HP;
    int try_cnt = 0;
    Ship s(counter++, large, variant, speed, hp);
    do {
        int x = size.GetWidth();
        // 17/20h-10-1/20h-24=4/5h-34
//        int y = rand()%(size.GetHeight()*4/5-34-img->GetHeight()) + size.GetHeight()/20+24;
        int y = rand() % (size.GetHeight() - ship_imgs[large][0].GetHeight());
        s.SetPosition(x, y);
    } while(CheckCollision(s, true) && try_cnt++ < 5);
    
    // Set the position of the bot ship to a random location on the right side of the screen
    ships.push_back(s);
}

// Add a bomb to the game environment
void Environment::Shoot(int player_id) {
    if (!IsPlayerAlive(player_id))
        return;
    Bullet b(player_ref[player_id-1]->pos.x+player_imgs[0].GetWidth()-BULLET_SIZE, player_ref[player_id-1]->pos.y+player_imgs[0].GetHeight()/2-BULLET_SIZE/2);
    bullets[player_id-1].push_back(b);
}

// Update the game environment
bool Environment::Step() {
    for(auto s=ships.begin(); s != ships.end();) {
        if (!s->isPlayer()) {
            s->Update();
            if (s->pos.x + ship_imgs[s->large][0].GetWidth() <= 0) {
                auto it = s;
                it++;
                ships.erase(s);
                s = it;
                continue;
            }
        }
        s++;
    }
    for (int i=0; i < 2; i++) {
        for (auto& b: bullets[i]) {
            b.Update();
        }
    }
    for (auto s=ships.begin(); s!=ships.end();) {
        int by_player = CheckCollision(*s, false);
        if (by_player && s->GotHit(LARGE_SHIP_HP)) {
            auto it = s;
            it++;
            DestoryShip(by_player, *s);
            s = it;
        } else
            s++;
    }
    return player_cnt > 0;
}

// Check for collisions between ships then bullets
// return 0 if no collsion
// return player_id if s not player and collision detected
// return 1 is if s player and collision detected
int Environment::CheckCollision(Ship& s, bool detect_only) {
    int x1 = s.pos.x;
    int y1 = s.pos.y;
    int w1, h1;
    if (s.isPlayer()) {
        w1 = player_imgs[0].GetWidth();
        h1 = player_imgs[0].GetHeight();
    } else {
        w1 = ship_imgs[s.large][0].GetWidth();
        h1 = ship_imgs[s.large][0].GetHeight();
    }
    for (auto& ss: ships) {
        if (ss != s) {
            int x2 = ss.pos.x;
            int y2 = ss.pos.y;
            int w2, h2;
            if (ss.isPlayer()) {
                w2 = player_imgs[0].GetWidth();
                h2 = player_imgs[0].GetHeight();
            } else {
                w2 = ship_imgs[s.large][0].GetWidth();
                h2 = ship_imgs[s.large][0].GetHeight();
            }

            if (x1 < x2 + w2 && x1 + w1 > x2 &&
                y1 < y2 + h2 && y1 + h1 > y2) {
                if (detect_only)
                    return 1;
                if (ss.isPlayer() != s.isPlayer()) {
                    if (ss.GotHit(LARGE_SHIP_HP)) {
                        DestoryShip(-s.variant, ss);
                    }
                    if (s.isPlayer())
                        return 1;
                    else
                        return -ss.variant;
                }
            }
        }
    }
    
    if (s.isPlayer())
        return 0;
    
    for (int i=0; i<2; i++) {
        for (auto b=bullets[i].begin(); b != bullets[i].end(); b++) {
            int x2 = b->pos.x;
            int y2 = b->pos.y;
            int w2 = bullet_img[0].GetWidth();
            int h2 = bullet_img[0].GetHeight();
            if (x1 < x2 + w2 && x1 + w1 > x2 &&
                y1 < y2 + h2 && y1 + h1 > y2) {
                bullets[i].erase(b);
                return i+1;
            }
        }
    }
    return 0;
}

void Environment::DestoryShip(int by_player, Ship &ship) {
    if (ship.isPlayer()) {
        player_ref[-ship.variant-1] = nullptr;
        player_cnt--;
        ships.remove(ship);
    } else {
        if (IsPlayerAlive(by_player))
            player_ref[by_player-1]->score += 5*(1+ship.large);
        ships.remove(ship);
    }
}

// Draw ships and bullets on the screen
void Environment::Draw(wxPaintDC& dc) {
    for (auto& s: ships) {
        wxBitmap img;
        if (s.isPlayer()) {
            // Use the player ship image if the ship is a player ship
            img = player_imgs[-s.variant-1];
        } else {
            // Use the bot ship image if the ship is a bot ship
            img = ship_imgs[s.large][s.variant-1];
        }
        dc.DrawBitmap(img, s.pos+offset, true);
    }
    for (int i=0; i<2; i++) {
        for (auto& b: bullets[i]) {
            dc.DrawBitmap(bullet_img[i], b.pos+offset, true);
        }
    }
}

int Environment::GetScore(int player_id) {
    if (IsPlayerAlive(player_id))
        return player_ref[player_id-1]->score;
    return 0;
}

unsigned int Environment::GetHp(int player_id) {
    if (IsPlayerAlive(player_id))
        return player_ref[player_id-1]->health;
    return 0;
}

void Environment::MovePlayer(int player_id, MoveDirection dir) {
    if (IsPlayerAlive(player_id)) {
        Ship* s = player_ref[player_id-1];
        switch (dir) {
            case UP:
                s->pos.y = std::max(s->pos.y-s->speed, 0);
                break;
            case DOWN:
                s->pos.y = std::min(s->pos.y+s->speed, size.GetHeight()-player_imgs[0].GetHeight());
                break;
            case LEFT:
                s->pos.x = std::max(s->pos.x-s->speed, 0);
                break;
            case RIGHT:
                s->pos.x = std::min(s->pos.x+s->speed, size.GetWidth()-player_imgs[0].GetWidth());
                break;
            default:
                break;
        }
    }
}

bool Environment::IsPlayerAlive(int player_id) {
    return player_ref[player_id-1] != nullptr;
}
