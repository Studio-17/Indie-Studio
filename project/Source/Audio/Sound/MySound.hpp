/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MySound
*/

#ifndef MYSOUND_HPP_
    #define MYSOUND_HPP_

    #include <raylib.h>

    #include <nlohmann/json.hpp>

    #include <string>

    #include "IAudio.hpp"

class MySound : public IAudio {
    public:
        MySound(std::string const &filename);
        MySound(nlohmann::json const &jsonData);

        MySound();
        ~MySound();

        MySound &operator =(std::string const &filename);

        void play() override;
        void stop() override;
        void pause() override;
        void resume() override;
        bool isPlaying() const override;
        void setVolume(float volume) override;
    protected:
    private:
        Sound _sound;
};

#endif /* !MYSOUND_HPP_ */
