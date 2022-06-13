/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** BindingScene
*/

#include <functional>

#include "tools.hpp"
#include "BindingScene.hpp"

Scene::BindingScene::BindingScene(std::shared_ptr<Settings> settings, Keyboard &keyboard, std::vector<std::map<PlayerAction, int>> const &playerAction, std::function<void(int, int, int)> bindingFunction) : 
    AScene(settings), _keyboard(keyboard), _playerAction(playerAction), _bindingFunction(bindingFunction), _buttonIndex(0)
{
    _nextScene = Scenes::SAVE;
    _parallax = loadObjects<Object::Image>("Conf/Scenes/parallax.json");
    _buttons = loadObjects<Object::Button>("Conf/Scenes/BindingScene/button.json");
    _buttons.at(0)->setCallBack(std::bind(&Scene::BindingScene::exitScene, this));
    for (std::size_t index = 1; index !=_buttons.size(); index++)
        _buttons.at(index)->setCallBack(std::bind(&Scene::BindingScene::newGameScene, this));
    _images = loadObjects<Object::Image>("Conf/Scenes/BindingScene/image.json");
    _images.at(0)->disable();
    _texts = loadObjects<Object::Text>("Conf/Scenes/BindingScene/text.json");
    for (auto &text: _texts)
        text->disable();
    _texts.at(0)->enable();
}

Scene::BindingScene::~BindingScene()
{
}

void Scene::BindingScene::fadeBlack()
{

}

Scene::Scenes Scene::BindingScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    _nextScene = Scenes::SAVE;
    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }
    if (_images.at(0)->isEnable()) {
        int newKey = _keyboard.getPressedKeycode();
        if (newKey) {
            _images.at(0)->disable();
            _texts.at(_buttonOpened)->disable();
            _bindingFunction((_buttonOpened - 1) / 5, (_buttonOpened - 1) % 5, newKey);
            _playerAction.at((_buttonOpened - 1) / 5).at(static_cast<PlayerAction>((_buttonOpened - 1) % 5)) = newKey;
        }
    }

    _buttonIndex = 0;
    for (auto &button : _buttons) {
        button->checkHover(GetMousePosition());
        _buttonIndex++;
    }
    return _nextScene;
}

void Scene::BindingScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &button: _buttons)
        button->draw();
    for (auto &image: _images)
        image->draw();
    for (auto &text: _texts)
        text->draw();
}

void Scene::BindingScene::exitScene()
{
    _nextScene = Scenes::MAIN_MENU;
}

void Scene::BindingScene::settingsScene()
{

}

void Scene::BindingScene::newGameScene()
{
    _images.at(0)->enable();
    _texts.at(_buttonIndex)->enable();
    _buttonOpened = _buttonIndex;
}

