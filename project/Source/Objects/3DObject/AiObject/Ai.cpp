/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Ai
*/

#include "Ai.hpp"

Object::Ai::Ai(Object::PLAYER_ORDER id, std::shared_ptr<Object::Player> const &player, std::shared_ptr<Object::Map> const &gameMap) : _id(id), _aiPlayer(player), _gameMap(gameMap)
{
    _margin = 5.0;
    _collisionCondition = {
        {PlayerAction::MoveLeft, {-_margin, 0, 0}},
        {PlayerAction::MoveRight, {_margin, 0, 0}},
        {PlayerAction::MoveUp, {0, 0, -_margin}},
        {PlayerAction::MoveDown, {0, 0, _margin}},
        {PlayerAction::Drop, {0, 0, 0}}
    };
}

Object::Ai::~Ai()
{
}

static int escapingTheBomb(int action)
{
    int tmp;

    switch (action) {
        case 0:
            tmp = 1;
            break;
        case 1:
            tmp = 0;
            break;
        case 2:
            tmp = 3;
            break;
        case 3:
            tmp = 2;
            break;
    }
    return tmp;
}


void Object::Ai::handleEvent(std::map<PlayerAction, bool> &aiAction, std::vector<std::unique_ptr<Object::Bomb>> const &bombs)
{
    for (auto &[action, isPressed] : aiAction) {
        aiAction.at(action) = false;
    }

    _forbiddenCells = stockForbiddenCells(bombs);

    if (checkAiIsSafe())
        _isSafe = true;

    if (_isSafe && !validDir(static_cast<PlayerAction>(_actionMove)))
        _isMoving = false;

    if (!_isMoving) {
        _isMoving = true;
        _possibleDirection = getPossibleDir();
        _actionMove = rand() % _possibleDirection.size();
    } else {
        if (_gameMap->isColliding(_collisionCondition.at(static_cast<PlayerAction>(_possibleDirection.at(_actionMove))), _aiPlayer->getPosition()) == Object::MAP_OBJECTS::EMPTY) {

            if (!_isSafe) {
                aiAction.at(static_cast<PlayerAction>(_possibleDirection.at(_actionMove))) = true;
                _isMoving = true;
            } else {
                if (validDir(static_cast<PlayerAction>(_actionMove))) {
                    aiAction.at(static_cast<PlayerAction>(_possibleDirection.at(_actionMove))) = true;
                    _isMoving = true;
                } else
                    _isMoving = false;
            }
        } else {
            _isMoving = false;
            if (_isSafe && _gameMap->isColliding(_collisionCondition.at(static_cast<PlayerAction>(_possibleDirection.at(_actionMove))), _aiPlayer->getPosition()) == Object::MAP_OBJECTS::BOX   && _aiPlayer->getAlreadyPlacedBombs() < _aiPlayer->getRangeBomb()) {
                aiAction.at(PlayerAction::Drop) = true;
                _isSafe = false;
                _actionMove = escapingTheBomb(_actionMove);
                _isMoving = true;
            }
        }
    }
}

std::vector<PlayerAction> Object::Ai::getPossibleDir()
{
    const std::vector<PlayerAction> all_actions = {PlayerAction::MoveLeft, PlayerAction::MoveRight, PlayerAction::MoveUp, PlayerAction::MoveDown};
    std::vector<PlayerAction> dirs;

    for (auto &action : all_actions) {
        bool isPossibleDir = true;
        Position temppos = _aiPlayer->getPosition();
        temppos += _collisionCondition.at(action);
        std::pair<int, int> newAiPos = _gameMap->transposeFrom3Dto2D(temppos);

        dirs.emplace_back(action);
    }
    return dirs;
}

std::vector<std::pair<int, int>> Object::Ai::stockForbiddenCells(std::vector<std::unique_ptr<Object::Bomb>> const &bombs)
{
    const std::vector<std::pair<int, int>> target = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<std::pair<int, int>> aiForbiddenCells;
    std::pair<int, int> aiPos = _gameMap->transposeFrom3Dto2D(_aiPlayer->getPosition());
    Position blockToPlace;

    for (auto &bomb : bombs) {
        if (bomb->getPlayer() == static_cast<Object::PLAYER_ORDER>(_id)) {
            std::pair<int, int> blockPosition = _gameMap->transposeFrom3Dto2D(bomb->getPosition());

            blockToPlace = {static_cast<float>(blockPosition.first * _gameMap->getBlockSize()), 0, static_cast<float>(blockPosition.second * _gameMap->getBlockSize())};
            aiForbiddenCells.emplace_back(_gameMap->transposeFrom3Dto2D(blockToPlace));

            for (auto &[x, y] : target) {
                for (std::size_t bombRangeIndex = 1; bombRangeIndex <= bomb->getRange(); bombRangeIndex++) {
                    if ((blockPosition.second + y * bombRangeIndex) > 0 && (blockPosition.second + y * bombRangeIndex) < _gameMap->getMapPositionsObjects().size()) {
                        if ((blockPosition.first + x * bombRangeIndex) > 0 && (blockPosition.first + x * bombRangeIndex) < _gameMap->getMapPositionsObjects().at(blockPosition.second + y * bombRangeIndex).size()) {
                            blockToPlace = {static_cast<float>((blockPosition.first + x * bombRangeIndex) * _gameMap->getBlockSize()), 0, static_cast<float>((blockPosition.second + y * bombRangeIndex) * _gameMap->getBlockSize())};

                            aiForbiddenCells.emplace_back(_gameMap->transposeFrom3Dto2D(blockToPlace));
                        }
                    }
                }
            }
        }
    }
    return aiForbiddenCells;
}

bool Object::Ai::checkAiIsSafe()
{
    std::pair<int, int> aiPos = _gameMap->transposeFrom3Dto2D(_aiPlayer->getPosition());

    for (auto &cell : _forbiddenCells) {
        if (cell == aiPos)
            return false;
    }
    return true;
}

bool Object::Ai::checkAiIsSafe(std::pair<int, int> newPosAi)
{
    for (auto &cell : _forbiddenCells) {
        if (cell == newPosAi)
            return false;
    }
    return true;
}

bool Object::Ai::validDir(PlayerAction action)
{
    Position temppos = _aiPlayer->getPosition();

    temppos += _collisionCondition.at(action);
    std::pair<int, int> newAiPos = _gameMap->transposeFrom3Dto2D(temppos);

    if (!checkAiIsSafe(newAiPos))
        return false;
    return true;
}
