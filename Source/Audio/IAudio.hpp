/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP_
    #define IAUDIO_HPP_

/**
 * @brief Audio Interface to handle Sounds and Musics
 */
class IAudio {
    public:
        /**
         * @brief Destroy the IAudio object
         */
        virtual ~IAudio() = default;

        /**
         * @brief Start music playing
         */
        virtual void play() = 0;
        /**
         * @brief Stop music playing
         */
        virtual void stop() = 0;
        /**
         * @brief Pause music playing
         */
        virtual void pause() = 0;
        /**
         * @brief Resume playing paused music
         */
        virtual void resume() = 0;

        /**
         * @brief Check if music is playing
         *
         * @return true
         * @return false
         */
        virtual bool isPlaying() const = 0;
        /**
         * @brief Set the Volume object
         *
         * @param volume
         */
        virtual void setVolume(float volume) = 0;

    protected:
    private:
};

#endif /* !IAUDIO_HPP_ */
