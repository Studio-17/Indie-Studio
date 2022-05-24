/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SettingsParams
*/

#include "SettingsParams.hpp"

SettingsParams::SettingsParams() :
    _title("Raylib project"), _windowSize({1920, 1080}), _audioVolume(100), _musicVolume(100),
    _cameraPosition(0, 0, 0), _cameraTarget(0, 0, 0), _cameraMode(CAMERA_CUSTOM), _cameraProjection(CAMERA_PERSPECTIVE)
{
}

SettingsParams::~SettingsParams()
{
}
