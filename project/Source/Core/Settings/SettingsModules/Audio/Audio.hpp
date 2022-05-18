/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <string>
#include <any>

#include <utility>

#include "raylib.h"

namespace RayLib
{
    class Audio
    {
        public:
            Audio();
            ~Audio();

            // Audio management functions
            void initAudioDevice(void);                                         // Initialize audio device and context
            void closeAudioDevice(void);                                        // Close the audio device and context

            bool isAudioDeviceReady(void);                                      // Check if audio device has been initialized successfully

            void setMasterVolume(float volume);                                 // Set master volume (listener)

        protected:
        private:
    };
}

#endif /* !AUDIO_HPP_ */
