/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <string>
#include <any>

#include <utility>

#include "raylib.h"

#include "IAudio.hpp"

class MyMusic : public IAudio {
    public:
        MyMusic(std::string const &filename);
        ~MyMusic();

        // Music management functions
        void play() override;                       // Start music playing
        void stop() override;                       // Stop music playing
        void pause() override;                      // Pause music playing
        void resume() override;                     // Resume playing paused music

        bool isPlaying() override;                  // Check if music is playing
        void setVolume(float volume) override;      // Set volume for music (1.0 is max level)

    protected:
    private:
        Music _music;
};

#endif /* !MUSIC_HPP_ */
