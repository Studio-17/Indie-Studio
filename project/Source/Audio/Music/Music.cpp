/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Music
*/

#include "AudioError.hpp"
#include "Music.hpp"

MyMusic::MyMusic(std::string const &filename) : _music(LoadMusicStream(filename.c_str()))
{
    if (!_music.ctxData)
        throw Error::AudioError("MyMusic initialization failed");
}

MyMusic::MyMusic(nlohmann::json const &jsonData) : _music(LoadMusicStream(jsonData.value("musicPath", "default").c_str()))
{
    if (!_music.ctxData)
        throw Error::AudioError("MyMusic initialization failed");
}

MyMusic::~MyMusic()
{
    UnloadMusicStream(_music);
}

MyMusic &MyMusic::operator =(std::string const &filename)
{
    _music = LoadMusicStream(filename.c_str());
    if (!_music.ctxData)
        throw Error::AudioError("MyMusic initialization failed");
    return *this;
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

bool MyMusic::isPlaying() const
{
    return (IsMusicStreamPlaying(_music));
}

void MyMusic::setVolume(float volume)
{
    SetMusicVolume(_music, volume);
}

void MyMusic::updateMusicStream()
{
    UpdateMusicStream(_music);
}