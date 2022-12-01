/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Audio
*/

#include "Audio.hpp"

RayLib::Audio::Audio(float musicVolume, float soundVolume) : _musicVolume(musicVolume), _soundVolume(soundVolume)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitAudioDevice();
    if (!isAudioDeviceReady())
        throw Error::AudioError("audio failed to initialize");
}

RayLib::Audio::~Audio()
{
    CloseAudioDevice();
}

bool RayLib::Audio::isAudioDeviceReady() const
{
    return (IsAudioDeviceReady());
}

void RayLib::Audio::setMasterVolume(float volume)
{
    SetMasterVolume(volume);
}

void RayLib::Audio::setMusicVolume(float volume)
{
    _musicVolume = volume;
}

float RayLib::Audio::getMusicVolume() const
{
    return (_musicVolume);
}

void RayLib::Audio::setSoundVolume(float volume)
{
    _soundVolume = volume;
}

float RayLib::Audio::getSoundVolume() const
{
    return (_soundVolume);
}
