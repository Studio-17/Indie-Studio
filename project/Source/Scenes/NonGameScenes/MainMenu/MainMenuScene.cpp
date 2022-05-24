/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#include "Button.hpp"
#include "MainMenuScene.hpp"

Scene::MainMenuScene::MainMenuScene(std::shared_ptr<Settings> settings) : AScene(settings),
 _isRunning(true), _button("../Save/button.png", 3, Position(400, 300, 0))
{
    // _button = 
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

void Scene::MainMenuScene::handelEvent()
{

}

#include <raylib.h>
#include <iostream>
void Scene::MainMenuScene::draw()
{
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    // for (auto &iterator : _objects) {
        // std::cout << "in the row" << std::endl;
    // }
    _button.checkHover(GetMousePosition());
        _button.draw();
}
