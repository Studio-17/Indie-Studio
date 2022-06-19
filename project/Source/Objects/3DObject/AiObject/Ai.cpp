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

void Object::Ai::handleEvent(std::map<PlayerAction, bool> &aiAction, std::vector<std::unique_ptr<Object::Bomb>> const &bombs)
{
    for (auto &[action, isPressed] : aiAction) {
        aiAction.at(action) = false;
    }

    _forbiddenCells = stockForbiddenCells(bombs);

    if (!checkAiIsSafe())
        _isSafe = false;
    else
        _isSafe = true;

    if (!_isMoving) {
        _isMoving = true;
        _possibleDirection = getPossibleDir();
        _actionMove = rand() % _possibleDirection.size();
    }

    if (!_isSafe) {
        switch (_gameMap->isColliding(_collisionCondition.at(static_cast<PlayerAction>(_possibleDirection.at(_actionMove))), _aiPlayer->getPosition())) {
            case Object::MAP_OBJECTS::EMPTY:
                aiAction.at(static_cast<PlayerAction>(_actionMove)) = true;
                _isMoving = true;
                break;
            case Object::MAP_OBJECTS::WALL_SIDE:
                _isMoving = false;
                break;
            case Object::MAP_OBJECTS::WALL_MIDDLE:
                _isMoving = false;
                break;

        }
    }
    if (_gameMap->isColliding(_collisionCondition.at(static_cast<PlayerAction>(_possibleDirection.at(_actionMove))), _aiPlayer->getPosition()) == Object::MAP_OBJECTS::EMPTY) {
        aiAction.at(static_cast<PlayerAction>(_possibleDirection.at(_actionMove))) = true;
        _isMoving = true;
    } else {
        _isMoving = false;
        if (_isSafe && _gameMap->isColliding(_collisionCondition.at(static_cast<PlayerAction>(_possibleDirection.at(_actionMove))), _aiPlayer->getPosition()) == Object::MAP_OBJECTS::BOX && _aiPlayer->getAlreadyPlacedBombs() < _aiPlayer->getRangeBomb()) {
            aiAction.at(PlayerAction::Drop) = true;
            _isSafe = false;
            switch (_actionMove) {
                case 0:
                    _actionMove = 1;
                    break;
                case 1:
                    _actionMove = 0;
                    break;
                case 2:
                    _actionMove = 3;
                    break;
                case 3:
                    _actionMove = 2;
                    break;
            }
            _isMoving = true;
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
        }
    }
    return aiForbiddenCells;
}

bool Object::Ai::checkAiIsSafe()
{
    std::pair<int, int> aiPos = _gameMap->transposeFrom3Dto2D(_aiPlayer->getPosition());

    for (auto &cell : _forbiddenCells) {
        if (cell.first == aiPos.first || cell.second == aiPos.second)
            return false;
    }
    return true;
}
