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

void Scene::SettingsScene::mainMenuScene(void)
{
    _nextScene = Scene::Scenes::MAIN_MENU;
}

Scene::SettingsScene::SettingsScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    _buttons.emplace_back(std::make_unique<Object::Button>("Ressources/buttons/button.png", 3, std::bind(&Scene::SettingsScene::mainMenuScene, this),"Ressources/buttons/click_sound.ogg", Position(700, 800, 0)));
    _nextScene = Scene::Scenes::SETTINGS;
    _gameMap = std::make_unique<Object::Map>();
    _mapFile = "Save/Maps/random.map";
    _margin = 1.9f;
    _playerSpeed = 0.15f;
    _gameMap->generate(_mapFile, 11, 11);
    _gameMap->process(_mapFile);
    _playerOne = std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/models/player/player.iqm", "Ressources/models/player/blue.png"), "Ressources/models/player/player.iqm", 1, Position(100, 0, 10));
    // _playerTwo = std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/models/player/player.iqm", "Ressources/models/player/red.png"), "Ressources/models/player/player.iqm", 1, Position(0, 0, 0));

    std::cout << "camera target: " << _gameMap->getDimensions() << std::endl;

    _settings->getCamera()->setTarget((Position){_gameMap->getDimensions()});
    _settings->getCamera()->setPosition(_gameMap->getDimensions());
}

Scene::SettingsScene::~SettingsScene()
{
}

void Scene::SettingsScene::fadeBlack()
{

}

bool Scene::SettingsScene::isColliding(Position margin)
{
    float tileSpace = 10 - 2;
    Position playerPos = _playerOne->getPosition();

    for (auto &object : _gameMap->getMapObjects()) {
        Position block = object.getPosition();

        if (object.getPosition().getY() == 0 &&
        ((playerPos.getX() + margin.getX() >= (block.getX() - tileSpace) && playerPos.getX() + margin.getX() <= (block.getX() + tileSpace)) &&
        (playerPos.getZ() + margin.getZ() >= (block.getZ() - tileSpace) && playerPos.getZ() + margin.getZ() <= (block.getZ() + tileSpace))))
            return true;
    }
    return false;
}

int Scene::SettingsScene::getMovingKeys()
{
    if (IsKeyDown(KEY_UP))
        return KEY_UP;
    if (IsKeyDown(KEY_DOWN))
        return KEY_DOWN;
    if (IsKeyDown(KEY_LEFT))
        return KEY_LEFT;
    if (IsKeyDown(KEY_RIGHT))
        return KEY_RIGHT;
    if (IsKeyDown(KEY_SPACE))
        return KEY_SPACE;
    return 0;
}

Scene::Scenes Scene::SettingsScene::handelEvent()
{
    int key = getMovingKeys();
    Position playerPos = _playerOne->getPosition();

    _nextScene = Scene::Scenes::SETTINGS;
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    switch (key) {
        case KEY_UP:
            if (!isColliding((Position){0, 0, -_margin}))
                _playerOne->move((Position){ playerPos.getX(), playerPos.getY(), playerPos.getZ() - _playerSpeed}, (Position){0, 90, 0});
            break;
        case KEY_DOWN:
            if (!isColliding((Position){0, 0, _margin}))
                _playerOne->move((Position){ playerPos.getX(), playerPos.getY(), playerPos.getZ() + _playerSpeed}, (Position){0, -90, 0});
            break;
        case KEY_LEFT:
            if (!isColliding((Position){-_margin, 0, 0}))
                _playerOne->move((Position){ playerPos.getX() - _playerSpeed, playerPos.getY(), playerPos.getZ()}, (Position){0, 0, 0});
            break;
        case KEY_RIGHT:
            if (!isColliding((Position){_margin, 0, 0}))
                _playerOne->move((Position){ playerPos.getX() + _playerSpeed, playerPos.getY(), playerPos.getZ()}, (Position){0, 180, 0});
            break;
        case KEY_SPACE:
            _playerOne->dropBomb();
            break;
        default:
            _playerOne->resetAnimation();
    }
    return _nextScene;
}

void Scene::SettingsScene::draw()
{
    _settings->getCamera()->startMode3D();

        DrawLine3D((Vector3){-1000, 0, 0}, (Vector3){1000, 0, 0}, GREEN);     // X
        DrawLine3D((Vector3){0, -1000, 0}, (Vector3){0, 1000, 0}, RED);       // Y
        DrawLine3D((Vector3){0, 0, -1000}, (Vector3){0, 0, 1000}, DARKBLUE);  // Z

        _gameMap->draw();
        _playerOne->setScale(5.0f);
        _playerOne->draw();

    _settings->getCamera()->endMode3D();

    for (auto &button : _buttons)
        button->draw();
}
