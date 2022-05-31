/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Core
*/

#include <raylib.h>

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
    _actionPressed = {
    {Action::Next, KEY_ENTER},
    {Action::Previous, KEY_BACKSPACE},
    {Action::Right, KEY_D},
    {Action::Left, KEY_Q},
    {Action::Up, KEY_Z},
    {Action::Down, KEY_S}};
    _playerActions = {
    {
    {PlayerAction::MoveLeft, KEY_LEFT},
    {PlayerAction::MoveRight, KEY_RIGHT},
    {PlayerAction::MoveUp, KEY_UP},
    {PlayerAction::MoveDown, KEY_DOWN},
    {PlayerAction::Drop, KEY_A}
    },
    {
    {PlayerAction::MoveLeft, KEY_Q},
    {PlayerAction::MoveRight, KEY_D},
    {PlayerAction::MoveUp, KEY_Z},
    {PlayerAction::MoveDown, KEY_S},
    {PlayerAction::Drop, KEY_A}
    },
    {
    {PlayerAction::MoveLeft, KEY_K},
    {PlayerAction::MoveRight, KEY_M},
    {PlayerAction::MoveUp, KEY_O},
    {PlayerAction::MoveDown, KEY_L},
    {PlayerAction::Drop, KEY_P}
    },
 {
    {PlayerAction::MoveLeft, KEY_Q},
    {PlayerAction::MoveRight, KEY_D},
    {PlayerAction::MoveUp, KEY_Z},
    {PlayerAction::MoveDown, KEY_S},
    {PlayerAction::Drop, KEY_A}
    }};

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

        getEvent();
        _activeScene = _menuScenes.at(_activeScene)->handelEvent();
        if (_activeScene == Scene::Scenes::QUIT)
            continue;
        _menuScenes.at(_activeScene)->draw();

        _settings->getWindow()->endDrawing();
    }
}

void Core::getEvent()
{
    std::map<Action, bool> actionPressed = _keyboard.getKeysPressed<Action>(_actionPressed);
    std::map<PlayerAction, bool> playerAction;
    std::vector<std::map<PlayerAction, bool>> playerActions;
    std::size_t index = 0;

    for (auto &player : _playerActions) {
        playerActions.emplace_back(_keyboard.getKeysPressed<PlayerAction>(player));
        index++;
    }
    _settings->setActionPressed(actionPressed);
    _settings->setPlayerActionsPressed(playerActions);
}
