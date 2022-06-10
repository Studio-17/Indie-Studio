/*
** EPITECH PROJECT, 2022
** project
** File description:
** GameScene
*/

#include <nlohmann/json.hpp>

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
    _backgroundImage = loadObjects<Object::Image>("Conf/Scenes/GameScene/background.json");
    _images = loadObjects<Object::Image>("Conf/Scenes/GameScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/GameScene/text.json");

    _nextScene = Scene::Scenes::GAME;

    _isPaused = false;
    _endGame = false;

    _gameMap = std::make_unique<Object::Map>(_models, _textures);
    _timePerRound = 3;
    _3dcameraVue = false;
    _actualMinutes = _timePerRound - 1;
    _mapSize = {13, 13};
    _mapFile = gameSettings->getMapPath();
    _margin = 5.0f;
    _percentageBonusDrop = 60;
    _percentageBoxDrop = 90;
    _collisionCondition = {
        {PlayerAction::MoveLeft, {-_margin, 0, 0}},
        {PlayerAction::MoveRight, {_margin, 0, 0}},
        {PlayerAction::MoveUp, {0, 0, -_margin}},
        {PlayerAction::MoveDown, {0, 0, _margin}},
        {PlayerAction::Drop, {0, 0, 0}}
    };
    _playerPositions = _gameMap->getMapCorners(_mapSize.x, _mapSize.y);
    _gameMap->generate(_mapFile, _mapSize.x, _mapSize.y, _percentageBoxDrop);
    _gameMap->process(_mapFile);
    _clockGame.start();

    _players.emplace(static_cast<char>(Object::PLAYER_ORDER::PLAYER1), std::make_unique<Object::Player>(_models.at(0), _textures.at(1), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1)), Object::MAP_OBJECTS::PLAYER));
    _players.emplace(static_cast<char>(Object::PLAYER_ORDER::PLAYER2), std::make_unique<Object::Player>(_models.at(1), _textures.at(2), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER2)), Object::MAP_OBJECTS::PLAYER));
    _players.emplace(static_cast<char>(Object::PLAYER_ORDER::PLAYER3), std::make_unique<Object::Player>(_models.at(2), _textures.at(3), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER3)), Object::MAP_OBJECTS::PLAYER));
    _players.emplace(static_cast<char>(Object::PLAYER_ORDER::PLAYER4), std::make_unique<Object::Player>(_models.at(3), _textures.at(4), _animations.at(0), 1, _playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER4)), Object::MAP_OBJECTS::PLAYER));
    _pauseScene = std::make_unique<Scene::PauseScene>(settings, gameSettings, std::bind(&Scene::GameScene::resumeGame, this), std::bind(&Scene::GameScene::save, this));
    _defaultAttributes = {{"bombRange", {1, 3}},
        {"explosionRange", {1, 6}},
        {"speed", {0.4, 0.8}},
        {"kickRange", {1, 3}}};
}

Scene::GameScene::~GameScene()
{
}

void Scene::GameScene::loadSceneAssets()
{
    /* CHARACTERS */
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

    /* BLOCKS */
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

    /* BOMBS */

    /* BONUSES */
}

void Scene::GameScene::resumeGame()
{
    _isPaused = false;
}

void Scene::GameScene::AwardBonus(Object::PLAYER_ORDER playerNb, Object::BONUS_OBJECTS bonus)
{
    switch (bonus) {
        case Object::BONUS_OBJECTS::BOMB_DOWN:
            _players.at(static_cast<char>(playerNb))->setRangeBomb(false);
            break;
        case Object::BONUS_OBJECTS::BOMB_UP:
            _players.at(static_cast<char>(playerNb))->setRangeBomb(true);
            break;
        case Object::BONUS_OBJECTS::FIRE_DOWN:
            _players.at(static_cast<char>(playerNb))->setRangeExplosion(false);
            break;
        case Object::BONUS_OBJECTS::FIRE_UP:
            _players.at(static_cast<char>(playerNb))->setRangeExplosion(true);
            break;
        case Object::BONUS_OBJECTS::SPEED_DOWN:
            _players.at(static_cast<char>(playerNb))->setSpeed(false);
            break;
        case Object::BONUS_OBJECTS::SPEED_UP:
            _players.at(static_cast<char>(playerNb))->setSpeed(true);
            break;
    };
    std::cout << _players.at(static_cast<char>(playerNb))->getSpeed() << std::endl;
}

