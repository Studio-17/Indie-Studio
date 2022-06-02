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
    loadSceneAssets();

    _nextScene = Scene::Scenes::SETTINGS;

    _gameMap = std::make_unique<Object::Map>(_models, _textures);
    _mapSize = {11, 11};
    _mapFile = "Save/Maps/random.map";

    _margin = 1.9f;
    _playerSpeed = 0.2f;

    _playerPositions = _gameMap->getMapCorners(_mapSize.x, _mapSize.y);

    _gameMap->generate(_mapFile, _mapSize.x, _mapSize.y);
    _gameMap->process(_mapFile);

    _players.emplace_back(std::make_unique<Object::Player>(_models.at(0), _textures.at(1), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1))));
    _players.emplace_back(std::make_unique<Object::Player>(_models.at(1), _textures.at(2), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER2))));
    _players.emplace_back(std::make_unique<Object::Player>(_models.at(2), _textures.at(3), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER3))));
    _players.emplace_back(std::make_unique<Object::Player>(_models.at(3), _textures.at(4), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER4))));
}

Scene::SettingsScene::~SettingsScene()
{
}

void Scene::SettingsScene::fadeBlack()
{

}

void Scene::SettingsScene::loadSceneAssets()
{
    // CHARACTERS
    _animations.emplace_back("Ressources/models/player/player.iqm", 0);

    _models.emplace_back("Ressources/models/player/player.iqm");
    _models.emplace_back("Ressources/models/player/player.iqm");
    _models.emplace_back("Ressources/models/player/player.iqm");
    _models.emplace_back("Ressources/models/player/player.iqm");

    _textures.emplace_back("Ressources/models/player/blue.png");
    _textures.emplace_back("Ressources/models/player/cyan.png");
    _textures.emplace_back("Ressources/models/player/green.png");
    _textures.emplace_back("Ressources/models/player/purple.png");
    _textures.emplace_back("Ressources/models/player/red.png");
    _textures.emplace_back("Ressources/models/player/yellow.png");

    // BLOCKS
    _models.emplace_back("Ressources/models/block/stone/box.obj");
    _models.emplace_back("Ressources/models/block/dirt/wall_side.obj");
    _models.emplace_back("Ressources/models/block/stone/wall_side.obj");
    _models.emplace_back("Ressources/models/block/dirt/box.obj");

    _textures.emplace_back("Ressources/models/block/stone/box.png");
    _textures.emplace_back("Ressources/models/block/dirt/wall_side.png");
    _textures.emplace_back("Ressources/models/block/stone/wall_side.png");
    _textures.emplace_back("Ressources/models/block/dirt/box.png");

    // BOMB
}

bool Scene::SettingsScene::isCollidingBomb(Position margin, std::vector<std::unique_ptr<Object::Player>> &players, int playerNb)
{
    float tileSpace = _gameMap->getBlockSize() - (_margin + 0.4f);
    Position playerPos = players.at(playerNb)->getPosition();

    for (auto &object : _bombs) {
        Position block = object->getPosition();

        if (object->getPosition().getY() == 0 &&
        ((playerPos.getX() + margin.getX() >= (block.getX() - tileSpace) && playerPos.getX() + margin.getX() <= (block.getX() + tileSpace)) &&
        (playerPos.getZ() + margin.getZ() >= (block.getZ() - tileSpace) && playerPos.getZ() + margin.getZ() <= (block.getZ() + tileSpace)))) {
            if (!object->getCollide())
                return false;
            return true;
        }
        else
            object->setCollide(true);
    }
    return false;
}

