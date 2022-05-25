/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Core
*/

#include "SettingsScene.hpp"
#include "SplashScreenScene.hpp"
#include "MainMenuScene.hpp"
#include "tools.hpp"
#include "Core.hpp"

Core::Core() : _settings(std::make_shared<Settings>(loadSettings("Conf/settings.conf"))), _isRunning(true),
    _activeScene(Scene::Scenes::MAIN_MENU)
{
    loadMenuScenes();
}

Core::~Core()
{
}

void Core::loadMenuScenes()
{
    _menuScenes.emplace(Scene::Scenes::MAIN_MENU, std::make_shared<Scene::MainMenuScene>(_settings));
    // _menuScenes.emplace(Scene::Scenes::SPLASH_SCREEN, std::make_shared<Scene::SplashScreenScene>());
    _menuScenes.emplace(Scene::Scenes::SETTINGS, std::make_shared<Scene::SettingsScene>(_settings));
    //rajouter toutes les scènes des menus
}

void Core::loop()
{
    while (!_settings->getWindow()->windowShouldClose() && _activeScene != Scene::Scenes::QUIT) {
        // _menuScenes.at(_activeScene)->run();
        _settings->getWindow()->startDrawing();
            _activeScene = _menuScenes.at(_activeScene)->handelEvent();

            _settings->getWindow()->clearBackground(BLACK);
            _menuScenes.at(_activeScene)->draw();

            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        _settings->getWindow()->endDrawing();
    }
}

void Core::getEvent()
{

}
