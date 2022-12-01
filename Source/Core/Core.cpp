/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Core
*/

#include <raylib.h>

#include "MainMenuScene.hpp"
#include "StartGameScene.hpp"
#include "GameScene.hpp"
#include "SettingsScene.hpp"
#include "OptionGameMenuScene.hpp"
#include "BindingScene.hpp"
#include "SelectPlayerScene.hpp"
#include "EndGameScene.hpp"
#include "SelectMapScene.hpp"
#include "CreditsScene.hpp"
#include "SelectSaveScene.hpp"
#include "IntroductionScene.hpp"
#include "HelpScene.hpp"
#include "InformationScene.hpp"

#include "tools.hpp"
#include "Map.hpp"
#include "Core.hpp"

Core::Core() : _isRunning(true),
    _activeScene(Scene::Scenes::INTRODUCTION),
    _settings(std::make_shared<Settings>(getJsonData("Conf/Settings/settings.json"))),
    _gameSettings(std::make_shared<GameSettings>())
{
    // waitingLoad();
    loadKeyBinding(getJsonData("Conf/Settings/keys.json"));
    _parallax = loadObjects<Object::Image>("Conf/Scenes/parallax.json");
    loadMenuScenes();
    srand(time(NULL));
}

Core::~Core()
{
}

void Core::updateLoadingScreen(std::string const &string)
{
    _settings->getWindow()->startDrawing();
    _settings->getWindow()->clearBackground(DARKPURPLE);
    for (auto &text : _texts)
        text->draw();
    _images.at(2)->setRotation(_images.at(2)->getRotation() + 45.0f);
    for (auto &image : _images)
        image->draw();
    _texts.at(0)->setText("Now Loading" + string);
    _settings->getWindow()->endDrawing();
}

void Core::loadMenuScenes()
{
    _images = loadObjects<Object::Image>("Conf/WaitingScreen/image.json");
    _texts = loadObjects<Object::Text>("Conf/WaitingScreen/text.json");
    updateLoadingScreen(".");
    std::shared_ptr<Scene::GameScene> gameScene = std::make_shared<Scene::GameScene>(_settings, _gameSettings);
    updateLoadingScreen("..");
    std::shared_ptr<Scene::SelectSaveScene> selectSaveScene = std::make_shared<Scene::SelectSaveScene>(_settings, _gameSettings, _parallax, std::bind(&Scene::GameScene::loadFromSave, gameScene, std::placeholders::_1));
    _menuScenes.emplace(Scene::Scenes::SAVE, selectSaveScene);
    updateLoadingScreen("...");
    _menuScenes.emplace(Scene::Scenes::INTRODUCTION, std::make_shared<Scene::IntroductionScene>(_settings, _parallax, _keyboard));
    updateLoadingScreen("..");
    _menuScenes.emplace(Scene::Scenes::MAIN_MENU, std::make_shared<Scene::MainMenuScene>(_settings, _parallax));
    updateLoadingScreen(".");
    _menuScenes.emplace(Scene::Scenes::START_GAME, std::make_shared<Scene::StartGameScene>(_settings, _parallax, std::bind(&Scene::SelectSaveScene::updateSaveFiles, selectSaveScene)));
    updateLoadingScreen("");
    _menuScenes.emplace(Scene::Scenes::SETTINGS, std::make_shared<Scene::SettingsScene>(_settings, _parallax));
    updateLoadingScreen(".");
    _menuScenes.emplace(Scene::Scenes::GAME, gameScene);
    updateLoadingScreen("..");
    _menuScenes.emplace(Scene::Scenes::OPTION_GAME, std::make_shared<Scene::OptionGameMenuScene>(_settings, _gameSettings, _parallax));
    updateLoadingScreen("...");
    _menuScenes.emplace(Scene::Scenes::BINDING_MENU, std::make_shared<Scene::BindingScene>(_settings, _parallax, _keyboard, _actionPressed, _playerActions, _gamepadPlayerActions));
    updateLoadingScreen("..");
    _menuScenes.emplace(Scene::Scenes::SELECT_PLAYER, std::make_shared<Scene::SelectPlayerScene>(_settings, _gameSettings, _parallax, std::bind(&Scene::GameScene::applyGameParams, gameScene)));
    updateLoadingScreen("");
    _menuScenes.emplace(Scene::Scenes::END_GAME, std::make_shared<Scene::EndGameScene>(_settings, _gameSettings, _parallax, std::bind(&Scene::GameScene::applyGameParams, gameScene)));
    updateLoadingScreen(".");
    _menuScenes.emplace(Scene::Scenes::SELECT_MAP, std::make_shared<Scene::SelectMapScene>(_settings, _gameSettings, _parallax));
    updateLoadingScreen("..");
    _menuScenes.emplace(Scene::Scenes::CREDITS, std::make_shared<Scene::CreditsScene>(_settings, _parallax));
    updateLoadingScreen("...");
    _menuScenes.emplace(Scene::Scenes::HELP, std::make_shared<Scene::HelpScene>(_settings, _parallax));
    updateLoadingScreen("..");
    _menuScenes.emplace(Scene::Scenes::INFORMATION, std::make_shared<Scene::InformationScene>(_settings, _parallax));
    updateLoadingScreen(".");
    _settings->getWindow()->endDrawing();
}

void Core::loop()
{
    while (!_settings->getWindow()->windowShouldClose() && _activeScene != Scene::Scenes::QUIT) {
        _settings->getWindow()->startDrawing();
        _settings->getWindow()->clearBackground(DARKGRAY);

        getEvent();
        _activeScene = _menuScenes.at(_activeScene)->handleEvent();
        if (_activeScene == Scene::Scenes::QUIT)
            continue;
        _menuScenes.at(_activeScene)->draw();

        _settings->getWindow()->endDrawing();
    }
}

void Core::getEvent()
{
    std::map<Action, bool> actionPressed = _keyboard.getKeysHasBeenPressed<Action>(_actionPressed);
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
    _actionPressed.emplace(Action::Right, jsonData.at("basicKeyboard").value("right", 262));
    _actionPressed.emplace(Action::Left, jsonData.at("basicKeyboard").value("left", 263));
    _actionPressed.emplace(Action::Up, jsonData.at("basicKeyboard").value("up", 265));
    _actionPressed.emplace(Action::Down, jsonData.at("basicKeyboard").value("down", 264));
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
    _gamepadPlayerMovement = {
        {PlayerAction::MoveLeft, GAMEPAD_AXIS_LEFT_X},
        {PlayerAction::MoveRight, GAMEPAD_AXIS_LEFT_X},
        {PlayerAction::MoveUp, GAMEPAD_AXIS_LEFT_Y},
        {PlayerAction::MoveDown, GAMEPAD_AXIS_LEFT_Y}
    };
}

void Core::waitingLoad()
{
    std::vector<std::unique_ptr<Object::Image>> images = loadObjects<Object::Image>("Conf/WaitingScreen/image.json");
    std::vector<std::unique_ptr<Object::Text>> texts = loadObjects<Object::Text>("Conf/WaitingScreen/text.json");

    _settings->getWindow()->startDrawing();
    _settings->getWindow()->clearBackground(DARKPURPLE);
    for (auto &image : images) {
        image->draw();
    }
    for (auto &text : texts)
        text->draw();
    _settings->getWindow()->endDrawing();
}