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
    _nextScene = Scene::Scenes::OPTION_GAME;
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
    _parallax = loadObjects<Object::Image>("Conf/Scenes/parallax.json");

    _nextScene = Scene::Scenes::GAME;
}

Scene::SelectGameMenuScene::~SelectGameMenuScene()
{
}

void Scene::SelectGameMenuScene::fadeBlack()
{
}

Scene::Scenes Scene::SelectGameMenuScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }

    _nextScene = Scene::Scenes::GAME;

    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::SelectGameMenuScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}
