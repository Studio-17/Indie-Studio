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

/**
 * @brief 
 * 
 */
class MySound : public IAudio {
    public:
        /**
         * @brief Construct a new My Sound object
         *
         * @param filename
         */
        MySound(std::string const &filename);
        /**
         * @brief Construct a new My Sound object
         *
         * @param jsonData
         */
        MySound(nlohmann::json const &jsonData);

        /**
         * @brief Construct a new My Sound object
         */
        MySound();
        /**
         * @brief Destroy the My Sound object
         */
        ~MySound();

        /**
         * @brief Using operator overload for comparison
         *
         * @param filename
         * @return MySound&
         */
        MySound &operator =(std::string const &filename);

        /**
         * @brief Start music playing
         */
        void play() override;
        /**
         * @brief Stop music playing
         */
        void stop() override;
        /**
         * @brief Pause music playing
         */
        void pause() override;
        /**
         * @brief Resume playing paused music
         */
        void resume() override;

        /**
         * @brief Check if music is playing
         *
         * @return true
         * @return false
         */
        bool isPlaying() const override;
        /**
         * @brief Set the Volume object
         *
         * @param volume
         */
        void setVolume(float volume) override;

    protected:
    private:
        Sound _sound; ///< Sound object
};

#endif /* !MYSOUND_HPP_ */
