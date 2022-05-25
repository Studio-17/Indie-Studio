/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Audio
*/

#include "Audio.hpp"

RayLib::Audio::Audio(float audioVolume, float soundVolume) : _audioVolume(audioVolume), _soundVolume(soundVolume)
{
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

void RayLib::Audio::setAudioVolume(float volume)
{
    _audioVolume = volume;
}

float RayLib::Audio::getAudioVolume() const
{
    return (_audioVolume);
}

void RayLib::Audio::setSoundVolume(float volume)
{
    _soundVolume = volume;
}

float RayLib::Audio::getSoundVolume() const
{
    return (_soundVolume);
}
