/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#include "MainMenuScene.hpp"
#include <functional>

#include <iostream>
static void testFunction(void)
{
    std::cout << "in test function" << std::endl;
}

Scene::MainMenuScene::MainMenuScene(std::shared_ptr<Settings> settings) : AScene(settings),
 _isRunning(true), _scenes(Scene::Scenes::MAIN_MENU)
{
    _buttons.emplace(Scene::BUTTONSNAME::NEWGAME, std::make_unique<Object::Button>("Save/button.png", 3, "Save/assets_sound_Click.ogg", Position(700, 300, 0)));
    _buttons.emplace(Scene::BUTTONSNAME::EXIT, std::make_unique<Object::Button>("Save/button.png", 3, "Save/assets_sound_Click.ogg", Position(700, 500, 0)));
    _buttons.emplace(Scene::BUTTONSNAME::SETTINGS, std::make_unique<Object::Button>("Save/button.png", 3, "Save/assets_sound_Click.ogg", Position(700, 800, 0)));

    // MUSIC HANDLING
    // _mainMusic = std::make_unique<MyMusic>("Save/music.mp3");
    // _mainMusic->play();
    // _mainMusic->setVolume(_settings->getAudio()->getAudioVolume());
}

Scene::MainMenuScene::~MainMenuScene()
{
    // _mainMusic->stop();
}

Scene::Scenes Scene::MainMenuScene::run()
{
    while (_isRunning) {
        handelEvent();
        draw();
    }
    return Scene::Scenes::MAIN_MENU;
}

void Scene::MainMenuScene::fadeBlack()
{

}

Scene::Scenes Scene::MainMenuScene::handelEvent()
{
    for (auto &[type, button] : _buttons)
        button->checkHover(GetMousePosition());
    return Scene::Scenes::MAIN_MENU;
}

void Scene::MainMenuScene::draw()
{
    for (auto &[type, button] : _buttons)
        button->draw();
}
