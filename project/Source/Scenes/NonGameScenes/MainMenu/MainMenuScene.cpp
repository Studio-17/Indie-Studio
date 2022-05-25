/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#include "MainMenuScene.hpp"
#include <functional>

#include <iostream>
void Scene::MainMenuScene::testFunction()
{
    std::cout << "in test function" << std::endl;
}

Scene::MainMenuScene::MainMenuScene(std::shared_ptr<Settings> settings) : AScene(settings),
 _isRunning(true), _scenes(Scene::Scenes::MAIN_MENU),_button("Save/button.png", 3, "Save/assets_sound_Click.ogg", Position(700, 300, 0)),
 _button2("Save/button.png", 3, "Save/assets_sound_Click.ogg", Position(700, 500, 0)),
 _button3("Save/button.png", 3, "Save/assets_sound_Click.ogg", Position(700, 800, 0))
{
}

Scene::MainMenuScene::~MainMenuScene()
{
}

Scene::Scenes Scene::MainMenuScene::run()
{
    while (_isRunning) {
        handelEvent();
        draw();
    }
}

void Scene::MainMenuScene::fadeBlack()
{

}

Scene::Scenes Scene::MainMenuScene::handelEvent()
{
    _button.checkHover(GetMousePosition());
    _button2.checkHover(GetMousePosition());
    _button3.checkHover(GetMousePosition());

    // for (auto it : _buttons) {
        // it.second.checkHover(GetMousePosition());
    // }

    return Scene::Scenes::MAIN_MENU;
}

#include <raylib.h>
#include <iostream>
void Scene::MainMenuScene::draw()
{
    // for (auto &iterator : _objects) {
        // std::cout << "in the row" << std::endl;
    // }
    _button.draw();
    _button2.draw();
    _button3.draw();
    // for (auto it : _buttons) {
        // it.second.draw();
    // }
}
