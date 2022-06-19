/*
** EPITECH PROJECT, 2022
** project
** File description:
** GameScene
*/

#include <nlohmann/json.hpp>

#include <functional>

#include "tools.hpp"
#include "GameScene.hpp"

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
    _startingGameTexts = loadObjects<Object::Text>("Conf/Scenes/GameScene/startingGameText.json");
    _buttons = loadObjects<Object::Button>("Conf/Scenes/GameScene/button.json");
    _playerParameters = loadObjects<Object::Text>("Conf/Scenes/GameScene/parameters.json");
    _endingGameText = loadObjects<Object::Text>("Conf/Scenes/GameScene/endingGameText.json");
    _buttons.at(0)->setCallBack(std::bind(&Scene::GameScene::changeCameraView, this));

    _nextScene = Scene::Scenes::GAME;
    _cinematicCamera = true;
    _isPaused = true;
    _3dcameraVue = false;
    _elapsedTime = 0;
    _timePerRound = 1;
    _endSet = false;
    _endingGameText.at(0)->disable();

    _margin = 5.0;
    _collisionCondition = {
        {PlayerAction::MoveLeft, {-_margin, 0, 0}},
        {PlayerAction::MoveRight, {_margin, 0, 0}},
        {PlayerAction::MoveUp, {0, 0, -_margin}},
        {PlayerAction::MoveDown, {0, 0, _margin}},
        {PlayerAction::Drop, {0, 0, 0}}
    };
    _timeBeforeBombExplosion = 3;

    _pauseScene = std::make_unique<Scene::PauseScene>(settings, gameSettings, std::vector<std::function<void(void)>>{std::bind(&Scene::GameScene::resumeGame, this), std::bind(&Scene::GameScene::applyGameParams, this), std::bind(&Scene::GameScene::save, this)});

    _percentageBonusDrop = 60;
    _percentageBoxDrop = 90;

    _gameMap = std::make_shared<Object::Map>(_models, _textures);
    _gameSettings->setPercentageBoxDrop(_percentageBoxDrop);

    _defaultAttributes = {{"bombRange", {1, 3}},
        {"explosionRange", {1, 6}},
        {"speed", {0.5, 0.8}}};

    for (std::size_t index = 0; index != 4; index++)
        _players.emplace(static_cast<Object::PLAYER_ORDER>(index), std::make_unique<Object::Player>(_models.at(index), _textures.at(index + 1), _animations.at(0), 1, (Position){0, 0, 0}, Object::MAP_OBJECTS::PLAYER));
    _actualSet = 1;
}

Scene::GameScene::~GameScene()
{
    for (auto &model : _models)
        model.unload();
    for (auto &texture : _textures)
        texture.unload();
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
    _textures.emplace_back("Ressources/models/player/pink.png");
    _textures.emplace_back("Ressources/models/player/white.png");

    /* BLOCKS */
    _models.emplace_back("Ressources/models/block/stone/box.obj");
    _models.emplace_back("Ressources/models/block/dirt/wall_side.obj");
    _models.emplace_back("Ressources/models/block/stone/wall_side.obj");
    _models.emplace_back("Ressources/models/block/dirt/box.obj");
    _models.emplace_back(""); // For empty block
    _models.emplace_back("Ressources/models/explosion/explosion.iqm");

    _textures.emplace_back("Ressources/models/block/stone/box.png");
    _textures.emplace_back("Ressources/models/block/dirt/wall_side.png");
    _textures.emplace_back("Ressources/models/block/stone/wall_side.png");
    _textures.emplace_back("Ressources/models/block/dirt/box.png");
    _textures.emplace_back(""); // For empty block
    _textures.emplace_back("Ressources/models/explosion/Fire_baseColor.png");
}

