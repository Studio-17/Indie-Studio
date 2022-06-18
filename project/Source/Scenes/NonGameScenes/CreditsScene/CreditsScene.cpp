/*
** EPITECH PROJECT, 2022
** project
** File description:
** CreditsScene
*/

#include <functional>

#include "tools.hpp"
#include "CreditsScene.hpp"

Scene::CreditsScene::CreditsScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax) : AScene(settings),
    _parallax(parallax)
{
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::CreditsScene::back, this)};

    _nextScene = Scene::Scenes::START_GAME;
    _buttons = loadObjects<Object::Button>("Conf/Scenes/CreditsScene/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/CreditsScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/CreditsScene/text.json");
}

Scene::CreditsScene::~CreditsScene()
{
}

Scene::Scenes Scene::CreditsScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    _nextScene = Scene::Scenes::CREDITS;
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

void Scene::CreditsScene::draw()
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

void Scene::CreditsScene::back()
{
    _nextScene = Scene::Scenes::SETTINGS;
}
