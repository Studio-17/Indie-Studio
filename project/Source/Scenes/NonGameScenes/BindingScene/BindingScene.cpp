/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** BindingScene
*/

#include <functional>
#include <fstream>

#include "tools.hpp"
#include "BindingScene.hpp"

Scene::BindingScene::BindingScene(std::shared_ptr<Settings> settings, Keyboard &keyboard, std::map<Action, int> const &actionPressed, std::vector<std::map<PlayerAction, int>> &playerAction, std::vector<std::pair<PlayerAction, int>> const &gamepadPlayerActions) :
    AScene(settings), _keyboard(keyboard), _actionPressed(actionPressed), _playerAction(playerAction), _gamepadPlayerActions(gamepadPlayerActions), _buttonIndex(0)
{
    _nextScene = Scenes::BINDING_MENU;
    _images = loadObjects<Object::Image>("Conf/Scenes/BindingScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/BindingScene/text.json");
    _buttons = loadObjects<Object::Button>("Conf/Scenes/BindingScene/button.json");
    _buttons.at(0)->setCallBack(std::bind(&Scene::BindingScene::back, this));
    for (std::size_t player = 0; player != 4; player++)
        for (std::size_t touch = 1; touch != 6; touch++) {
            std::cout << "player" << player * 5 + touch << std::endl;
            _buttons.at((player * 5) + touch)->setText(setActionToString(playerAction.at(player).at(static_cast<PlayerAction>(touch - 1))));
            _buttons.at((player * 5) + touch)->setCallBack(std::bind(&Scene::BindingScene::bindKey, this));
        }
    _parallax = loadObjects<Object::Image>("Conf/Scenes/parallax.json");
    _popUp = loadObjects<Object::Image>("Conf/Scenes/BindingScene/pop_up.json");
    _popUpText = loadObjects<Object::Text>("Conf/Scenes/BindingScene/pop_up_text.json");
    _popUpButton = loadObjects<Object::Button>("Conf/Scenes/BindingScene/pop_up_button.json");
    _popUpButton.at(0)->setCallBack(std::bind(&Scene::BindingScene::cancelBind, this));
    for (auto &popUp : _popUp)
        popUp->disable();
    for (auto &popUp : _popUpText)
        popUp->disable();
    for (auto &popUp : _popUpButton) {
        popUp->disable();
        popUp->disableClick();
    }
}

Scene::BindingScene::~BindingScene()
{
}

Scene::Scenes Scene::BindingScene::handleEvent()
{
    Vector2 mousePos = GetMousePosition();
    std::float_t speed = 0.0;
    int index = 0;

    _nextScene = Scenes::BINDING_MENU;
    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }
    if (_popUpButton.at(0)->isEnable()) {
        int newKey = _keyboard.getPressedKeycode();
        if (newKey) {
            cancelBind();
            _playerAction.at((_buttonOpened - 1) / 5).at(static_cast<PlayerAction>((_buttonOpened - 1) % 5)) = newKey;
            _buttons.at(_buttonOpened)->setText(setActionToString(newKey));
        }
    }
    _buttonIndex = 0;
    for (auto &button : _buttons) {
        button->checkHover(mousePos);
        _buttonIndex++;
    }
    for (auto &button : _popUpButton)
        button->checkHover(mousePos);
    return _nextScene;
}

void Scene::BindingScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &button : _buttons)
        button->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &popUp : _popUp)
        popUp->draw();
    for (auto &popUp : _popUpText)
        popUp->draw();
    for (auto &popUp : _popUpButton)
        popUp->draw();
}

void Scene::BindingScene::save()
{
    std::ofstream fileToWrite("Conf/Settings/keys.json");
    std::vector<std::string> playerName {"playerOne", "playerTwo", "playerThree", "playerFour"};
    std::map<Action, std::string> actionName {{Action::Left, "left"}, {Action::Right, "right"}, {Action::Up, "up"}, {Action::Down, "down"}, {Action::Next, "next"}, {Action::Previous, "previous"}};
    std::map<PlayerAction, std::string> playerActionName {{PlayerAction::MoveLeft, "moveLeft"}, {PlayerAction::MoveRight, "moveRight"}, {PlayerAction::MoveUp, "moveUp"}, {PlayerAction::MoveDown, "moveDown"}, {PlayerAction::Drop, "keyboardDrop"}};
    nlohmann::json saveData;
    nlohmann::json keyData;
    std::size_t index = 0;

    if (!fileToWrite.is_open())
        throw Error::FileError("File Conf/Settings/keys.json failed to open");
    for (auto &[action, key] : _actionPressed )
        keyData[actionName.at(action)] = key;
    saveData["basicKeyboard"] = keyData;
    for (auto &player : _playerAction) {
        keyData.clear();
        for (auto &[action, key] : player) {
            keyData[playerActionName.at(action)] = key;
        }
        keyData["gamepadDrop"] = _gamepadPlayerActions.at(index).second;
        saveData[playerName.at(index)] = keyData;
        index++;
    }
    fileToWrite << std::setw(4) << saveData << std::endl;
}

void Scene::BindingScene::back()
{
    save();
    _nextScene = Scenes::SETTINGS;
}

void Scene::BindingScene::bindKey()
{
    for (auto &button : _buttons)
        button->disableClick();
    for (auto &popUp : _popUp)
        popUp->enable();
    for (auto &popUp : _popUpText)
        popUp->enable();
    for (auto &popUp : _popUpButton) {
        popUp->enable();
        popUp->enableClick();
    }
    _buttonOpened = _buttonIndex;
}

void Scene::BindingScene::cancelBind()
{
    for (auto &popUp : _popUp)
        popUp->disable();
    for (auto &popUp : _popUpText)
        popUp->disable();
    for (auto &popUp : _popUpButton) {
        popUp->disable();
        popUp->disableClick();
    }
    for (auto &button : _buttons)
        button->enableClick();
}
