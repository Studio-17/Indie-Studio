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
    // _gameMap->generate("Save/Maps/random.map", 11, 11);
    _gameMap->process("Save/Maps/random.map");
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

bool Scene::SettingsScene::collideUp()
{
    float tileSpace = 10 - 2;

    for (auto &object : _gameMap->getMapObjects()) {
        if (object.getPosition().getY() == 0) {
            if ((_playerOne->getPosition().getX() >= (object.getPosition().getX() - tileSpace) && _playerOne->getPosition().getX() <= (object.getPosition().getX() + tileSpace))
            && (_playerOne->getPosition().getZ() - _margin >= (object.getPosition().getZ() - tileSpace) && _playerOne->getPosition().getZ() - _margin <= (object.getPosition().getZ() + tileSpace))) {
                    std::cout << "in collision" << std::endl;
                    return (true);
            }
        }
    }
    return (false);
}

bool Scene::SettingsScene::collideDown()
{
    float tileSpace = 10 - 2;

    for (auto &object : _gameMap->getMapObjects()) {
        if (object.getPosition().getY() == 0) {
            if ((_playerOne->getPosition().getX() >= (object.getPosition().getX() - tileSpace) && _playerOne->getPosition().getX() <= (object.getPosition().getX() + tileSpace))
            && (_playerOne->getPosition().getZ() + _margin >= (object.getPosition().getZ() - tileSpace) && _playerOne->getPosition().getZ() + _margin <= (object.getPosition().getZ() + tileSpace))) {
                    std::cout << "in collision" << std::endl;
                    return (true);
            }
        }
    }
    return (false);
}

bool Scene::SettingsScene::collideRight()
{
    float tileSpace = 10 - 2;

    for (auto &object : _gameMap->getMapObjects()) {
        if (object.getPosition().getY() == 0) {
            if ((_playerOne->getPosition().getX() + _margin >= (object.getPosition().getX() - tileSpace) && _playerOne->getPosition().getX() + _margin <= (object.getPosition().getX() + tileSpace))
            && (_playerOne->getPosition().getZ() >= (object.getPosition().getZ() - tileSpace) && _playerOne->getPosition().getZ() <= (object.getPosition().getZ() + tileSpace))) {
                    std::cout << "in collision" << std::endl;
                    return (true);
            }
        }
    }
    return (false);
}

bool Scene::SettingsScene::collideLeft()
{
    float tileSpace = 10 - 2;

    for (auto &object : _gameMap->getMapObjects()) {
        if (object.getPosition().getY() == 0) {
            if ((_playerOne->getPosition().getX() - _margin >= (object.getPosition().getX() - tileSpace) && _playerOne->getPosition().getX() - _margin <= (object.getPosition().getX() + tileSpace))
            && (_playerOne->getPosition().getZ() >= (object.getPosition().getZ() - tileSpace) && _playerOne->getPosition().getZ() <= (object.getPosition().getZ() + tileSpace))) {
                    std::cout << "in collision" << std::endl;
                    return (true);
            }
        }
    }
    return (false);
}

Scene::Scenes Scene::SettingsScene::handelEvent()
{
    _nextScene = Scene::Scenes::SETTINGS;

    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());

    if (IsKeyDown(KEY_UP) && !collideUp())
        _playerOne->move((Position){ _playerOne->getPosition().getX(), _playerOne->getPosition().getY(), _playerOne->getPosition().getZ() - 0.2f});
    else if (IsKeyDown(KEY_DOWN) && !collideDown())
        _playerOne->move((Position){ _playerOne->getPosition().getX(), _playerOne->getPosition().getY(), _playerOne->getPosition().getZ() + 0.2f});
    else if (IsKeyDown(KEY_LEFT) && !collideLeft())
        _playerOne->move((Position){ _playerOne->getPosition().getX() - 0.2f, _playerOne->getPosition().getY(), _playerOne->getPosition().getZ()});
    else if (IsKeyDown(KEY_RIGHT) && !collideRight())
        _playerOne->move((Position){ _playerOne->getPosition().getX() + 0.2f, _playerOne->getPosition().getY(), _playerOne->getPosition().getZ()});
    else
        _playerOne->resetAnimation();

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
