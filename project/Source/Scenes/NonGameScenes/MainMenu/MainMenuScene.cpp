/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#include "MainMenuScene.hpp"

Scene::MainMenuScene::MainMenuScene() :
 _isRunning(true)
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

void Scene::MainMenuScene::handelEvent()
{

}

void Scene::MainMenuScene::draw()
{
    for (auto &iterator : _objects)
        iterator->draw();
}
