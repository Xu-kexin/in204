//
//  soundplayer.hpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2023/1/12.
//

/*
 This is a C++ implementation for playing sounds using the mpg123 library and the ao library. The implementation defines a SoundPlayer class with methods for playing, stopping and checking if a sound is playing.

 The play method starts playing the sound and the stop method stops it. The isPlaying method returns a boolean indicating if the sound is currently playing or not.

 The implementation also includes a separate soundplay function that is used by the SoundPlayer class to actually play the sound. This function initializes the libraries, opens the file, sets the output format, and then continuously decodes and plays the sound in a loop. It also checks for a should_exit flag to stop playing the sound when needed.

 There is a music_lock mutex used to synchronize the playing and stopping of the sound, and a playing flag to keep track of whether the sound is currently playing or not. The implementation also checks if the sound file was opened successfully before playing it, and prints an error message and exits if it wasn't.
 */

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
