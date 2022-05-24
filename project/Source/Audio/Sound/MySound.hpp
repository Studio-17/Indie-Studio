/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MySound
*/

#ifndef MYSOUND_HPP_
    #define MYSOUND_HPP_

    #include <string>
    #include <any>
    #include <utility>


    #include "raylib.h"

    #include "IAudio.hpp"

class MySound : public IAudio {
    public:
        MySound(std::string const &filename);
        MySound() {};
        ~MySound();
        // Sound management functions
        void play() override;                       // Play a sound
        void stop() override;                       // Stop playing a sound
        void pause() override;                      // Pause a sound
        void resume() override;                     // Resume a paused sound
        bool isPlaying() override;                  // Check if a sound is currently playing
        void setVolume(float volume) override;      // Set volume for a sound (1.0 is max level)
    protected:
    private:
        Sound _sound;
};

#endif /* !MYSOUND_HPP_ */
