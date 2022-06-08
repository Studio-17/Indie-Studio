/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#include <functional>

#include "tools.hpp"
#include "FileError.hpp"
#include "Texture.hpp"

#include "MainMenuScene.hpp"

void Scene::MainMenuScene::exitScene(void)
{
    _nextScene = Scene::Scenes::QUIT;
}

void Scene::MainMenuScene::gameScene(void)
{
    _nextScene = Scene::Scenes::SAVE;
}

void Scene::MainMenuScene::newGameScene(void)
{
    _nextScene = Scene::Scenes::OPTION_GAME;
}

Scene::MainMenuScene::MainMenuScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::MainMenuScene::newGameScene, this), std::bind(&Scene::MainMenuScene::gameScene, this), std::bind(&Scene::MainMenuScene::exitScene, this)};

    Object::Render::MyTexture buttonTexture("Ressources/buttons/button2.png");
    _buttons = loadObjects<Object::Button>("Conf/Scenes/MainMenu/button.json", true);
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/MainMenu/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/MainMenu/text.json");

    _nextScene = Scene::Scenes::MAIN_MENU;
    _parallax = loadObjects<Object::Image>("Conf/Scenes/parallax.json");
}

Scene::MainMenuScene::~MainMenuScene()
{
}

void Scene::MainMenuScene::fadeBlack()
{
}

Scene::Scenes Scene::MainMenuScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    _nextScene = Scene::Scenes::MAIN_MENU;
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

void Scene::MainMenuScene::draw()
{
    // std::float_t speed = 0.0;

    // for (std::int8_t i = 0; i < 10; i++) {
    //     if (i % 2 == 0)
    //         speed += 0.1;

    //     _images.at(i)->setPosition(_images.at(i)->getPosition().getX() - speed, _images.at(i)->getPosition().getY());

    //     if (_images.at(i)->getPosition().getX() <= -1930)
    //         _images.at(i)->setPosition(1928, _images.at(i)->getPosition().getY());
    // }

    for (auto &parallax: _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}
