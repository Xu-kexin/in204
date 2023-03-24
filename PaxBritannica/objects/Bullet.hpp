//
//  bullet.hpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2023/2/18.
//

#ifndef bullet_hpp
#define bullet_hpp

#define BULLET_SPEED 10

class Bullet {
    friend class Environment;
public:
    Bullet(int x, int y): pos(x, y) {};
    
    void Update() {
        pos.x += speed;
    }
    
private:
    int speed {BULLET_SPEED};
    wxPoint pos;
};


#endif /* bullet_hpp */
