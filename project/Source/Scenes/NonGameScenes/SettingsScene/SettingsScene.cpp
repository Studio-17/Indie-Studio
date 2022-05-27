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
    _gameMap = std::make_unique<Object::Map>();
    _gameMap->generate("Ressources/Maps/Basics/random.map", 11, 11);
    _gameMap->process("Ressources/Maps/Basics/random.map");
    _playerOne = std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/Assets/models/players/player.iqm", "Ressources/Assets/models/players/blue.png"), "Ressources/Assets/models/players/player.iqm", 1, Position(0, 0, 0));
    _playerTwo = std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/Assets/models/players/player.iqm", "Ressources/Assets/models/players/red.png"), "Ressources/Assets/models/players/player.iqm", 1, Position(0, 0, 0));
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
    if (IsKeyDown(KEY_UP))
        _playerOne->moveUp();
    if (IsKeyDown(KEY_DOWN))
        _playerOne->moveDown();
    if (IsKeyDown(KEY_LEFT))
        _playerOne->moveLeft();
    if (IsKeyDown(KEY_RIGHT))
        _playerOne->moveRight();
    return _nextScene;
}

void Scene::SettingsScene::draw()
{
    _settings->getCamera()->startMode3D();

        DrawLine3D((Vector3){-100, 0, 0}, (Vector3){100, 0, 0}, GREEN);     // X
        DrawLine3D((Vector3){0, -100, 0}, (Vector3){0, 100, 0}, RED);       // Y
        DrawLine3D((Vector3){0, 0, -100}, (Vector3){0, 0, 100}, DARKBLUE);  // Z

        _gameMap->draw();
        _playerOne->setScale(8.0f);
        _playerOne->draw();

        _playerTwo->setScale(8.0f);
        _playerTwo->setPosition(10, 0, 0);
        _playerTwo->draw();

    _settings->getCamera()->endMode3D();

    for (auto &[type, button] : _buttons)
        button->draw();
}
