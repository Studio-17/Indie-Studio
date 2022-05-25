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
    class Audio
    {
        public:
            Audio(float audioVolume, float soundVolume);
            ~Audio();

            // Audio management functions
            bool isAudioDeviceReady() const;                                      // Check if audio device has been initialized successfully

            void setMasterVolume(float volume);                                 // Set master volume (listener)

            // Game Audio management functions
            void setAudioVolume(float volume);                                  // Set audio volume
            float getAudioVolume() const;                                         // Get audio volume

            void setSoundVolume(float volume);                                  // Set sound volume
            float getSoundVolume() const;                                         // Get sound volume

        protected:
        private:
            float _audioVolume;
            float _soundVolume;
    };
}

#endif /* !AUDIO_HPP_ */