bool Scene::SettingsScene::isCollidingBlock(Position margin, std::unique_ptr<Object::Player> &player)
{
    float tileSpace = _gameMap->getBlockSize() - (_margin - 0.4f);
    Position playerPosition = player->getPosition();

    for (auto &object : _gameMap->getMapObjects()) {
        Position blockPosition = object->getPosition();

        if (object->getPosition().getY() == 0 &&
        ((playerPosition.getX() + margin.getX() >= (blockPosition.getX() - tileSpace) && playerPosition.getX() + margin.getX() <= (blockPosition.getX() + tileSpace)) &&
        (playerPosition.getZ() + margin.getZ() >= (blockPosition.getZ() - tileSpace) && playerPosition.getZ() + margin.getZ() <= (blockPosition.getZ() + tileSpace))))
            return true;
    }
    return false;
}

Scene::Scenes Scene::SettingsScene::handelEvent()
{
    std::map<PlayerAction, std::pair<Position, Position>> actionMap = {
        {PlayerAction::MoveLeft, {{-_playerSpeed, 0, 0}, {0, 0, 0}}},
        {PlayerAction::MoveRight, {{_playerSpeed, 0, 0}, {0, 180, 0}}},
        {PlayerAction::MoveUp, {{0, 0, -_playerSpeed}, {0, 90, 0}}},
        {PlayerAction::MoveDown, {{0, 0, _playerSpeed}, {0, -90, 0}}},
        {PlayerAction::Drop, {{0, 0, 0}, {0, 0, 0}}}
    };
    std::map<PlayerAction, Position> collisionCondition = {
        {PlayerAction::MoveLeft, {-_margin, 0, 0}},
        {PlayerAction::MoveRight, {_margin, 0, 0}},
        {PlayerAction::MoveUp, {0, 0, -_margin}},
        {PlayerAction::MoveDown, {0, 0, _margin}},
        {PlayerAction::Drop, {0, 0, 0}}
    };
    bool moving = false;
    int index = 0;

    _nextScene = Scene::Scenes::SETTINGS;
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());

    for (auto &playerAc: _settings->getPlayerActionsPressed()) {
        moving = false;
        for (auto &[action, isPressed] : playerAc) {
            if (isPressed) {
                if (playerPressesDrop(action))
                    placeBomb(_players.at(index)->getPosition(), 5, 1, Object::PLAYER_ORDER::PLAYER1);
                else if (playerCanMove(collisionCondition.at(action), index)) {
                    _players.at(index)->move(actionMap.at(action).first, actionMap.at(action).second);
                    moving = true;
                }
            }
        }
        if (!moving)
            _players.at(index)->animation(1);
        index++;
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
        return (-(abs(nb) - remainder));
    else
        return (nb + multiple - remainder);
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

void Scene::SettingsScene::setBonus(Position const &position, std::size_t percentageDrop)
{
    static std::map<Object::BONUS_OBJECTS, std::pair<std::string, std::string>> bonusMap = {
        {Object::BONUS_OBJECTS::BOMB_DOWN, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/bomb_down.png"}},
        {Object::BONUS_OBJECTS::BOMB_MOVE, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/bomb_move.png"}},
        {Object::BONUS_OBJECTS::BOMB_UP, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/bomb_up.png"}},
        {Object::BONUS_OBJECTS::BOX_MOVE, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/box_move.png"}},
        {Object::BONUS_OBJECTS::DEATH_HEAD, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/death_head.png"}},
        {Object::BONUS_OBJECTS::EMPTY, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/empty.png"}},
        {Object::BONUS_OBJECTS::FIRE_DOWN, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/fire_down.png"}},
        {Object::BONUS_OBJECTS::FIRE_UP, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/fire_up.png"}},
        {Object::BONUS_OBJECTS::HEARTH, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/hearth.png"}},
        {Object::BONUS_OBJECTS::ICE_GLOVE, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/ice_glove.png"}},
        {Object::BONUS_OBJECTS::KICK, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/kick.png"}},
        {Object::BONUS_OBJECTS::P_BOMB, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/p_bomb.png"}},
        {Object::BONUS_OBJECTS::PEAKY_BOMB, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/peaky_bomb.png"}},
        {Object::BONUS_OBJECTS::PUNCH, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/punch.png"}},
        {Object::BONUS_OBJECTS::RISE_UP, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/rise_up.png"}},
        {Object::BONUS_OBJECTS::SPEED_DOWN, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/speed_down.png"}},
        {Object::BONUS_OBJECTS::SPEED_UP, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/speed_up.png"}},
        {Object::BONUS_OBJECTS::WATER_BOMB, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/water_bomb.png"}},
        {Object::BONUS_OBJECTS::WIZARD, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/wizard.png"}}
    };
    srand(time(NULL));
    std::size_t randomNumber = 1 + (rand() % 100);
    std::size_t randomBonus = 1 + (rand() % bonusMap.size());

    if (randomNumber >= 1 && randomNumber <= percentageDrop)
        _bonus.emplace_back(std::make_unique<Object::Bonus>(bonusMap.at(static_cast<Object::BONUS_OBJECTS>(randomBonus)), position, static_cast<Object::BONUS_OBJECTS>(randomBonus)));
}

void Scene::SettingsScene::explodeBomb(std::size_t bombPos)
{
    std::size_t percentageBonusDrop = 100;
    float blockSize = _gameMap->getBlockSize();
    std::vector<bool> alreadyDestroyed = { false, false, false, false };

    for (std::size_t bombRange = 0; bombRange < _bombs.at(bombPos)->getRange(); bombRange++) {
        for (std::size_t index = 0; index < _gameMap->getMapObjects().size(); index++) {
            if (_gameMap->getMapObjects().at(index)->getPosition() == (_bombs.at(bombPos)->getPosition() += (Position){0, 0, -blockSize}) && !alreadyDestroyed.at(0)) {
                _gameMap->removeBlock(index);
                alreadyDestroyed.at(0) = true;
                setBonus(_bombs.at(bombPos)->getPosition() += (Position){0, 0, -blockSize}, percentageBonusDrop);
            }
            if (_gameMap->getMapObjects().at(index)->getPosition() == (_bombs.at(bombPos)->getPosition() += (Position){0, 0, blockSize}) && !alreadyDestroyed.at(1)) {
                _gameMap->removeBlock(index);
                alreadyDestroyed.at(1) = true;
                setBonus(_bombs.at(bombPos)->getPosition() += (Position){0, 0, blockSize}, percentageBonusDrop);
            }
            if (_gameMap->getMapObjects().at(index)->getPosition() == (_bombs.at(bombPos)->getPosition() += (Position){-blockSize, 0, 0}) && !alreadyDestroyed.at(2)) {
                _gameMap->removeBlock(index);
                alreadyDestroyed.at(2) = true;
                setBonus(_bombs.at(bombPos)->getPosition() += (Position){-blockSize, 0, 0}, percentageBonusDrop);
            }
            if (_gameMap->getMapObjects().at(index)->getPosition() == (_bombs.at(bombPos)->getPosition() += (Position){blockSize, 0, 0}) && !alreadyDestroyed.at(3)) {
                _gameMap->removeBlock(index);
                alreadyDestroyed.at(3) = true;
                setBonus(_bombs.at(bombPos)->getPosition() += (Position){blockSize, 0, 0}, percentageBonusDrop);
            }
        }
        blockSize += _gameMap->getBlockSize();
    }
}

void Scene::SettingsScene::draw()
{
    _settings->getCamera()->startMode3D();
    _gameMap->draw();
    for (auto &player : _players)
        player->draw();

    if (!_bombs.empty()) {
        for (std::size_t bombPos = 0; bombPos < _bombs.size(); bombPos++) {
            if (_bombs.at(bombPos)->checkIfShouldExplode()) {
                explodeBomb(bombPos);
                _bombs.erase(_bombs.begin() + bombPos);
            }
        }
    }
    _gameMap->draw();

    for (auto &bonus : _bonus)
        bonus->draw();

    // _explosion->draw();

    for (auto &bomb : _bombs)
        bomb->draw();
    _settings->getCamera()->endMode3D();

    // for (auto &button : _buttons)
        // button->draw();
}
