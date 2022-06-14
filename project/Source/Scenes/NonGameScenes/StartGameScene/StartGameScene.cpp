/*
** EPITECH PROJECT, 2022
** project
** File description:
** StartGameScene
*/

#include <functional>

#include "tools.hpp"
#include "StartGameScene.hpp"

Scene::StartGameScene::StartGameScene(std::shared_ptr<Settings> settings) : AScene(settings),
    _buttonTexture("Ressources/buttons/button2.png")
{
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::StartGameScene::newGameScene, this), std::bind(&Scene::StartGameScene::loadSaveScene, this), std::bind(&Scene::StartGameScene::backScene, this)};

    _nextScene = Scene::Scenes::START_GAME;
    _buttons = loadObjects<Object::Button>("Conf/Scenes/StartGameScene/button.json", _buttonTexture);
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/StartGameScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/StartGameScene/text.json");
    _parallax = loadObjects<Object::Image>("Conf/Scenes/parallax.json");
}

Scene::StartGameScene::~StartGameScene()
{
    _buttonTexture.unload();
}

Scene::Scenes Scene::StartGameScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    _nextScene = Scene::Scenes::START_GAME;
    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::StartGameScene::draw()
{
    for (auto &parallax: _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}

void Scene::StartGameScene::newGameScene()
{
    _nextScene = Scene::Scenes::OPTION_GAME;
}

void Scene::StartGameScene::loadSaveScene()
{
    _nextScene = Scene::Scenes::OPTION_GAME;
}

void Scene::StartGameScene::backScene()
{
    _nextScene = Scene::Scenes::MAIN_MENU;
}
