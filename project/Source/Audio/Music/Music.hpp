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

/**
 * @brief MyMusic Class
 */
class MyMusic : public IAudio {
    public:
        /**
         * @brief Construct a new My Music object
         *
         * @param filename
         */
        MyMusic(std::string const &filename);
        /**
         * @brief Construct a new My Music object
         *
         * @param jsonData
         */
        MyMusic(nlohmann::json const &jsonData);
        /**
         * @brief Construct a new My Music object
         */
        MyMusic();
        /**
         * @brief Destroy the My Music object
         */
        ~MyMusic();

        /**
         * @brief Using operator overload for comparison
         *
         * @param filename
         * @return MyMusic&
         */
        MyMusic &operator =(std::string const &filename);

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
        /**
         * @brief Upadte Music stream
         */
        void updateMusicStream();

    protected:
    private:
        Music _music; ///< Music object

};

#endif /* !MUSIC_HPP_ */
