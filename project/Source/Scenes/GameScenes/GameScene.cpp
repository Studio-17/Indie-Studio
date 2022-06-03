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

Scene::GameScene::GameScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    loadSceneAssets();

    _nextScene = Scene::Scenes::GAME;

    _gameMap = std::make_unique<Object::Map>(_models, _textures);
    _mapSize = {11, 11};
    _mapFile = "Save/Maps/random.map";
    _margin = 5.0f;
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
    // ("Ressources/models/bomb/bomb.obj");
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

void Scene::GameScene::handleBombs()
{
    if (!_bombs.empty()) {
        for (std::size_t bombPos = 0; bombPos < _bombs.size(); bombPos++) {
            if (_bombs.at(bombPos)->checkIfShouldExplode()) {
                exploseBomb(_bombs.at(bombPos)->getPosition(), _bombs.at(bombPos)->getRange());
                _bombs.erase(_bombs.begin() + bombPos);
            }
        }
    }
}

Scene::Scenes Scene::GameScene::handleEvent()
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

    _nextScene = Scene::Scenes::GAME;
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());

    for (auto &playerAc: _settings->getPlayerActionsPressed()) {
        moving = false;
        for (auto &[action, isPressed] : playerAc) {
            if (isPressed) {
                if (playerPressesDrop(action))
                    placeBomb(_players.at(index)->getPosition(), 5, 1, static_cast<Object::PLAYER_ORDER>(index));
                else if (_gameMap->isColliding(collisionCondition.at(action), _players.at(index)->getPosition()) == Object::MAP_OBJECTS::EMPTY && !isCollidingBomb(collisionCondition.at(action), _players.at(index)->getPosition(), static_cast<Object::PLAYER_ORDER>(index))) {
                    _players.at(index)->move(actionMap.at(action).first, actionMap.at(action).second);
                    moving = true;
                }
            }
        }
        if (!moving)
            _players.at(index)->animation(1);
        index++;
    }
    handleBombs();
    return _nextScene;
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

void Scene::GameScene::checkIfPlayerIsInRange(std::pair<int, int> explosionPos)
{
    std::pair<int, int> playerPos;

    for (std::size_t player = 0; player < _players.size(); player++) {
        playerPos = _gameMap->transposeFrom3Dto2D(_players.at(player)->getPosition());
        // if (playerPos == explosionPos)
        //     _players.erase(_players.begin() + player);
    }
}

void Scene::GameScene::exploseBomb(Position const &position, int radius)
{
    // std::size_t percentageBonusDrop = 30;
    std::pair<int, int> blockPosition = _gameMap->transposeFrom3Dto2D(position);
    float blockSize = _gameMap->getBlockSize();
    std::vector<bool> alreadyDestroyed = { false, false, false, false };
    Position blockToPlace;
    std::vector<std::pair<int, int>> target = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::size_t index = 0;

    for (std::size_t bombRange = 1; bombRange < radius + 1; bombRange++) {
        index = 0;
        for (auto &[x, y] : target) {
            if ((blockPosition.second + (y * bombRange)) > 0 && (blockPosition.second + (y * bombRange)) < _gameMap->getMapPositionsObjects().size())
                if ((blockPosition.first + (x * bombRange)) > 0 && (blockPosition.first + (x * bombRange)) < _gameMap->getMapPositionsObjects().at(blockPosition.second + (y * bombRange)).size()) {
                    if (_gameMap->getMapPositionsObjects().at(blockPosition.second + (y * bombRange)).at(blockPosition.first + (x * bombRange))->getType() == Object::MAP_OBJECTS::WALL_MIDDLE)
                        alreadyDestroyed.at(index) = true;
                    if (_gameMap->getMapPositionsObjects().at(blockPosition.second + (y * bombRange)).at(blockPosition.first + (x * bombRange))->getType() == Object::MAP_OBJECTS::BOX && !alreadyDestroyed.at(index)) {
                        blockToPlace = {static_cast<float>((blockPosition.first +  (x * bombRange)) * 10), 0, static_cast<float>((blockPosition.second +(y * bombRange)) * 10)};
                        _gameMap->placeObjectInMap<Object::Block>({blockPosition.first + (x * bombRange), blockPosition.second + (y * bombRange)}, std::make_shared<Object::Block>(_gameMap->getMapModels().at(8), _gameMap->getMapTextures().at(10), blockToPlace, Object::MAP_OBJECTS::EMPTY));
                        checkIfPlayerIsInRange({blockPosition.first + (x * bombRange), blockPosition.second + (y * bombRange)});
                        alreadyDestroyed.at(index) = true;
                    }
                }
            index++;
        }
    }
}

void Scene::GameScene::draw()
{
    _settings->getCamera()->startMode3D();
    _gameMap->draw();
    for (auto &player : _players)
        player->draw();

    for (auto &bonus : _bonus)
        bonus->draw();

    for (auto &bomb : _bombs)
        bomb->draw();
    _settings->getCamera()->endMode3D();
}
