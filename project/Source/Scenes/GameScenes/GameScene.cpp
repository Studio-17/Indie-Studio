/*
** EPITECH PROJECT, 2022
** project
** File description:
** GameScene
*/

#include "GameScene.hpp"
#include <tgmath.h>

void Scene::GameScene::exitScene(void)
{
    _nextScene = Scene::Scenes::QUIT;
}

void Scene::GameScene::settingsScene(void)
{
    _nextScene = Scene::Scenes::SETTINGS;
}

void Scene::GameScene::newGameScene(void)
{
    _nextScene = Scene::Scenes::GAME;
}

void Scene::GameScene::mainMenuScene(void)
{
    _nextScene = Scene::Scenes::MAIN_MENU;
}

Scene::GameScene::GameScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings) :
    AScene(settings), _gameSettings(gameSettings), _actionMap ({
                {PlayerAction::MoveLeft, {{-1, 0, 0}, {0, 0, 0}}},
                {PlayerAction::MoveRight, {{1, 0, 0}, {0, 180, 0}}},
                {PlayerAction::MoveUp, {{0, 0, -1}, {0, 90, 0}}},
                {PlayerAction::MoveDown, {{0, 0, 1}, {0, -90, 0}}},
                {PlayerAction::Drop, {{0, 0, 0}, {0, 0, 0}}}})
{
    loadSceneAssets();

    _nextScene = Scene::Scenes::GAME;

    _gameMap = std::make_unique<Object::Map>(_models, _textures);
    _mapSize = {11, 11};
    _mapFile = gameSettings->getMapPath();
    _margin = 5.0f;
    _collisionCondition = {
        {PlayerAction::MoveLeft, {-_margin, 0, 0}},
        {PlayerAction::MoveRight, {_margin, 0, 0}},
        {PlayerAction::MoveUp, {0, 0, -_margin}},
        {PlayerAction::MoveDown, {0, 0, _margin}},
        {PlayerAction::Drop, {0, 0, 0}}
    };
    _playerSpeed = 0.6f;
    _playerPositions = _gameMap->getMapCorners(_mapSize.x, _mapSize.y);
    _gameMap->generate(_mapFile, _mapSize.x, _mapSize.y, 90);
    _gameMap->process(_mapFile);

    _players.emplace_back(std::make_unique<Object::Player>(_models.at(0), _textures.at(1), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1)), Object::MAP_OBJECTS::PLAYER));
    _players.emplace_back(std::make_unique<Object::Player>(_models.at(1), _textures.at(2), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER2)), Object::MAP_OBJECTS::PLAYER));
    _players.emplace_back(std::make_unique<Object::Player>(_models.at(2), _textures.at(3), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER3)), Object::MAP_OBJECTS::PLAYER));
    _players.emplace_back(std::make_unique<Object::Player>(_models.at(3), _textures.at(4), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER4)), Object::MAP_OBJECTS::PLAYER));
}

Scene::GameScene::~GameScene()
{
}

void Scene::GameScene::fadeBlack()
{

}

void Scene::GameScene::loadSceneAssets()
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
    _models.emplace_back("");

    _textures.emplace_back("Ressources/models/block/stone/box.png");
    _textures.emplace_back("Ressources/models/block/dirt/wall_side.png");
    _textures.emplace_back("Ressources/models/block/stone/wall_side.png");
    _textures.emplace_back("Ressources/models/block/dirt/box.png");
    _textures.emplace_back("");

    // BOMB
    // ("Ressourhttps://github.com/MyEpitech/B-YEP-400-PAR-4-1-indiestudio-martin.vanaud/pull/77/conflict?name=project%252FSource%252FScenes%252FGameScenes%252FGameScene.cpp&ancestor_oid=715b3cb86f33664af1a888c95d667bbe42000acc&base_oid=fce135dcf841e6ee2401dde0c4ca9302b3b10b7f&head_oid=55133c22d2d9e8f6b81adcb9a9df24f1ef2b74c2ces/models/bomb/bomb.obj");
    // ("Ressources/models/bomb/bomb.png");
}

bool Scene::GameScene::isCollidingBomb(Position const &direction, Position const &playerPosition, Object::PLAYER_ORDER playerNb)
{
    Position newPlayerPos = playerPosition;
    newPlayerPos += direction;
    std::pair<int, int> position = _gameMap->transposeFrom3Dto2D(newPlayerPos);

    for (auto &object : _bombs) {
        std::pair<int, int> block = _gameMap->transposeFrom3Dto2D(object->getPosition());
        if (position.first == block.first && position.second == block.second && object->getPlayer() == static_cast<Object::PLAYER_ORDER>(playerNb)) {
            if (!object->getCollide())
                return false;
            return true;
        }
        else
            object->setCollide(true);
    }
    return false;
}