void Scene::GameScene::restartSet()
{
    _playerSkin = _gameSettings->getPlayerSkins();
    _startingGameTexts.at(0)->setText("3");
    std::vector<Position> playerPositions;

    _ai.clear();
    _endSet = false;
    _endingGameText.at(0)->disable();
    for (std::size_t player = _gameSettings->getNbPlayers(); player < 4; player++)
        _ai.emplace(static_cast<Object::PLAYER_ORDER>(player), std::make_shared<Object::Ai>(static_cast<Object::PLAYER_ORDER>(player), _players.at(static_cast<Object::PLAYER_ORDER>(player)), _gameMap));
    _3dcameraVue = false;
    _nextScene = Scene::Scenes::GAME;
    _cameraClock.start();
    _gameClock.reset();
    _explosions.clear();
    _isPaused = true;
    _actualSet += 1;
    _bombs.clear();
    _gameMap->clearMap();
    _gameMap->process(_gameSettings->getMapPath());
    _mapStatistics.clear();
    _timePerRound = _gameSettings->getTimePerRound();
    _elapsedTime = _gameSettings->getGameTime();
    _percentageBoxDrop = _gameSettings->getPercentageBoxDrop();
    if (_gameSettings->IsEnabledBonus())
        _percentageBonusDrop = 60;
    else
        _percentageBonusDrop = 0;
    playerPositions = _gameMap->getMapCorners(_gameSettings->getMapSize().first, _gameSettings->getMapSize().second);
    for (auto &[index, player] : _players) {
        player->reset();
        player->setPosition(playerPositions.at(static_cast<int>(index)));
        player->setSkin(_textures.at(_playerSkin.at(static_cast<int>(index))));
        player->setDefaultAttributes(_gameSettings->getDefaultAttributes());
    }
    for (std::size_t i = 0; i < _players.size(); i++) {
        std::string pathToImage = "Conf/Scenes/GameScene/icons/player" + std::to_string(i + 1) + ".json";
        std::string pathToStars = "Conf/Scenes/GameScene/sets/player" + std::to_string(i + 1) + ".json";

        _setsIcons.emplace_back(loadObjects<Object::Image>(pathToStars));
        _playersIcons.emplace_back(loadObjects<Object::Image>(pathToImage));
    }
    setCameraView();
    setBombToPause(false);
    _cinematicCamera = true;
    _settings->getCamera()->setPosition({(_gameSettings->getMapSize().first * _gameMap->getBlockSize()) / 2, 1, ((_gameSettings->getMapSize().second * _gameMap->getBlockSize()) / 2)});
}

void Scene::GameScene::applyGameParams()
{
    _settings->stopMusic(MusicsEnum::Game);
    _settings->playMusic(MusicsEnum::Game);
    restartSet();
    for (auto &[index, player] : _players)
        player->setWon(0);
    _actualSet = 1;
}

void Scene::GameScene::handleCinematicCamera()
{
    long long int timer = _cameraClock.getElapsedTime();

    if (_settings->getCamera()->getCamera().position.y < (_gameSettings->getMapSize().first * 5) * 4) {
        _settings->getCamera()->setPosition({(_gameSettings->getMapSize().first * _gameMap->getBlockSize()) / 2, static_cast<float>(timer / 10), ((_gameSettings->getMapSize().second * _gameMap->getBlockSize()) / 2) + 1});
    } else {
        _cinematicCamera = false;
        resumeGame();
    }
    std::cout << timer << std::endl;
    if (timer > 500 && timer < 1000)
        _startingGameTexts.at(0)->setText("2");
    if (timer > 1001)
        _startingGameTexts.at(0)->setText("1");
    if (timer > 1500) {
        _startingGameTexts.at(0)->setPosition(Position(820, 500, 0));
        _startingGameTexts.at(0)->setText("GO !!");
    }
}

void Scene::GameScene::loadFromSave(nlohmann::json const &jsonData)
{
    _gameSettings->loadFromJson(jsonData.at("game-data"));
    restartSet();
    for (std::size_t playerIndex = 0; playerIndex != 4; playerIndex++) {
        _players.at(static_cast<Object::PLAYER_ORDER>(playerIndex))->loadFromJson(jsonData.at("player-" + std::to_string(playerIndex)));
    }
}

void Scene::GameScene::handleBonusParameters()
{
    int textPos = 0;

    for (auto &[index, player] : _players) {
        _playerParameters.at(static_cast<int>(textPos))->setText(std::to_string(player->getRangeExplosion()) + " / " + std::to_string(player->getDefaultRangeExplosion().second));
        textPos++;
        _playerParameters.at(static_cast<int>(textPos))->setText(std::to_string(player->getAlreadyPlacedBombs()) + " / " + std::to_string(player->getRangeBomb()));
        textPos++;
        _playerParameters.at(static_cast<int>(textPos))->setText(std::to_string(static_cast<int>(player->getSpeed() * 10) - 4) + " / " + std::to_string(static_cast<int>(player->getDefaultSpeed().second * 10)  - 4));
        textPos++;
    }
}

