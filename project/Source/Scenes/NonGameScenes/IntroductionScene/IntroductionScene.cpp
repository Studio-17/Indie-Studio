/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** IntroductionScene
*/

#include "tools.hpp"
#include "IntroductionScene.hpp"

Scene::IntroductionScene::IntroductionScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax, Keyboard &keyboard) : AScene(settings), _keyboard(keyboard), _parallax(parallax)
{
    _nextScene = Scene::Scenes::INTRODUCTION;
    _texts = loadObjects<Object::Text>("Conf/Scenes/IntroductionScene/text.json");
    _images = loadObjects<Object::Image>("Conf/Scenes/IntroductionScene/image.json");
    _shouldPrintText = true;
    _clock.start();
}

Scene::IntroductionScene::~IntroductionScene()
{
}

Scene::Scenes Scene::IntroductionScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    BlinkText();
    _nextScene = Scene::Scenes::INTRODUCTION;
    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }
    handleKey();
    return _nextScene;
}

void Scene::IntroductionScene::handleKey()
{
    int newKey = _keyboard.getPressedKeycode();

    if (newKey)
        _nextScene = Scene::Scenes::MAIN_MENU;
}

void Scene::IntroductionScene::BlinkText()
{
    if (_clock.getElapsedTime() > 500) {
        _shouldPrintText = !_shouldPrintText;
        _clock.restart();
    }
}

void Scene::IntroductionScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    if (_shouldPrintText)
        _texts.at(0)->draw();
}
