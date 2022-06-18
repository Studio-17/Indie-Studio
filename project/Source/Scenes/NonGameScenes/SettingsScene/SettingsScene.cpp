/*
** EPITECH PROJECT, 2022
** project
** File description:
** SettingsScene
*/

#include <functional>

#include "tools.hpp"
#include "SettingsScene.hpp"

Scene::SettingsScene::SettingsScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::SettingsScene::credits, this), std::bind(&Scene::SettingsScene::help, this), std::bind(&Scene::SettingsScene::volume, this),
        std::bind(&Scene::SettingsScene::framerate, this), std::bind(&Scene::SettingsScene::controls, this), std::bind(&Scene::SettingsScene::back, this), };

    _nextScene = Scene::Scenes::START_GAME;
    _buttons = loadObjects<Object::Button>("Conf/Scenes/SettingsScene/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/SettingsScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/SettingsScene/text.json");
    _parallax = loadObjects<Object::Image>("Conf/Scenes/parallax.json");
    _volumeSettingsScene = std::make_unique<Scene::VolumeSettingsScene>(settings, std::vector<std::function<void(void)>>{std::bind(&Scene::SettingsScene::closePopupVolume, this)});
    _isVolumeSettings = false;
}

Scene::SettingsScene::~SettingsScene()
{
}

Scene::Scenes Scene::SettingsScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    _nextScene = Scene::Scenes::SETTINGS;
    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }
    if (!_isVolumeSettings) {
        for (auto &button : _buttons) {
            if (button->isClickable())
                button->checkHover(GetMousePosition());
        }
    } else {
        _nextScene = _volumeSettingsScene->handleEvent();
    }
    return _nextScene;
}

void Scene::SettingsScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
    if (_isVolumeSettings)
        _volumeSettingsScene->draw();
}

void Scene::SettingsScene::credits()
{
    _nextScene = Scene::Scenes::CREDITS;
}

void Scene::SettingsScene::help()
{
    _nextScene = Scene::Scenes::HELP;
}

void Scene::SettingsScene::volume()
{
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->disableClick();
    }
    _isVolumeSettings = true;
}

void Scene::SettingsScene::framerate()
{

}

void Scene::SettingsScene::controls()
{
    _nextScene = Scene::Scenes::BINDING_MENU;
}

void Scene::SettingsScene::back()
{
    _nextScene = Scene::Scenes::MAIN_MENU;
}

void Scene::SettingsScene::closePopupVolume()
{
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->enableClick();
    }
    _isVolumeSettings = false;
}