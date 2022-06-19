/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Test
*/

#include "raylib.h"

#include <assert.h>

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <unistd.h>
#include "Audio/IAudio.hpp"
#include "Audio/Music/Music.hpp"

Test(Audio, audioTest)
{
    std::string path("Tests/Ressources/musics/music.ogg");
    MyMusic music(path);

    music.setVolume(10.0f);

    while (1) {
        music.updateMusicStream();

        music.play();

        music.pause();
        if (music.isPlaying() == false)
            music.resume();

        music.stop();

        break;
    }

    assert(true);
}
