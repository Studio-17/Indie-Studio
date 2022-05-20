/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Settings
*/

#include "Settings.hpp"

Settings::Settings()
{
    _audio = std::make_unique<RayLib::Audio>();
    _camera = std::make_unique<RayLib::CinematicCamera>();
    _window = std::make_unique<RayLib::Window>();
}

Settings::~Settings()
{
}
