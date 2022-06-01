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
    _activeScene(Scene::Scenes::MAIN_MENU),
    _settings(std::make_shared<Settings>(getJsonData("Conf/Settings/settings.json")))
{
    loadKeyBinding(getJsonData("Conf/Settings/keys.json"));
    _gamepadPlayerMovement = {
        {PlayerAction::MoveLeft, GAMEPAD_AXIS_LEFT_X},
        {PlayerAction::MoveRight, GAMEPAD_AXIS_LEFT_X},
        {PlayerAction::MoveUp, GAMEPAD_AXIS_LEFT_Y},
        {PlayerAction::MoveDown, GAMEPAD_AXIS_LEFT_Y}
    };
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

    for (std::size_t index = 0; index != 4; index++) {
        if (_gamepad.isAvailable(index))
            playerActions.emplace_back(_gamepad.getMovement<PlayerAction>(_gamepadPlayerMovement, index, _gamepadPlayerActions.at(index)));
        else
            playerActions.emplace_back(_keyboard.getKeysPressed<PlayerAction>(_playerActions.at(index)));
    }
    _settings->setActionPressed(actionPressed);
    _settings->setPlayerActionsPressed(playerActions);
}

void Core::loadKeyBinding(nlohmann::json const &jsonData)
{
    std::vector<std::string> playerConfName = {"playerOne", "playerTwo", "playerThree", "playerFour"};
    std::map<PlayerAction, int> tmpPLayerAction;

    _actionPressed.emplace(Action::Next, jsonData.at("basicKeyboard").value("next", 1));
    _actionPressed.emplace(Action::Previous, jsonData.at("basicKeyboard").value("previous", 1));
    _actionPressed.emplace(Action::Right, jsonData.at("basicKeyboard").value("right", 1));
    _actionPressed.emplace(Action::Left, jsonData.at("basicKeyboard").value("left", 1));
    _actionPressed.emplace(Action::Up, jsonData.at("basicKeyboard").value("Up", 1));
    _actionPressed.emplace(Action::Down, jsonData.at("basicKeyboard").value("down", 1));
    for (auto &player : playerConfName) {
        tmpPLayerAction.clear();
        tmpPLayerAction.emplace(PlayerAction::MoveLeft, jsonData.at(player).value("moveLeft", 263));
        tmpPLayerAction.emplace(PlayerAction::MoveRight, jsonData.at(player).value("moveRight", 262));
        tmpPLayerAction.emplace(PlayerAction::MoveUp, jsonData.at(player).value("moveUp", 265));
        tmpPLayerAction.emplace(PlayerAction::MoveDown, jsonData.at(player).value("moveDown", 264));
        tmpPLayerAction.emplace(PlayerAction::Drop, jsonData.at(player).value("keyboardDrop", 32));
        _playerActions.emplace_back(tmpPLayerAction);
        _gamepadPlayerActions.emplace_back(PlayerAction::Drop, jsonData.at(player).value("gamepadDrop", 7));
    }
}