Scene::Scenes Scene::GameScene::handleEvent()
{
    Vector2 mousePos = GetMousePosition();

    _nextScene = Scene::Scenes::GAME;
    _settings->updateMusicStream(MusicsEnum::Game);
    if (!_cinematicCamera) {
        for (auto &button: _buttons)
            button->checkHover(mousePos);
    } else
        handleCinematicCamera();
    if (!_isPaused) {
        handleWin();
        handlePlayers();
        handleBombs();
    } else {
        _nextScene = _pauseScene->handleEvent();
    }
    handleBonusParameters();
    handlePause();
    handleExplosions();
    handleTimer();
    handleSets();
    return _nextScene;
}

void Scene::GameScene::draw()
{
    for (auto &backgroundImage : _backgroundImage)
        backgroundImage->draw();
    _settings->getCamera()->startMode3D();
    _gameMap->draw();
    for (auto &[index, player] : _players) {
        if (player->isAlive())
            player->draw();
    }
    drawObjects();
    _settings->getCamera()->endMode3D();
    _cinematicCamera ? _startingGameTexts.at(0)->draw() : drawUserInterface();
}

void Scene::GameScene::handleWin()
{
    std::size_t nbPlayersAlive = 0;
    std::size_t playerIndex = 0;
    std::size_t alivePlayerIndex = 0;

    for (auto &player : _players) {
        if (player.second->isAlive()) {
            nbPlayersAlive++;
            alivePlayerIndex = playerIndex;
        }
        playerIndex++;
    }
    if (nbPlayersAlive == 1) {
        handleEndSet(alivePlayerIndex);
        for (auto &[index, player] : _players) {
            if (player->getSetsWon() == _gameSettings->getNbSets())
                _nextScene = Scene::Scenes::END_GAME;
        }
    }
}

void Scene::GameScene::handlePlayers()
{
    bool moving = false;
    std::vector<std::map<PlayerAction, bool>> playerAction = _settings->getPlayerActionsPressed();

    for (auto &[playerIndex, player] : _players) {
        moving = false;
        std::map<PlayerAction, bool> tmp = playerAction.at(static_cast<int>(playerIndex));

        if (_ai.find(playerIndex) != _ai.end())
            _ai.at(playerIndex)->handleEvent(tmp, _bombs);

        for (auto &[action, isPressed] : tmp) {
            if (isPressed && player->isAlive()) {
                if (action == PlayerAction::Drop && player->getAlreadyPlacedBombs() < player->getRangeBomb())
                   placeBomb(player->getPosition(), playerIndex);
                else if (_gameMap->isColliding(_collisionCondition.at(action), player->getPosition()) == Object::MAP_OBJECTS::EMPTY && !isCollidingBomb(_collisionCondition.at(action), player->getPosition(), playerIndex)) {
                    CollideObject(player->getPosition(), playerIndex);
                    player->move(_actionMap.at(action).first, _actionMap.at(action).second);
                    moving = true;
                }
            }
        }
        if (!moving)
            player->animation(1);
    }
}

void Scene::GameScene::placeBomb(Position const &pos, Object::PLAYER_ORDER playerNb)
{
    bool blockTook = false;
    std::pair<int, int> pairPos = _gameMap->transposeFrom3Dto2D(pos);
    Position newPos = {pairPos.first * _gameMap->getBlockSize(), pos.getY(), pairPos.second * _gameMap->getBlockSize()};

    _settings->playSound(SoundsEnum::BombDrop);

    for (auto &bomb : _bombs) {
        if (bomb->getPosition() == newPos)
            blockTook = true;
    }
    if (!blockTook) {
        _players.at(playerNb)->setAlreadyPlacedBombs(true);
        _bombs.emplace_back(std::make_unique<Object::Bomb>(std::make_pair<std::string, std::string>("Ressources/models/bomb/bomb.obj", "Ressources/models/bomb/bomb.png"), newPos, playerNb, _timeBeforeBombExplosion, _players.at(playerNb)->getRangeExplosion()));
    }
}

