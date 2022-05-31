/*
** EPITECH PROJECT, 2022
** project
** File description:
** SettingsScene
*/

#include "SettingsScene.hpp"
#include <tgmath.h>

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
    _playerSpeed = 0.2f;
    _gameMap->generate(_mapFile, 11, 11);
    _gameMap->process(_mapFile);
    _players.emplace_back(std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/models/player/player.iqm", "Ressources/models/player/blue.png"), "Ressources/models/player/player.iqm", 1, Position(100, 0, 10)));
    _settings->getCamera()->setTarget({_gameMap->getDimensions()});
    _settings->getCamera()->setPosition(_gameMap->getDimensions());
}

Scene::SettingsScene::~SettingsScene()
{
}

void Scene::SettingsScene::fadeBlack()
{

}

bool Scene::SettingsScene::isCollidingBomb(Position margin, std::vector<std::unique_ptr<Object::Player>> &players, Object::PLAYER_ORDER playerNb)
{
    float tileSpace = _gameMap->getBlockSize() - (_margin + 0.5f);
    Position playerPos = players.at(static_cast<char>(playerNb))->getPosition();

    for (auto &object : _bombs) {
        Position block = object->getPosition();

        if (object->getPosition().getY() == 0 &&
        ((playerPos.getX() + margin.getX() >= (block.getX() - tileSpace) && playerPos.getX() + margin.getX() <= (block.getX() + tileSpace)) &&
        (playerPos.getZ() + margin.getZ() >= (block.getZ() - tileSpace) && playerPos.getZ() + margin.getZ() <= (block.getZ() + tileSpace)))) {
            if (!object->getCollide())
                return (false);
            return true;
        }
        else
            object->setCollide(true);
    }
    return false;
}

bool Scene::SettingsScene::isCollidingBlock(Position margin, std::unique_ptr<Object::Player> &player)
{
    float tileSpace = _gameMap->getBlockSize() - _margin;
    Position playerPos = player->getPosition();

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
    Position playerPos = _players.at(0)->getPosition();

    _nextScene = Scene::Scenes::SETTINGS;
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    switch (key) {
        case KEY_UP:
            if (!isCollidingBlock({0, 0, -_margin}, _players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1))) && !isCollidingBomb({0, 0, -_margin}, _players, Object::PLAYER_ORDER::PLAYER1))
                _players.at(0)->move({ playerPos.getX(), playerPos.getY(), playerPos.getZ() - _playerSpeed}, {0, 90, 0});
            break;
        case KEY_DOWN:
            if (!isCollidingBlock({0, 0, _margin}, _players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1))) && !isCollidingBomb({0, 0, _margin}, _players, Object::PLAYER_ORDER::PLAYER1))
                _players.at(0)->move({ playerPos.getX(), playerPos.getY(), playerPos.getZ() + _playerSpeed}, {0, -90, 0});
            break;
        case KEY_LEFT:
            if (!isCollidingBlock({-_margin, 0, 0}, _players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1))) && !isCollidingBomb({-_margin, 0, 0}, _players, Object::PLAYER_ORDER::PLAYER1))
                _players.at(0)->move({ playerPos.getX() - _playerSpeed, playerPos.getY(), playerPos.getZ()}, {0, 0, 0});
            break;
        case KEY_RIGHT:
            if (!isCollidingBlock({_margin, 0, 0}, _players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1))) && !isCollidingBomb({_margin, 0, 0}, _players, Object::PLAYER_ORDER::PLAYER1))
                _players.at(0)->move({ playerPos.getX() + _playerSpeed, playerPos.getY(), playerPos.getZ()}, {0, 180, 0});
            break;
        case KEY_SPACE:
            placeBomb(playerPos, 5, 1, Object::PLAYER_ORDER::PLAYER1);
            break;
        default:
            _players.at(0)->resetAnimation();
    }
    return _nextScene;
}

int Scene::SettingsScene::roundUp(int nb, int multiple)
{
    if (multiple == 0)
        return nb;

    int remainder = abs(nb) % multiple;

    if (remainder == 0)
        return nb;

    if (nb < 0)
        return -(abs(nb) - remainder);
    else
        return nb + multiple - remainder;
}

void Scene::SettingsScene::placeBomb(Position pos, float lifetime, std::size_t range, Object::PLAYER_ORDER playerNb)
{
    bool blockTooked = false;
    int nb = roundUp(pos.getZ(), _gameMap->getBlockSize() / 2);
    if (nb % 10 == (_gameMap->getBlockSize() / 2))
        nb -= _gameMap->getBlockSize() / 2;

    Position newPos = {static_cast<float>(roundUp(pos.getX(), _gameMap->getBlockSize() / 2)), pos.getY(), static_cast<float>(nb)};

    if (static_cast<int>(newPos.getX()) % 10 == 0) {
        for (auto &bomb : _bombs) {
            if (bomb->getPosition() == newPos)
                blockTooked = true;
        }
        if (!blockTooked)
            _bombs.emplace_back(std::make_unique<Object::Bomb>(std::make_pair<std::string, std::string>("Ressources/models/bomb/bomb.obj", "Ressources/models/bomb/bomb.png"), newPos, playerNb, 3, 1));
    }
}

void Scene::SettingsScene::draw()
{
    _settings->getCamera()->startMode3D();

        DrawLine3D((Vector3){-1000, 0, 0}, (Vector3){1000, 0, 0}, GREEN);     // X
        DrawLine3D((Vector3){0, -1000, 0}, (Vector3){0, 1000, 0}, RED);       // Y
        DrawLine3D((Vector3){0, 0, -1000}, (Vector3){0, 0, 1000}, DARKBLUE);  // Z

        _gameMap->draw();
        _players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1))->draw();

        if (!_bombs.empty()) {
            for(std::size_t i = 0; i < _bombs.size(); i++) {
                if (_bombs.at(i)->checkIfShouldExplode())
                    _bombs.erase(_bombs.begin() + i);
            }
        }

        for (auto &bomb : _bombs)
            bomb->draw();

    _settings->getCamera()->endMode3D();

    for (auto &button : _buttons)
        button->draw();
}
