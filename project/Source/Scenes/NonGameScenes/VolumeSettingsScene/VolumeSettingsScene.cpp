/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** VolumeSettingsScene
*/

#include "tools.hpp"
#include "VolumeSettingsScene.hpp"

Scene::VolumeSettingsScene::VolumeSettingsScene(std::shared_ptr<Settings> settings, std::vector<std::function<void(void)>> callBacks) : AScene(settings)
{
    std::vector<std::function<void(void)>> callBack = {
        callBacks.at(0),
        std::bind(&Scene::VolumeSettingsScene::downgradeSound, this),
        std::bind(&Scene::VolumeSettingsScene::upgradeSound, this),
        std::bind(&Scene::VolumeSettingsScene::downgradeMusic, this),
        std::bind(&Scene::VolumeSettingsScene::upgradeMusic, this)
    };

    _buttons = loadObjects<Object::Button>("Conf/Scenes/VolumeSettingsScene/button.json");
    _images = loadObjects<Object::Image>("Conf/Scenes/VolumeSettingsScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/VolumeSettingsScene/text.json");

    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBack.at(index));
    }
    _texts.at(1)->setText(std::to_string(static_cast<int>(_settings->getAudio()->getSoundVolume() * 100)) + "%");
    _texts.at(3)->setText(std::to_string(static_cast<int>(_settings->getAudio()->getMusicVolume() * 100)) + "%");
}

Scene::VolumeSettingsScene::~VolumeSettingsScene()
{
}

Scene::Scenes Scene::VolumeSettingsScene::handleEvent()
{
    _nextScene = Scene::Scenes::SETTINGS;
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::VolumeSettingsScene::draw()
{
    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}

void Scene::VolumeSettingsScene::downgradeSound()
{
    float soundVolume = _settings->getAudio()->getSoundVolume();

    if (soundVolume > 0.01) {
        soundVolume -= 0.1;
        _settings->applySoundVolume(soundVolume);
        _texts.at(1)->setText(std::to_string(static_cast<int>(soundVolume * 100)) + "%");
    }
}

void Scene::VolumeSettingsScene::upgradeSound()
{
    float soundVolume = _settings->getAudio()->getSoundVolume();

    if (soundVolume < 1) {
        soundVolume += 0.1;
        _settings->applySoundVolume(soundVolume);
        _texts.at(1)->setText(std::to_string(static_cast<int>(soundVolume * 100)) + "%");
    }
}

void Scene::VolumeSettingsScene::downgradeMusic()
{
    float musicVolume = _settings->getAudio()->getMusicVolume();

    std::cout << musicVolume << std::endl;

    if (musicVolume > 0.01) {
        musicVolume -= 0.1;
        _settings->applyMusicVolume(musicVolume);
        _texts.at(3)->setText(std::to_string(static_cast<int>(musicVolume * 100)) + "%");
    }
}

void Scene::VolumeSettingsScene::upgradeMusic()
{
    float musicVolume = _settings->getAudio()->getMusicVolume();

    if (musicVolume < 1) {
        musicVolume += 0.1;
        _settings->applyMusicVolume(musicVolume);
        _texts.at(3)->setText(std::to_string(static_cast<int>(musicVolume * 100)) + "%");
    }
}