void Scene::GameScene::CollideObject(Position const &playerPosition, Object::PLAYER_ORDER playerNb)
{
    std::pair<int, int> actualPos = _gameMap->transposeFrom3Dto2D(playerPosition);

    try {
        _bonus.at(actualPos.second).at(actualPos.first);
        AwardBonus(playerNb, _bonus.at(actualPos.second).at(actualPos.first)->getMapObject());
        _bonus.at(actualPos.second).erase(actualPos.first);
        if (_bonus.at(actualPos.second).empty())
            _bonus.erase(actualPos.second);
    }
    catch (std::out_of_range const &) {}
}

void Scene::GameScene::AwardBonus(Object::PLAYER_ORDER playerNb, Object::BONUS_OBJECTS bonus)
{
    switch (bonus) {
        case Object::BONUS_OBJECTS::BOMB_DOWN:
            _players.at(playerNb)->setRangeBomb(false);
            break;
        case Object::BONUS_OBJECTS::BOMB_UP:
            _players.at(playerNb)->setRangeBomb(true);
            break;
        case Object::BONUS_OBJECTS::FIRE_DOWN:
            _players.at(playerNb)->setRangeExplosion(false);
            break;
        case Object::BONUS_OBJECTS::FIRE_UP:
            _players.at(playerNb)->setRangeExplosion(true);
            break;
        case Object::BONUS_OBJECTS::SPEED_DOWN:
            _players.at(playerNb)->setSpeed(false);
            break;
        case Object::BONUS_OBJECTS::SPEED_UP:
            _players.at(playerNb)->setSpeed(true);
            break;
    };
}

void Scene::GameScene::handleBombs()
{
    for (std::size_t bombPos = 0; bombPos < _bombs.size(); bombPos++) {
        if (_bombs.at(bombPos)->checkIfShouldExplode()) {
            _players.at(_bombs.at(bombPos)->getPlayer())->setAlreadyPlacedBombs(false);
            exploseBomb(_bombs.at(bombPos)->getPosition(), _bombs.at(bombPos)->getRange());
            _bombs.erase(_bombs.begin() + bombPos);
        }
    }
}

void Scene::GameScene::exploseBomb(Position const &position, int radius)
{
    std::pair<int, int> blockPosition = _gameMap->transposeFrom3Dto2D(position);
    std::vector<bool> alreadyDestroyed = { false, false, false, false };
    Position blockToPlace;
    std::vector<std::pair<int, int>> target = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::size_t index = 0;

    _settings->playSound(SoundsEnum::BombExplosion);
    placeExplosions(_gameClock.getElapsedTime(), position);
    _gameMap->placeObjectInMap<Object::Block>(blockPosition, std::make_shared<Object::Block>(_gameMap->getMapModels().at(9), _gameMap->getMapTextures().at(13), position, Object::MAP_OBJECTS::EXPLOSION, _gameMap->getBlockSize()));
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
                        _gameMap->placeObjectInMap<Object::Block>({blockPosition.first + (x * bombRange), blockPosition.second + (y * bombRange)}, std::make_shared<Object::Block>(_gameMap->getMapModels().at(9), _gameMap->getMapTextures().at(13), blockToPlace, Object::MAP_OBJECTS::EXPLOSION, _gameMap->getBlockSize()));
                        placeExplosions(_gameClock.getElapsedTime(), blockToPlace);
                        alreadyDestroyed.at(index) = true;
                        placeBonus({blockPosition.first + (x * bombRange), blockPosition.second + (y * bombRange)}, _percentageBonusDrop);
                    }
                    if (_gameMap->getMapPositionsObjects().at(blockPosition.second + (y * bombRange)).at(blockPosition.first + (x * bombRange))->getType() == Object::MAP_OBJECTS::EMPTY && !alreadyDestroyed.at(index)) {
                        _gameMap->placeObjectInMap<Object::Block>({blockPosition.first + (x * bombRange), blockPosition.second + (y * bombRange)}, std::make_shared<Object::Block>(_gameMap->getMapModels().at(9), _gameMap->getMapTextures().at(13), blockToPlace, Object::MAP_OBJECTS::EXPLOSION, _gameMap->getBlockSize()));
                        placeExplosions(_gameClock.getElapsedTime(), blockToPlace);
                    }
                    if (!alreadyDestroyed.at(index))
                        checkIfPlayerIsInRange(_gameMap->transposeFrom3Dto2D(blockToPlace));
                }
            index++;
        }
    }
}

