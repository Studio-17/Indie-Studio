/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Music
*/

#include "Errors/ErrorsModules/ErrorsSettings.hpp"

#include "Music.hpp"

MyMusic::MyMusic(std::string const &filename) : _music(LoadMusicStream(filename.c_str()))
{
    if (!_music.ctxData)
        throw Error::ErrorsSettings(std::cerr, "MyMusic initialization failed");
}

MyMusic::~MyMusic()
{
    UnloadMusicStream(_music);
}

void MyMusic::play()
{
    PlayMusicStream(_music);
}

void MyMusic::stop()
{
    StopMusicStream(_music);
}

void MyMusic::pause()
{
    PauseMusicStream(_music);
}

void MyMusic::resume()
{
    ResumeMusicStream(_music);
}

bool MyMusic::isPlaying()
{
    return (IsMusicStreamPlaying(_music));
}

void MyMusic::setVolume(float volume)
{
    SetMusicVolume(_music, volume);
}
