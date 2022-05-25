/*
** EPITECH PROJECT, 2022
** project
** File description:
** SettingsScene
*/

#include "SettingsScene.hpp"

void Scene::SettingsScene::exitScene(void)
{
    _nextScene = Scene::Scenes::QUIT;
}

void Scene::SettingsScene::settingsScene(void)
{
    _nextScene = Scene::Scenes::SETTINGS;
}

void Scene::SettingsScene::newGameScene(void)
{
    _nextScene = Scene::Scenes::GAME;
}

Scene::SettingsScene::SettingsScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    // _buttons.emplace(Scene::BUTTONSNAME::NEWGAME, std::make_unique<Object::Button>("Save/button.png", 3, std::bind(&Scene::SettingsScene::newGameScene, this), "Save/assets_sound_Click.ogg", Position(700, 300, 0)));
    // _buttons.emplace(Scene::BUTTONSNAME::EXIT, std::make_unique<Object::Button>("Save/button.png", 3, std::bind(&Scene::SettingsScene::exitScene, this),"Save/assets_sound_Click.ogg", Position(700, 500, 0)));
    _buttons.emplace(Scene::BUTTONSNAME::SETTINGS, std::make_unique<Object::Button>("Save/button.png", 3, std::bind(&Scene::SettingsScene::settingsScene, this),"Save/assets_sound_Click.ogg", Position(700, 800, 0)));
    _nextScene = Scene::Scenes::SETTINGS;

    // MUSIC HANDLING
    // _mainMusic = std::make_unique<MyMusic>("Save/music.mp3");
    // _mainMusic->play();
    // _mainMusic->setVolume(_settings->getAudio()->getAudioVolume());
}

Scene::SettingsScene::~SettingsScene()
{
}

void Scene::SettingsScene::fadeBlack()
{

}

Scene::Scenes Scene::SettingsScene::handelEvent()
{
    for (auto &[type, button] : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::SettingsScene::draw()
{
    for (auto &[type, button] : _buttons)
        button->draw();
}
