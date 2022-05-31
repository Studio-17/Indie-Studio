/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#include "Player.hpp"

Object::Player::Player(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position) : AThreeDimensionObject(pathToRessources, pathToAnimation, nbAnimation, position)
{
    _playerScale = 7.0f;
}

Object::Player::Player(nlohmann::json const &jsonData) : AThreeDimensionObject(jsonData)
{
}

Object::Player::~Player()
{
}

void Object::Player::move(Position const &position, Position const &direction)
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount)
        _animFrameCounter = 0;

    _model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * direction.getX(), DEG2RAD * direction.getY(), DEG2RAD * direction.getZ()});
    _position += position;
}

void Object::Player::resetAnimation()
{
    _animFrameCounter = 20;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
}

void Object::Player::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };
    DrawModel(_model, modelPosition, _playerScale, WHITE);
}

void Object::Player::dropBomb(Position const &postion, float timeBeforeExplosion, std::size_t range)
{
    // bool blockTooked = false;
    // int nb = roundUp(pos.getZ(), _gameMap->getBlockSize() / 2);
    // if (nb % 10 == (_gameMap->getBlockSize() / 2))
    //     nb -= _gameMap->getBlockSize() / 2;

    // Position newPos = {static_cast<float>(roundUp(pos.getX(), _gameMap->getBlockSize() / 2)), pos.getY(), static_cast<float>(nb)};

    // if (static_cast<int>(newPos.getX()) % 10 == 0) {
    //     for (auto &bomb : _bombs) {
    //         if (bomb->getPosition() == newPos)
    //             blockTooked = true;
    //     }
    //     if (!blockTooked)
    //         _bombs.emplace_back(std::make_unique<Object::Bomb>(std::make_pair<std::string, std::string>("Ressources/models/bomb/bomb.obj", "Ressources/models/bomb/bomb.png"), newPos, playerNb, 3, 2));
    // }
}
