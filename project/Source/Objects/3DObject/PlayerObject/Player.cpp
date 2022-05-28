/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#include "Player.hpp"

Object::Player::Player(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position) : AThreeDimensionObject(pathToRessources, pathToAnimation, nbAnimation, position)
{
}

Object::Player::Player(nlohmann::json const &jsonData) : AThreeDimensionObject(jsonData)
{
}

Object::Player::~Player()
{
    // UnloadTexture(_texture);
    // UnloadModel(_model);
    // for (unsigned int i = 0; i < _animsCount; i++) UnloadModelAnimation(_anims[i]);
}

void Object::Player::move(Position const &position, Position const &direction)
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount)
        _animFrameCounter = 0;

    _model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * direction.getX(), DEG2RAD * direction.getY(), DEG2RAD * direction.getZ()});
    setPosition((Position){ position.getX(), position.getY(), position.getZ() });
}

void Object::Player::resetAnimation()
{
    _animFrameCounter = 19;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
}

void Object::Player::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };

    DrawModelEx(_model, modelPosition, (Vector3){ 0.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1 * _scale, 1 * _scale, 1 * _scale }, WHITE);
    // DrawModelWires(_model, modelPosition, 5, GREEN);
}
