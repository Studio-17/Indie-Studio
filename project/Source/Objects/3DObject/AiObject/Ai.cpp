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

void Object::Ai::handleEvent(std::map<PlayerAction, bool> &aiAction)
{
    for (auto &[action, isPressed] : aiAction) {
        aiAction.at(action) = false;
    }

    if (!_isMoving) {
        _possibleDirection = getPossibleDir();
        _actionMove = rand() % _possibleDirection.size();
    }

    if (_gameMap->isColliding(_collisionCondition.at(static_cast<PlayerAction>(_possibleDirection.at(_actionMove))), _aiPlayer->getPosition()) == Object::MAP_OBJECTS::EMPTY) {
        aiAction.at(static_cast<PlayerAction>(_possibleDirection.at(_actionMove))) = true;
        _isMoving = true;
    } else {
        _isMoving = false;
        // if (ai->getIsSafe() && _gameMap->isColliding(_collisionCondition.at(static_cast<PlayerAction>(ai->getAiPossibleDirections().at(ai->getActionMove()))), ai->getPosition()) == Object::MAP_OBJECTS::BOX) {
        //     aiAction.at(PlayerAction::Drop) = true;
        // }
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

        // if (_gameMap->isColliding(_collisionCondition.at(action), temppos) == Object::MAP_OBJECTS::EMPTY) {
            // if (ai->getIsSafe()) {
            //     // for (auto &cell : ai->getAiForbiddenCells()) {
            //     //     if (cell == newAiPos)
            //     //         isPossibleDir = false;
            //     // }
            //     if (!checkAiIsSafe(ai, newAiPos))
            //         isPossibleDir = false;
            // }
        // }

        if (isPossibleDir)
            dirs.emplace_back(action);
    }
    return dirs;
}

// std::vector<std::pair<int, int>> Object::Ai::stockForbiddenCells()
// {
//     const std::vector<std::pair<int, int>> target = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
//     std::vector<std::pair<int, int>> aiForbiddenCells;
//     std::pair<int, int> aiPos = _gameMap->transposeFrom3Dto2D(_aiPlayer->getPosition());
//     Position blockToPlace;

//     for (auto &bomb : _bombs) {
//         if (bomb->getPlayer() == static_cast<Object::PLAYER_ORDER>(_id)) {
//             std::pair<int, int> blockPosition = _gameMap->transposeFrom3Dto2D(bomb->getPosition());

//             blockToPlace = {static_cast<float>(blockPosition.first * _gameMap->getBlockSize()), 0, static_cast<float>(blockPosition.second * _gameMap->getBlockSize())};
//             aiForbiddenCells.emplace_back(_gameMap->transposeFrom3Dto2D(blockToPlace));

//             for (auto &[x, y] : target) {
//                 if ((blockPosition.second + y) > 0 && (blockPosition.second + y) < _gameMap->getMapPositionsObjects().size()) {
//                     if ((blockPosition.first + x) > 0 && (blockPosition.first + x) < _gameMap->getMapPositionsObjects().at(blockPosition.second + y).size()) {
//                         blockToPlace = {static_cast<float>((blockPosition.first + x) * _gameMap->getBlockSize()), 0, static_cast<float>((blockPosition.second + y) * _gameMap->getBlockSize())};

//                         aiForbiddenCells.emplace_back(_gameMap->transposeFrom3Dto2D(blockToPlace));
//                     }
//                 }
//             }
//         }
//     }
//     return aiForbiddenCells;
// }





// std::vector<std::pair<int, Position>> Scene::GameScene::checkPlayerPos(Position const &aiPos, int indexAi)
// {
//     std::vector<std::pair<int, Position>> posPlayers;
//     int index = 0;

//     for (auto &player : _players) {
//         if (index != indexAi)
//             posPlayers.emplace_back(index, player.second->getPosition());
//         index++;
//     }
//     return posPlayers;
// }

// bool Scene::GameScene::checkAiIsSafe(std::shared_ptr<Object::Player> const &ai)
// {
//     std::pair<int, int> aiPos = _gameMap->transposeFrom3Dto2D(ai->getPosition());

//     for (auto &cell : ai->getAiForbiddenCells())
//         if (cell == aiPos)
//             return false;
//     return true;
// }

// bool Scene::GameScene::checkAiIsSafe(std::shared_ptr<Object::Player> const &ai, std::pair<int, int> const &aiPos)
// {
//     for (auto &cell : ai->getAiForbiddenCells())
//         if (cell == aiPos)
//             return false;
//     return true;
// }

// void Scene::GameScene::handleAi(std::map<PlayerAction, bool> &tmp, std::shared_ptr<Object::Player> const &ai, int indexAi)
// {
//     for (auto &[action, isPressed] : tmp) {
//         tmp.at(action) = false;
//     }

//     // ai->handleEvent(tmp);

//     // DEBUG

//     // std::cout << "AI is safe ? " << ai->getIsSafe() << std::endl;

//     // std::pair<int, int> aipos = _gameMap->transposeFrom3Dto2D(ai->getPosition());
//     // std::cout << "AI position: " << aipos.first << ", " << aipos.second << std::endl;

//     // ai->setAiForbiddenCells(stockForbiddenCells(ai, indexAi));
//     // for (auto &cell : ai->getAiForbiddenCells())
//     //     std::cout << "cell : " << cell.first << ", " << cell.second << std::endl;

//     // DEBUG

//     // if (!ai->getIsMoving()) {
//     //     ai->animation(1);
//     //     ai->setAiPossibleDirections(getPossibleDir(ai, indexAi));
//     //     ai->setActionMove(rand() % ai->getAiPossibleDirections().size());
//     // }

//     // if (_gameMap->isColliding(_collisionCondition.at(static_cast<PlayerAction>(ai->getAiPossibleDirections().at(ai->getActionMove()))), ai->getPosition()) == Object::MAP_OBJECTS::EMPTY  && !isCollidingBomb(_collisionCondition.at(static_cast<PlayerAction>(ai->getAiPossibleDirections().at(ai->getActionMove()))), ai->getPosition(), static_cast<Object::PLAYER_ORDER>(indexAi))) {
//     //     CollideObject(ai->getPosition(), static_cast<Object::PLAYER_ORDER>(indexAi));
//     //     tmp.at(static_cast<PlayerAction>(ai->getAiPossibleDirections().at(ai->getActionMove()))) = true;
//     //     ai->setIsMoving(true);
//     // } else {
//     //     ai->setIsMoving(false);
//     //     if (ai->getIsSafe() && _gameMap->isColliding(_collisionCondition.at(static_cast<PlayerAction>(ai->getAiPossibleDirections().at(ai->getActionMove()))), ai->getPosition()) == Object::MAP_OBJECTS::BOX) {
//     //         tmp.at(PlayerAction::Drop) = true;
//     //     }
//     // }

//     // for (auto &[action, isPressed] : tmp) {
//     //     if (isPressed && ai->isAlive()) {
//     //         if (action == PlayerAction::Drop && ai->getAlreadyPlacedBombs() < ai->getRangeBomb()) {
//     //             placeBomb(ai->getPosition(), static_cast<Object::PLAYER_ORDER>(indexAi));
//     //             // ai->setIsSafe(false);
//     //         } else
//     //             ai->move(_actionMap.at(action).first, _actionMap.at(action).second);
//     //     }
//     // }
// }
