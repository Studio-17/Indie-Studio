/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Core
*/

#include "SettingsScene.hpp"
#include "Core.hpp"

Core::Core() : _isRunning(true),
    _scenes({{Scene::Scenes::SETTINGS, std::make_shared<Scene::SettingsScene>()}}),
    _activeScene(Scene::Scenes::SETTINGS)
{
}

Core::~Core()
{
}

void Core::loop()
{
    while (_isRunning) {
        _scenes.at(_activeScene)->run();
    }
}
