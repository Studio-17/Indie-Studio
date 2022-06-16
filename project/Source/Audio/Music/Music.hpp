/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Music
*/

#ifndef MUSIC_HPP_
    #define MUSIC_HPP_

    #include <raylib.h>

    #include <nlohmann/json.hpp>

    #include <string>

    #include "IAudio.hpp"

class MyMusic : public IAudio {
    public:
        MyMusic(std::string const &filename);
        MyMusic(nlohmann::json const &jsonData);
        MyMusic();
        ~MyMusic();

        MyMusic &operator =(std::string const &filename);

        void play() override;                       // Start music playing
        void stop() override;                       // Stop music playing
        void pause() override;                      // Pause music playing
        void resume() override;                     // Resume playing paused music

        bool isPlaying() const override;                  // Check if music is playing
        void setVolume(float volume) override;      // Set volume for music (1.0 is max level)
        void updateMusicStream();

    protected:
    private:
        Music _music;
};

#endif /* !MUSIC_HPP_ */