void Scene::GameScene::placeExplosions(float time, Position position)
{
    std::pair<int, int> tempPos = _gameMap->transposeFrom3Dto2D(position);
    _explosions.try_emplace(tempPos.first, std::map<int, float>());
    _explosions.at(tempPos.first).try_emplace(tempPos.second, _gameClock.getElapsedTime());
}

void Scene::GameScene::checkIfPlayerIsInRange(std::pair<int, int> const &explosionPos)
{
    std::pair<int, int> playerPos;
    for (auto &[index, player] : _players) {
        playerPos = _gameMap->transposeFrom3Dto2D(player->getPosition());
        if (playerPos == explosionPos) {
            player->die();
        }
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

void Scene::GameScene::handlePause()
{
    std::map<Action, bool> tmp = _settings->getActionPressed();
    if (tmp.at(Action::Previous)) {
        _isPaused = !_isPaused;
        if (_gameClock.isPaused()) {
            _gameClock.unpause();
            setBombToPause(false);
        }
        else {
            _gameClock.pause();
            setBombToPause(true);
        }
    }
}

void Scene::GameScene::setBombToPause(bool pause)
{
    for (auto &bomb : _bombs)
        pause ? bomb->pause() : bomb->unpause();
}

void Scene::GameScene::handleExplosions()
{
    float timeBeforeExplosion = 1000;

    for (auto &[col, explosions]: _explosions) {
        for (auto &[line, timer] : explosions) {
            float newTimer = timer + timeBeforeExplosion;
            if (newTimer <= static_cast<float>(_gameClock.getElapsedTime())) {
                _gameMap->placeObjectInMap<Object::Block>({col, line}, std::make_shared<Object::Block>(_gameMap->getMapModels().at(8), _gameMap->getMapTextures().at(12), (Position){static_cast<float>(col * 10), 0, static_cast<float>(line * 10)}, Object::MAP_OBJECTS::EMPTY, 0.1));
                _explosions.at(col).erase(line);
            }
        }
    }
}

void Scene::GameScene::handleEndSet(std::size_t winner)
{
    long long int timer = 0;

    if (_endSet) {
        _endSetClock.start();
        while (timer < 3000) {
            timer = _endSetClock.getElapsedTime();
        }
        restartSet();
    } else {
        _players.at(static_cast<Object::PLAYER_ORDER>( winner))->setWon(1);
        for (std::size_t index = 0; index < _players.size(); index++)
            _mapStatistics.push_back({_players.at(static_cast<Object::PLAYER_ORDER>(index))->getSetsWon(), static_cast<Object::PLAYER_ORDER>(index)});
        _gameSettings->setPlayersRank(_mapStatistics);
        _settings->stopMusic(MusicsEnum::Game);
        _settings->playMusic(MusicsEnum::EndGame);
        _endingGameText.at(0)->setText(std::to_string(winner + 1) + "J Wins!");
        _endingGameText.at(0)->enable();
        _endSet = true;
    }
}

void Scene::GameScene::handleSets()
{
    _texts.at(1)->setText("Set n°" + std::to_string(_actualSet));
}

void Scene::GameScene::handleTimer()
{
    int time = _gameClock.getElapsedTime() / 1000;
    int remaningTime = _timePerRound * 60 - time - _elapsedTime;
    int minutes = remaningTime / 60;
    int seconds = remaningTime % 60;

    if (remaningTime <= 0)
        restartSet();
    if (seconds < 10)
        _texts.at(0)->setText(std::to_string(minutes) + ":0" + std::to_string(seconds));
    else
        _texts.at(0)->setText(std::to_string(minutes) + ":" + std::to_string(seconds));
}

bool Scene::GameScene::isCollidingBomb(Position const &direction, Position const &playerPosition, Object::PLAYER_ORDER playerNb)
{
    Position newPlayerPos = playerPosition;
    newPlayerPos += direction;
    std::pair<int, int> frontPos = _gameMap->transposeFrom3Dto2D(newPlayerPos);

    for (auto &bomb : _bombs) {
        std::pair<int, int> bombPos = _gameMap->transposeFrom3Dto2D(bomb->getPosition());
        if (frontPos.first == bombPos.first && frontPos.second == bombPos.second && bomb->getPlayer() != playerNb)
            return true;
    }
    return false;
}

void Scene::GameScene::drawUserInterface()
{
    for (auto &image : _images)
        image->draw();
    for (std::size_t index = 0; index < _players.size(); index++) {
        if (_players.at(static_cast<Object::PLAYER_ORDER>(index))->isAlive())
            _playersIcons.at(index).at(_playerSkin.at(index))->draw();
        else
            _playersIcons.at(index).at(_playerSkin.at(index) + 8)->draw();
        for (std::size_t nbSets = 0; nbSets < _gameSettings->getNbSets(); nbSets++) {
            if (nbSets < _players.at(static_cast<Object::PLAYER_ORDER>(index))->getSetsWon())
                _setsIcons.at(index).at(nbSets + 5)->draw();
            else
                _setsIcons.at(index).at(nbSets)->draw();
        }
    }
    for (auto &text : _texts)
        text->draw();
    for (auto &parameter : _playerParameters)
        parameter->draw();
    if (_3dcameraVue)
        _buttons.at(1)->draw();
    else
        _buttons.at(0)->draw();
    if (_isPaused && !_cinematicCamera)
        _pauseScene->draw();
    if (_endSet)
        _endingGameText.at(0)->draw();
}

void Scene::GameScene::drawObjects()
{
    for (auto &[line, bonus] : _bonus)
        for (auto &[col, bonusObject] : bonus) {
            std::pair<int, int> tempPos = _gameMap->transposeFrom3Dto2D(bonusObject->getPosition());
            if (_gameMap->getMapPositionsObjects().at(tempPos.second).at(tempPos.first)->getType() == Object::MAP_OBJECTS::EMPTY)
                bonusObject->draw();
    }
    for (auto &bomb : _bombs)
        bomb->draw();
}

void Scene::GameScene::resumeGame()
{
    _gameClock.unpause();
    setBombToPause(false);
    _isPaused = false;
}

void Scene::GameScene::save()
{
    std::ofstream fileToWrite("Save/Games/Params/gameSave" + std::to_string(_settings->getSaveIndex()) + ".json");
    nlohmann::json saveData;
    nlohmann::json gameData;

    if (!fileToWrite.is_open())
        throw Error::FileError("File Save/Games/Params/gameSave" + std::to_string(_settings->getSaveIndex()) + ".json Failed to open");
    _gameMap->save("Save/Games/Maps/Savemap" + std::to_string(_settings->getSaveIndex()) + ".map");
    _gameClock.unpause();
    std::cout <<_timePerRound * 60 - (_gameClock.getElapsedTime() / 1000)<<std::endl;
    gameData["time"] = _gameClock.getElapsedTime() / 1000;
    gameData["timePerRound"] = _timePerRound;
    gameData["map"] = "Save/Games/Maps/Savemap" + std::to_string(_settings->getSaveIndex()) + ".map";
    gameData["mapSize"] = _gameSettings->getMapSize();
    gameData["playerSkins"] = _gameSettings->getPlayerSkins();
    gameData["nbPlayers"] = _gameSettings->getNbPlayers();
    gameData["attributes"] = _defaultAttributes;
    gameData["nbSets"] = _gameSettings->getNbSets();
    gameData["actualSet"] = _actualSet;
    saveData["game-data"] = gameData;
    for (auto &[playerIndex, player] : _players)
        saveData["player-" + std::to_string(static_cast<int>(playerIndex))] = player->save();
    fileToWrite << std::setw(4) << saveData << std::endl;
}

void Scene::GameScene::changeCameraView()
{
    _3dcameraVue = !_3dcameraVue;
    setCameraView();
}

void Scene::GameScene::setCameraView()
{
    std::pair<float, float> mapSize = _gameSettings->getMapSize();

    if (!_cinematicCamera) {
        if (_3dcameraVue) {
            _settings->getCamera()->setPosition({(mapSize.first * _gameMap->getBlockSize()) / 2, (mapSize.first * 5) * 3, mapSize.second * _gameMap->getBlockSize()});
        } else {
            _settings->getCamera()->setPosition({(mapSize.first * _gameMap->getBlockSize()) / 2, (mapSize.first * 5) * 4, ((mapSize.second * _gameMap->getBlockSize()) / 2) + 1});
        }
    }
    _settings->getCamera()->setTarget({(mapSize.first * _gameMap->getBlockSize()) / 2, 0, (mapSize.first * _gameMap->getBlockSize()) / 2});
}
