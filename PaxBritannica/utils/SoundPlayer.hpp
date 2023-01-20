//
//  soundplayer.hpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2023/1/12.
//

#ifndef soundplayer_hpp
#define soundplayer_hpp

#include <thread>
#include <mutex>

class SoundPlayer {
public:
    SoundPlayer(const char *name);
    ~SoundPlayer();
    void play();
    void stop();
    bool isPlaying();
private:
    std::thread *music {nullptr};
    bool playing {false};
};

#endif /* soundplayer_hpp */