bool Scene::GameScene::isCollidingObject(Position const &direction, Position const &playerPosition, Object::PLAYER_ORDER playerNb)
{
    Position newPlayerPos = playerPosition;
    newPlayerPos += direction;
    std::pair<int, int> frontPos = _gameMap->transposeFrom3Dto2D(newPlayerPos);
    std::pair<int, int> actualPos = _gameMap->transposeFrom3Dto2D(playerPosition);

    try {
        _bonus.at(actualPos.second).at(actualPos.first);
        AwardBonus(playerNb, _bonus.at(actualPos.second).at(actualPos.first)->getMapObject());
        _bonus.at(actualPos.second).erase(actualPos.first);
        if (_bonus.at(actualPos.second).empty())
            _bonus.erase(actualPos.second);
    }
    catch (std::out_of_range const &) {}

    for (auto &bomb : _bombs) {
        std::pair<int, int> bombPos = _gameMap->transposeFrom3Dto2D(bomb->getPosition());
        if (frontPos.first == bombPos.first && frontPos.second == bombPos.second && bomb->getPlayer() == playerNb) {
            if (!bomb->getCollide())
                return false;
            return true;
        }
        else
            bomb->setCollide(true);
    }
    return false;
}

void Scene::GameScene::handleBombs()
{
    for (std::size_t bombPos = 0; bombPos < _bombs.size(); bombPos++) {
            if (_bombs.at(bombPos)->checkIfShouldExplode()) {
                _players.at(static_cast<int>(_bombs.at(bombPos)->getPlayer()))->setAlreadyPlacedBombs(false);
                exploseBomb(_bombs.at(bombPos)->getPosition(), _bombs.at(bombPos)->getRange());
                _bombs.erase(_bombs.begin() + bombPos);
            }
        }
}

void Scene::GameScene::handleButtons()
{
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
}

void Scene::GameScene::handlePlayers()
{
    bool moving = false;
    int index = 0;

    _settings->getPlayerActionsPressed().at(index);
    for (auto &[playerIndex, player] : _players) {
        moving = false;
        std::map<PlayerAction, bool> tmp = _settings->getPlayerActionsPressed().at(index);
        for (auto &[action, isPressed] : tmp) {
            if (isPressed && player->isAlive()) {
                if (action == PlayerAction::Drop && player->getAlreadyPlacedBombs() < player->getRangeBomb())
                    placeBomb(player->getPosition(), player->getLifeTimeBombs(), player->getRangeExplosion(), static_cast<Object::PLAYER_ORDER>(index));
                else if (_gameMap->isColliding(_collisionCondition.at(action), player->getPosition()) == Object::MAP_OBJECTS::EMPTY && !isCollidingObject(_collisionCondition.at(action), player->getPosition(), static_cast<Object::PLAYER_ORDER>(index))) {
                    player->move(_actionMap.at(action).first, _actionMap.at(action).second);
                    moving = true;
                }
            }
        }
        if (!moving)
            player->animation(1);
        index++;
    }
}

Scene::Scenes Scene::GameScene::handleEvent()
{
    _nextScene = Scene::Scenes::GAME;
    if (!_isPaused) {
        handleWin();
        handlePlayers();
        handleBombs();
    } else {
        _nextScene = _pauseScene->handleEvent();
    }
    handlePause();
    handleButtons();
    return _nextScene;
}

void Scene::GameScene::handlePause()
{
    std::map<Action, bool> tmp = _settings->getActionPressed();
    if (tmp[Action::Previous] == true) {
        _isPaused = !_isPaused;
    }
}

void Scene::GameScene::placeBomb(Position pos, float lifetime, std::size_t range, Object::PLAYER_ORDER playerNb)
{
    bool blockTooked = false;
    std::pair<int, int> pairPos = _gameMap->transposeFrom3Dto2D(pos);
    Position newPos = {static_cast<float>(pairPos.first * static_cast<int>(_gameMap->getBlockSize())), pos.getY(), static_cast<float>(pairPos.second * static_cast<int>(_gameMap->getBlockSize()))};

    for (auto &bomb : _bombs) {
        if (bomb->getPosition() == newPos)
            blockTooked = true;
    }
    if (!blockTooked) {
        _players.at(static_cast<char>(playerNb))->setAlreadyPlacedBombs(true);
        _bombs.emplace_back(std::make_unique<Object::Bomb>(std::make_pair<std::string, std::string>("Ressources/models/bomb/bomb.obj", "Ressources/models/bomb/bomb.png"), newPos, playerNb, lifetime, range, Object::MAP_OBJECTS::BOMB));
    }
}

