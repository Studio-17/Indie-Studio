/*
** EPITECH PROJECT, 2022
** project
** File description:
** SettingsScene
*/

#include "Objects/3DObject/MapObject/Map/Map.hpp"

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

void Scene::SettingsScene::mainMenuScene(void)
{
    _nextScene = Scene::Scenes::MAIN_MENU;
}

Scene::SettingsScene::SettingsScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    _buttons.emplace(Scene::BUTTONSNAME::MAIN_MENU, std::make_unique<Object::Button>("Save/button.png", 3, std::bind(&Scene::SettingsScene::mainMenuScene, this),"Save/assets_sound_Click.ogg", Position(700, 800, 0)));
    _nextScene = Scene::Scenes::SETTINGS;
}

Scene::SettingsScene::~SettingsScene()
{
}

void Scene::SettingsScene::fadeBlack()
{

}

Scene::Scenes Scene::SettingsScene::handelEvent()
{
    _nextScene = Scene::Scenes::SETTINGS;
    for (auto &[type, button] : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::SettingsScene::draw()
{
    Object::Map map;
    map.generate("Ressources/Maps/Basics/random.map", 11, 11);
    map.process("Ressources/Maps/Basics/random.map");

    _settings->getCamera()->startMode3D();

        DrawLine3D((Vector3){-100, 0, 0}, (Vector3){100, 0, 0}, GREEN);     // X
        DrawLine3D((Vector3){0, -100, 0}, (Vector3){0, 100, 0}, RED);       // Y
        DrawLine3D((Vector3){0, 0, -100}, (Vector3){0, 0, 100}, DARKBLUE);  // Z

        map.draw();

    _settings->getCamera()->endMode3D();

    for (auto &[type, button] : _buttons)
        button->draw();
}
