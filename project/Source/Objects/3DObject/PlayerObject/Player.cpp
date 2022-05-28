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

Object::Player::~Player()
{
    // UnloadTexture(_texture);
    // UnloadModel(_model);
    // for (unsigned int i = 0; i < _animsCount; i++) UnloadModelAnimation(_anims[i]);
}

void Object::Player::move(Position const &position)
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount) _animFrameCounter = 0;

    // Position newPosition(position.getX(), position.getY(), position.getZ());
    setPosition((Position){ position.getX(), position.getY(), position.getZ() });
}

void Object::Player::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };

    DrawModelEx(_model, modelPosition, (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1*_scale, 1*_scale, 1*_scale }, WHITE);
    DrawModelWires(_model, modelPosition, 5, GREEN);
}