void Scene::GameScene::placeBonus(std::pair<int, int> position, std::size_t percentageDrop)
{
    static std::map<Object::BONUS_OBJECTS, std::pair<std::string, std::string>> bonusMap = {
        {Object::BONUS_OBJECTS::BOMB_DOWN, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/bomb_down.png"}},
        {Object::BONUS_OBJECTS::BOMB_UP, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/bomb_up.png"}},
        {Object::BONUS_OBJECTS::FIRE_DOWN, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/fire_down.png"}},
        {Object::BONUS_OBJECTS::FIRE_UP, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/fire_up.png"}},
        {Object::BONUS_OBJECTS::SPEED_DOWN, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/speed_down.png"}},
        {Object::BONUS_OBJECTS::SPEED_UP, {"Ressources/models/bonus/speedup.obj", "Ressources/models/bonus/textures/speed_up.png"}},
    };
    Position tempPos = {static_cast<float>(position.first * _gameMap->getBlockSize()), 0.0f, static_cast<float>(position.second * _gameMap->getBlockSize())};

    std::size_t randomNumber = 1 + (rand() % 100);
    std::size_t randomBonus = 1 + (rand() % bonusMap.size());

    if (randomNumber >= 1 && randomNumber <= percentageDrop) {
        std::pair<int, int> finalPos = _gameMap->transposeFrom3Dto2D(tempPos);
        try {
            _bonus.at(finalPos.second).emplace(finalPos.first, std::make_unique<Object::Bonus>(bonusMap.at(static_cast<Object::BONUS_OBJECTS>(randomBonus)), tempPos, static_cast<Object::BONUS_OBJECTS>(randomBonus), Object::MAP_OBJECTS::BONUS));
        }
        catch (std::out_of_range const &) {
            _bonus.emplace(finalPos.second, std::map<int, std::unique_ptr<Object::Bonus>>());
            _bonus.at(finalPos.second).emplace(finalPos.first, std::make_unique<Object::Bonus>(bonusMap.at(static_cast<Object::BONUS_OBJECTS>(randomBonus)), tempPos, static_cast<Object::BONUS_OBJECTS>(randomBonus), Object::MAP_OBJECTS::BONUS));
        }
    }
}

void Scene::GameScene::checkIfPlayerIsInRange(std::pair<int, int> const &explosionPos)
{
    std::pair<int, int> playerPos;
    for (auto &[index, player] : _players) {
        playerPos = _gameMap->transposeFrom3Dto2D(player->getPosition());
        if (playerPos == explosionPos)
            player->die();
    }
}

void Scene::GameScene::exploseBomb(Position const &position, int radius)
{
    std::pair<int, int> blockPosition = _gameMap->transposeFrom3Dto2D(position);
    std::vector<bool> alreadyDestroyed = { false, false, false, false };
    Position blockToPlace;
    std::vector<std::pair<int, int>> target = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::size_t index = 0;

    srand(time(NULL));
    checkIfPlayerIsInRange(blockPosition);

    for (std::size_t bombRange = 1; bombRange < radius + 1; bombRange++) {
        index = 0;
        for (auto &[x, y] : target) {
            if ((blockPosition.second + (y * bombRange)) > 0 && (blockPosition.second + (y * bombRange)) < _gameMap->getMapPositionsObjects().size())
                if ((blockPosition.first + (x * bombRange)) > 0 && (blockPosition.first + (x * bombRange)) < _gameMap->getMapPositionsObjects().at(blockPosition.second + (y * bombRange)).size()) {
                    if (_gameMap->getMapPositionsObjects().at(blockPosition.second + (y * bombRange)).at(blockPosition.first + (x * bombRange))->getType() == Object::MAP_OBJECTS::WALL_MIDDLE)
                        alreadyDestroyed.at(index) = true;
                    blockToPlace = {static_cast<float>((blockPosition.first +  (x * bombRange)) * _gameMap->getBlockSize()), 0, static_cast<float>((blockPosition.second +(y * bombRange)) * _gameMap->getBlockSize())};
                    if (_gameMap->getMapPositionsObjects().at(blockPosition.second + (y * bombRange)).at(blockPosition.first + (x * bombRange))->getType() == Object::MAP_OBJECTS::BOX && !alreadyDestroyed.at(index)) {
                        _gameMap->placeObjectInMap<Object::Block>({blockPosition.first + (x * bombRange), blockPosition.second + (y * bombRange)}, std::make_shared<Object::Block>(_gameMap->getMapModels().at(8), _gameMap->getMapTextures().at(10), blockToPlace, Object::MAP_OBJECTS::EMPTY));
                        alreadyDestroyed.at(index) = true;
                        placeBonus({blockPosition.first + (x * bombRange), blockPosition.second + (y * bombRange)}, _percentageBonusDrop);
                    }
                    if (!alreadyDestroyed.at(index))
                        checkIfPlayerIsInRange(_gameMap->transposeFrom3Dto2D(blockToPlace));
                }
            index++;
        }
    }
}

void Scene::GameScene::handleWin()
{
    std::size_t nbPlayersAlive = 0;

    for (auto &player : _players) {
        if (player.second->isAlive())
            nbPlayersAlive++;
    }
    if (nbPlayersAlive == 1)
        _endGame = true;

    if (_endGame == true) {
        save();
        _nextScene = Scene::Scenes::END_GAME;
    }
}

static float getInversedTime(float second)
{
    return ((second - 60) * -1);
}

void Scene::GameScene::printTimer()
{
    float seconds;

    seconds = getInversedTime(_clockGame.getElapsedTime() / 1000);
    if (_actualMinutes == 0 && std::to_string(static_cast<int>(seconds)) == "0") {
        _endGame = true;
    }
    if (seconds == 0) {
        _actualMinutes -= 1;
        _clockGame.restart();
    }
    if (std::to_string(static_cast<int>(seconds)).size() == 1)
        _texts.at(0)->setText(std::to_string(_actualMinutes) + ":0" + std::to_string(static_cast<int>(seconds)));
    else
        _texts.at(0)->setText(std::to_string(_actualMinutes) + ":" + std::to_string(static_cast<int>(seconds)));
}

void Scene::GameScene::setCameraVue()
{
    if (_3dcameraVue) {
        _settings->getCamera()->setPosition({(_mapSize.x * 10) / 2, (_mapSize.x * 5) * 3, _mapSize.x * 10});
        _settings->getCamera()->setTarget({(_mapSize.x * 10) / 2, 0, (_mapSize.x * 10) / 2});
    } else {
        _settings->getCamera()->setPosition({(_mapSize.x * 10) / 2, (_mapSize.x * 5) * 4, ((_mapSize.x * 10) / 2) + 1});
        _settings->getCamera()->setTarget({(_mapSize.x * 10) / 2, 0, (_mapSize.x * 10) / 2});
    }
}

void Scene::GameScene::draw()
{
    _backgroundImage.at(0)->draw();
    printTimer();
    setCameraVue();
    _settings->getCamera()->startMode3D();
    _gameMap->draw();

    for (auto &[index, player] : _players)
        if (player->isAlive())
            player->draw();

    for (auto &[line, bonus] : _bonus)
        for (auto &[col, bonusObject] : bonus)
            bonusObject->draw();

    for (auto &bomb : _bombs)
        bomb->draw();

    _settings->getCamera()->endMode3D();
    if (_isPaused)
        _pauseScene->draw();

    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
}

void Scene::GameScene::save()
{
    std::ofstream o("Save/Games/gameSave.json");
    nlohmann::json saveData;
    nlohmann::json gameData;

    _gameMap->save();
    gameData["time"] = 0.0;
    gameData["map"] = _mapFile;
    gameData["attributes"] = _defaultAttributes;
    saveData["game-data"] = gameData;
    for (auto &[playerIndex, player] : _players)
        saveData["player-" + std::to_string(static_cast<int>(playerIndex))] = player->save();
    o << std::setw(4) << saveData << std::endl;
}