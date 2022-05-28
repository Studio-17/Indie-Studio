/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#include <functional>

#include "tools.hpp"
#include "MainMenuScene.hpp"

#include "FileError.hpp"


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
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::MainMenuScene::newGameScene, this), std::bind(&Scene::MainMenuScene::settingsScene, this), std::bind(&Scene::MainMenuScene::exitScene, this)};

    _objects = loadGenericObjects("Conf/Scenes/MainMenu/object.json");
    _buttons = loadObjects<Object::Button>("Conf/Scenes/MainMenu/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _nextScene = Scene::Scenes::MAIN_MENU;
}

Scene::MainMenuScene::~MainMenuScene()
{
}

void Scene::MainMenuScene::fadeBlack()
{

}

Scene::Scenes Scene::MainMenuScene::handelEvent()
{
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::MainMenuScene::draw()
{
    for (auto &object : _objects)
        object->draw();
    for (auto &button : _buttons)
        button->draw();
}
