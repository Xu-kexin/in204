//
//  soundplayer.cpp
//  PaxBritannica
//
//  Created by Laurine Xu on 2023/1/12.
//

#include "SoundPlayer.hpp"
#include <iostream>
#include <ao/ao.h>
#include <mpg123.h>

#define BITS 8

std::mutex music_lock;
bool should_exit = false;

void soundplay(const char *filename)
{
    mpg123_handle *mh;
    char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;

    /* initializations */
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh)/2;
    buffer = (char*) malloc(buffer_size * sizeof(char));

    /* open the file and get the decoding format */
    mpg123_open(mh, filename);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    /* decode and play */
    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
        music_lock.lock();
        if (should_exit)
            break;
        ao_play(dev, buffer, done);
        music_lock.unlock();
    }

    /* clean up */
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
}

SoundPlayer::SoundPlayer(const char *name){
    if (!fopen(name, "rb")) {
        std::cout << "Open sound file failed!" << std::endl;
        exit(-1);
    }
    music_lock.lock();
    music = new std::thread(soundplay, name);
}

SoundPlayer::~SoundPlayer() {
    should_exit = true;
    music_lock.unlock();
    music->join();
    delete music;
}

void SoundPlayer::play() {
    music_lock.unlock();
    playing = true;
}

void SoundPlayer::stop() {
    music_lock.lock();
    playing = false;
}

bool SoundPlayer::isPlaying() {
    return playing;
}