Scene::Scenes Scene::GameScene::handleEvent()
{
    bool moving = false;
    int index = 0;

    _nextScene = Scene::Scenes::GAME;
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());

    for (auto &playerAc: _settings->getPlayerActionsPressed()) {
        moving = false;
        for (auto &[action, isPressed] : playerAc) {
            if (isPressed) {
                if (playerPressesDrop(action))
                    placeBomb(_players.at(index)->getPosition(), 5, 1, static_cast<Object::PLAYER_ORDER>(index));
                else if (_gameMap->isColliding(_collisionCondition.at(action), _players.at(index)->getPosition()) == Object::MAP_OBJECTS::EMPTY && !isCollidingBomb(_collisionCondition.at(action), _players.at(index)->getPosition(), static_cast<Object::PLAYER_ORDER>(index))) {
                    _players.at(index)->move(_actionMap.at(action).first, _actionMap.at(action).second);
                    moving = true;
                }
            }
        }
        if (!moving)
            _players.at(index)->animation(1);
        index++;
    }
    ai();
    return _nextScene;
}

bool Scene::GameScene::seeBomb(Position margin, std::vector<std::unique_ptr<Object::Player>> &players, int playerNb)
{
    float tileSpace = _gameMap->getBlockSize() - (_margin * 2 + 0.4f);
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
    }
    return false;
}

void Scene::GameScene::ai()
{
    srand(time(NULL));
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

    for (int i = 2; i < 4; i++) {
        int action = rand() % 4;

        if (!seeBomb(collisionCondition.at((PlayerAction) action), _players, i)) {
            if (_gameMap->isColliding(collisionCondition.at((PlayerAction) action), _players.at(i)->getPosition()) == Object::MAP_OBJECTS::EMPTY && !isCollidingBomb(collisionCondition.at((PlayerAction) action), _players, i)) {
                _players.at(i)->move(actionMap.at((PlayerAction) action).first, actionMap.at((PlayerAction) action).second);
                moving = true;
            }
        }
        if (!moving)
            _players.at(i)->animation(1);
    }
}

void Scene::GameScene::placeBomb(Position pos, float lifetime, std::size_t range, Object::PLAYER_ORDER playerNb)
{
    bool blockTooked = false;
    int nb = _gameMap->roundUp(pos.getZ(), _gameMap->getBlockSize() / 2);
    if (nb % 10 == (_gameMap->getBlockSize() / 2))
        nb -= _gameMap->getBlockSize() / 2;
    Position newPos = {static_cast<float>(_gameMap->roundUp(pos.getX(), _gameMap->getBlockSize() / 2)), pos.getY(), static_cast<float>(nb)};
    if (static_cast<int>(newPos.getX()) % 10 == 0) {
        for (auto &bomb : _bombs) {
            if (bomb->getPosition() == newPos)
                blockTooked = true;
        }
        if (!blockTooked)
            _bombs.emplace_back(std::make_unique<Object::Bomb>(std::make_pair<std::string, std::string>("Ressources/models/bomb/bomb.obj", "Ressources/models/bomb/bomb.png"), newPos, playerNb, 3, 2, Object::MAP_OBJECTS::BOMB));
    }
}

void Scene::GameScene::setBonus(Position const &position, std::size_t percentageDrop)
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
        _bonus.emplace_back(std::make_unique<Object::Bonus>(bonusMap.at(static_cast<Object::BONUS_OBJECTS>(randomBonus)), position, static_cast<Object::BONUS_OBJECTS>(randomBonus), Object::MAP_OBJECTS::BONUS));
}

void Scene::GameScene::draw()
{
    _settings->getCamera()->startMode3D();
    _gameMap->draw();
    for (auto &player : _players)
        player->draw();

    if (!_bombs.empty()) {
        for (std::size_t bombPos = 0; bombPos < _bombs.size(); bombPos++) {
            if (_bombs.at(bombPos)->checkIfShouldExplode()) {
                _gameMap->exploseBomb(_bombs.at(bombPos)->getPosition(), _bombs.at(bombPos)->getRange());
                _bombs.erase(_bombs.begin() + bombPos);
            }
        }
    }
    for (auto &bonus : _bonus)
        bonus->draw();

    for (auto &bomb : _bombs)
        bomb->draw();
    _settings->getCamera()->endMode3D();
}
