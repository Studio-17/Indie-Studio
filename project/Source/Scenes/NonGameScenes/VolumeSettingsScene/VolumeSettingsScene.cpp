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
    int audioVolume = 0;
    int soundVolume = 0;
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
    audioVolume = _settings->getAudio()->getAudioVolume() * 100;
    soundVolume = _settings->getAudio()->getSoundVolume() * 100;
    _texts.at(1)->setText(std::to_string(soundVolume) + "%");
    _texts.at(3)->setText(std::to_string(audioVolume) + "%");
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
    int soundVolume = _settings->getSoundVolume() * 100;

    if (soundVolume > 0) {
        soundVolume -= 10;
        _settings->applySoundVolume((float)soundVolume / 100);
        _texts.at(1)->setText(std::to_string(soundVolume) + "%");
    }
}

void Scene::VolumeSettingsScene::upgradeSound()
{
    int soundVolume = _settings->getSoundVolume() * 100;

    if (soundVolume < 100) {
        soundVolume += 10;
        _settings->applySoundVolume((float)soundVolume / 100);
        _texts.at(1)->setText(std::to_string(soundVolume) + "%");
    }
}

void Scene::VolumeSettingsScene::downgradeMusic()
{
    int musicVolume = _settings->getMusicVolume() * 100;

    if (musicVolume > 0) {
        musicVolume -= 10;
        _settings->applyMusicVolume((float)musicVolume / 100);
        _texts.at(3)->setText(std::to_string(musicVolume) + "%");
    }
}

void Scene::VolumeSettingsScene::upgradeMusic()
{
    int musicVolume = _settings->getMusicVolume() * 100;

    if (musicVolume < 100) {
        musicVolume += 10;
        _settings->applyMusicVolume((float)musicVolume / 100);
        _texts.at(3)->setText(std::to_string(musicVolume) + "%");
    }
}