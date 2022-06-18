/*
** EPITECH PROJECT, 2022
** project
** File description:
** FramerateScene
*/

#include "tools.hpp"
#include "FramerateScene.hpp"

Scene::FramerateScene::FramerateScene(std::shared_ptr<Settings> settings, std::vector<std::function<void(void)>> callBacks) : AScene(settings)
{
    int audioVolume = 0;
    int soundVolume = 0;
    std::vector<std::function<void(void)>> callBack = {
        callBacks.at(0),
        std::bind(&Scene::FramerateScene::downgradeFramerate, this),
        std::bind(&Scene::FramerateScene::upgradeFramerate, this)
    };

    _buttons = loadObjects<Object::Button>("Conf/Scenes/FramerateScene/button.json");
    _images = loadObjects<Object::Image>("Conf/Scenes/FramerateScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/FramerateScene/text.json");

    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBack.at(index));
    }
    _texts.at(1)->setText(std::to_string(_settings->getFramerate()));
}

Scene::FramerateScene::~FramerateScene()
{
}

Scene::Scenes Scene::FramerateScene::handleEvent()
{
    _nextScene = Scene::Scenes::SETTINGS;
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::FramerateScene::draw()
{
    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}

void Scene::FramerateScene::downgradeFramerate()
{
    int framerate = _settings->getFramerate();

    if (framerate > 10) {
        framerate -= 10;
        _settings->applyFramerate(framerate);
        _texts.at(1)->setText(std::to_string(framerate));
    }
}

void Scene::FramerateScene::upgradeFramerate()
{
    int framerate = _settings->getFramerate();

    if (framerate < 200) {
        framerate += 10;
        _settings->applyFramerate(framerate);
        _texts.at(1)->setText(std::to_string(framerate));
    }
}