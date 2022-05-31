/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Core
*/

#include "MainMenuScene.hpp"
#include "SettingsScene.hpp"
#include "SelectGameMenuScene.hpp"

#include "tools.hpp"
#include "Map.hpp"
#include "Core.hpp"

Core::Core() : _isRunning(true),
    _activeScene(Scene::Scenes::MAIN_MENU)
{
    SettingsParams settingsParams;

    settingsParams.loadFromData("Conf/settings.json");
    _settings = std::make_shared<Settings>(settingsParams),
    loadMenuScenes();
}

Core::~Core()
{
}

void Core::loadMenuScenes()
{
    _menuScenes.emplace(Scene::Scenes::MAIN_MENU, std::make_shared<Scene::MainMenuScene>(_settings));
    _menuScenes.emplace(Scene::Scenes::SETTINGS, std::make_shared<Scene::SettingsScene>(_settings));
    _menuScenes.emplace(Scene::Scenes::GAME, std::make_shared<Scene::SelectGameMenuScene>(_settings));
    //rajouter toutes les scènes des menus
}

void Core::loop()
{
    while (!_settings->getWindow()->windowShouldClose() && _activeScene != Scene::Scenes::QUIT) {
        _settings->getWindow()->startDrawing();
        _settings->getWindow()->clearBackground(DARKGRAY);

        _activeScene = _menuScenes.at(_activeScene)->handelEvent();
        if (_activeScene == Scene::Scenes::QUIT)
            continue;
        _menuScenes.at(_activeScene)->draw();

        _settings->getWindow()->endDrawing();
    }
}

void Core::getEvent()
{

}
