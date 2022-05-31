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
        Position block = object->getPosition();

        if (object->getPosition().getY() == 0 &&
        ((playerPos.getX() + margin.getX() >= (block.getX() - tileSpace) && playerPos.getX() + margin.getX() <= (block.getX() + tileSpace)) &&
        (playerPos.getZ() + margin.getZ() >= (block.getZ() - tileSpace) && playerPos.getZ() + margin.getZ() <= (block.getZ() + tileSpace))))
            return true;
    }
    return false;
}

Scene::Scenes Scene::SettingsScene::handelEvent()
{
    std::map<PlayerAction, std::pair<Position, Position>> actionMap = {{PlayerAction::MoveLeft, {{-_playerSpeed, 0, 0}, {0, 0, 0}}},
        {PlayerAction::MoveRight, {{_playerSpeed, 0, 0}, {0, 180, 0}}},
        {PlayerAction::MoveUp, {{0, 0, -_playerSpeed}, {0, 90, 0}}},
        {PlayerAction::MoveDown, {{0, 0, _playerSpeed}, {0, -90, 0}}},
        {PlayerAction::Drop, {{0, 0, 0}, {0, 0, 0}}}};
    std::map<PlayerAction, Position> collisionCondition = {{PlayerAction::MoveLeft, {-_margin, 0, 0}},
        {PlayerAction::MoveRight, {_margin, 0, 0}},
        {PlayerAction::MoveUp, {0, 0, -_margin}},
        {PlayerAction::MoveDown, {0, 0, _margin}},
        {PlayerAction::Drop, {0, 0, 0}}};

    bool moving = false;

    _nextScene = Scene::Scenes::SETTINGS;
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());

    for (auto &playerAc: _settings->getPlayerActionsPressed()) {
        for (auto &[action, isPressed] : playerAc) {
            if (isPressed) {
                if (action == PlayerAction::Drop)
                    placeBomb(_players.at(0)->getPosition(), 5, 1, Object::PLAYER_ORDER::PLAYER1);
                else if (!isCollidingBlock(collisionCondition.at(action), _players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1))) && !isCollidingBomb(collisionCondition.at(action), _players, Object::PLAYER_ORDER::PLAYER1)) {
                    _players.at(0)->move(actionMap.at(action).first, actionMap.at(action).second);
                    moving = true;
                }
            }
        }
    }

    if (!moving)
        _players.at(0)->resetAnimation();
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
            _bombs.emplace_back(std::make_unique<Object::Bomb>(std::make_pair<std::string, std::string>("Ressources/models/bomb/bomb.obj", "Ressources/models/bomb/bomb.png"), newPos, playerNb, 3, 2));
    }
}

void Scene::SettingsScene::explodeBomb(std::size_t bombPos)
{
    float blockSize = _gameMap->getBlockSize();

    std::map<ORIENTATION, std::pair<bool, Position>> explosionMap = {
        {UP, {false, {0, 0, -blockSize}}},
        {DOWN, {false, {0, 0, blockSize}}},
        {LEFT, {false, {-blockSize, 0, 0}}},
        {RIGHT, {false, {blockSize, 0, 0}}}
    };

    for (std::size_t bombRange = 0; bombRange < _bombs.at(bombPos)->getRange(); bombRange++) {
        for (std::size_t index = 0; index < _gameMap->getMapObjects().size(); index++) {
            for (auto &[_, bombInfo] : explosionMap) {
                if (_gameMap->getMapObjects().at(index)->getPosition() == (_bombs.at(bombPos)->getPosition() += bombInfo.second) && !bombInfo.first)
                    bombInfo.first = _gameMap->removeBlock(index);
            }
        }
        blockSize += _gameMap->getBlockSize();
    }
}

void Scene::SettingsScene::draw()
{
    _settings->getCamera()->startMode3D();

        if (!_bombs.empty()) {
            for (std::size_t bombPos = 0; bombPos < _bombs.size(); bombPos++) {
                if (_bombs.at(bombPos)->checkIfShouldExplode()) {
                    explodeBomb(bombPos);
                    _bombs.erase(_bombs.begin() + bombPos);
                }
            }
        }

        _gameMap->draw();
        _players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1))->draw();

        for (auto &bomb : _bombs)
            bomb->draw();

    _settings->getCamera()->endMode3D();

    for (auto &button : _buttons)
        button->draw();
}
