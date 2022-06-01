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
    _players.emplace_back(std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/models/player/player.iqm", "Ressources/models/player/blue.png"), "Ressources/models/player/player.iqm", 1, Position(110, 0, 10)));
    _players.emplace_back(std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/models/player/player.iqm", "Ressources/models/player/blue.png"), "Ressources/models/player/player.iqm", 1, Position(10, 0, 10)));
    _players.emplace_back(std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/models/player/player.iqm", "Ressources/models/player/blue.png"), "Ressources/models/player/player.iqm", 1, Position(10, 0, 110)));
    _players.emplace_back(std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/models/player/player.iqm", "Ressources/models/player/blue.png"), "Ressources/models/player/player.iqm", 1, Position(110, 0, 110)));
    Position tmpPos = _gameMap->getDimensions();
    std::cout << "trget" << tmpPos << std::endl;
    tmpPos.setY(tmpPos.getY() + 200);
    tmpPos.setZ(tmpPos.getZ() + 32);
    // _settings->getCamera()->setTarget({_gameMap->getDimensions()});
    // _settings->getCamera()->setPosition(tmpPos);
    std::cout << "target" << tmpPos << std::endl;

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
    int index = 0;

    _nextScene = Scene::Scenes::SETTINGS;
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    for (auto &playerAc: _settings->getPlayerActionsPressed()) {
        for (auto &[action, isPressed] : playerAc) {
            if (isPressed) {
                if (action == PlayerAction::Drop)
                    placeBomb(_players.at(index)->getPosition(), 5, 1, Object::PLAYER_ORDER::PLAYER1);
                else if (!isCollidingBlock(collisionCondition.at(action), _players.at(index)) && !isCollidingBomb(collisionCondition.at(action), _players, static_cast<Object::PLAYER_ORDER>(index))) {
                    _players.at(index)->move(actionMap.at(action).first, actionMap.at(action).second);
                    moving = true;
                }
            }
        }
        index++;
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
    float blockSize = 10.0f;
    std::vector<bool> alreadyDestroyed = {
        false,
        false,
        false,
        false
    };

    for (std::size_t bombRange = 0; bombRange < _bombs.at(bombPos)->getRange(); bombRange++) {
        for (std::size_t index = 0; index < _gameMap->getMapObjects().size(); index++) {
            if (_gameMap->getMapObjects().at(index)->getPosition() == (_bombs.at(bombPos)->getPosition() += (Position){0, 0, -blockSize}) && !alreadyDestroyed.at(0))
                alreadyDestroyed.at(0) = _gameMap->removeBlock(index);

            if (_gameMap->getMapObjects().at(index)->getPosition() == (_bombs.at(bombPos)->getPosition() += (Position){0, 0, blockSize}) && !alreadyDestroyed.at(1))
                alreadyDestroyed.at(1) = _gameMap->removeBlock(index);

            if (_gameMap->getMapObjects().at(index)->getPosition() == (_bombs.at(bombPos)->getPosition() += (Position){-blockSize, 0, 0}) && !alreadyDestroyed.at(2))
                alreadyDestroyed.at(2) = _gameMap->removeBlock(index);

            if (_gameMap->getMapObjects().at(index)->getPosition() == (_bombs.at(bombPos)->getPosition() += (Position){blockSize, 0, 0}) && !alreadyDestroyed.at(3))
                alreadyDestroyed.at(3) = _gameMap->removeBlock(index);

        }
        blockSize += 10.0f;
    }
}

void Scene::SettingsScene::draw()
{
    _settings->getCamera()->startMode3D();

        DrawLine3D((Vector3){-1000, 0, 0}, (Vector3){1000, 0, 0}, GREEN);     // X
        DrawLine3D((Vector3){0, -1000, 0}, (Vector3){0, 1000, 0}, RED);       // Y
        DrawLine3D((Vector3){0, 0, -1000}, (Vector3){0, 0, 1000}, DARKBLUE);  // Z

        _gameMap->draw();
        for (auto &player : _players)
            player->draw();

        if (!_bombs.empty()) {
            for(std::size_t bombPos = 0; bombPos < _bombs.size(); bombPos++) {
                if (_bombs.at(bombPos)->checkIfShouldExplode()) {
                    explodeBomb(bombPos);
                    _bombs.erase(_bombs.begin() + bombPos);
                }
            }
        }

        for (auto &bomb : _bombs)
            bomb->draw();

    _settings->getCamera()->endMode3D();

    // for (auto &button : _buttons)
        // button->draw();
}
