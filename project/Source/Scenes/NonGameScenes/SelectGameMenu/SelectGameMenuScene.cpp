/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectGameMenuScene
*/

#include <functional>

#include "tools.hpp"
#include "SelectGameMenuScene.hpp"

#include "FileError.hpp"

void Scene::SelectGameMenuScene::mainMenuScene()
{
    _nextScene = Scene::Scenes::MAIN_MENU;
}

void Scene::SelectGameMenuScene::loadGameScene()
{
    _nextScene = Scene::Scenes::SAVE;
}

void Scene::SelectGameMenuScene::newGameScene(void)
{
    _nextScene = Scene::Scenes::NEW_GAME;
}

Scene::SelectGameMenuScene::SelectGameMenuScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::SelectGameMenuScene::newGameScene, this), std::bind(&Scene::SelectGameMenuScene::loadGameScene, this), std::bind(&Scene::SelectGameMenuScene::mainMenuScene, this)};

    _buttons = loadObjects<Object::Button>("Conf/Scenes/SelectGameMenu/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/SelectGameMenu/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/SelectGameMenu/text.json");

    _nextScene = Scene::Scenes::GAME;
}

Scene::SelectGameMenuScene::~SelectGameMenuScene()
{
}

void Scene::SelectGameMenuScene::fadeBlack()
{
}

Scene::Scenes Scene::SelectGameMenuScene::handelEvent()
{
    _nextScene = Scene::Scenes::GAME;

    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::SelectGameMenuScene::draw()
{
    std::float_t speed = 0.0;

    for (std::int8_t i = 0; i < 10; i++) {
        if (i % 2 == 0)
            speed += 0.15;

        _images.at(i)->setPosition(_images.at(i)->getPosition().getX() - speed, _images.at(i)->getPosition().getY());

        if (_images.at(i)->getPosition().getX() <= -1930)
            _images.at(i)->setPosition(1928, _images.at(i)->getPosition().getY());
    }

    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}
