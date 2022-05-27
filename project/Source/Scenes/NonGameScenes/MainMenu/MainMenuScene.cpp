/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#include "MainMenuScene.hpp"
#include <functional>

#include <iostream>

void Scene::MainMenuScene::exitScene(void)
{
    _nextScene = Scene::Scenes::QUIT;
}

void Scene::MainMenuScene::settingsScene(void)
{
    _nextScene = Scene::Scenes::SETTINGS;
}

void Scene::MainMenuScene::newGameScene(void)
{
    _nextScene = Scene::Scenes::GAME;
}

Scene::MainMenuScene::MainMenuScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    // BUTTON HANDLING
    _buttons.emplace(Scene::BUTTONSNAME::NEWGAME, std::make_unique<Object::Button>("Ressources/buttons/button.png", 3, std::bind(&Scene::MainMenuScene::newGameScene, this), "Ressources/buttons/click_sound.ogg", Position(700, 300, 0)));
    _buttons.emplace(Scene::BUTTONSNAME::EXIT, std::make_unique<Object::Button>("Ressources/buttons/button.png", 3, std::bind(&Scene::MainMenuScene::exitScene, this),"Ressources/buttons/click_sound.ogg", Position(700, 500, 0)));
    _buttons.emplace(Scene::BUTTONSNAME::SETTINGS, std::make_unique<Object::Button>("Ressources/buttons/button.png", 3, std::bind(&Scene::MainMenuScene::settingsScene, this),"Ressources/buttons/click_sound.ogg", Position(700, 800, 0)));
    _nextScene = Scene::Scenes::MAIN_MENU;

    // MUSIC HANDLING
    _mainMusic = std::make_unique<MyMusic>("Ressources/musics/music_title.ogg");
    _mainMusic->setVolume(_settings->getAudio()->getAudioVolume());
    _mainMusic->play();

    // BACKGROUND HANDLING
    _imageBackground = std::make_unique<Object::Image>("Ressources/sprites/background.png");
    _imageBackground->setScale(1.5f);
    _imageBackground->setPosition(200, 100);


}

Scene::MainMenuScene::~MainMenuScene()
{
    _mainMusic->stop();
}

void Scene::MainMenuScene::fadeBlack()
{

}

Scene::Scenes Scene::MainMenuScene::handelEvent()
{
    _nextScene = Scene::Scenes::MAIN_MENU;
    for (auto &[type, button] : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::MainMenuScene::draw()
{
    _imageBackground->draw();
    for (auto &[type, button] : _buttons)
        button->draw();
}
