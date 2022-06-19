/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
    #define AUDIO_HPP_

    #include <raylib.h>

    #include <string>
    #include <any>
    #include <utility>

    #include "AudioError.hpp"

namespace RayLib
{
    /**
     * @brief Audio calss that handles RAII and handling of all audio related stuff
     */
    class Audio
    {
        public:
            /**
             * @brief Construct a new Audio object
             *
             * @param musicVolume
             * @param soundVolume
             */
            Audio(float musicVolume, float soundVolume);
            /**
             * @brief Destroy the Audio object
             *
             */
            ~Audio();

            /**
             * @brief Check if audio device has been initialized successfully
             *
             * @return true
             * @return false
             */
            bool isAudioDeviceReady() const;

            /**
             * @brief Set the Master Volume
             *
             * @param volume
             */
            void setMasterVolume(float volume);

            /**
             * @brief Set the Music Volume
             *
             * @param volume
             */
            void setMusicVolume(float volume);
            /**
             * @brief Get the Music Volume
             *
             * @return float
             */
            float getMusicVolume() const;

            /**
             * @brief Set the Sound Volume
             *
             * @param volume
             */
            void setSoundVolume(float volume);
            /**
             * @brief Get the Sound Volume
             *
             * @return float
             */
            float getSoundVolume() const;

        protected:
        private:
            float _musicVolume; ///< Music volume
            float _soundVolume; ///< Sound volume
    };
}

#endif /* !AUDIO_HPP_ */
