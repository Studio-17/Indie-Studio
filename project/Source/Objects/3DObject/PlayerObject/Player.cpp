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

void Object::Player::moveUp()
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount) _animFrameCounter = 0;

    Position newPosition(_position.getX(), _position.getY(), _position.getZ() + 0.2f);
    setPosition(newPosition);
}

void Object::Player::moveDown()
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount) _animFrameCounter = 0;

    Position newPosition(_position.getX(), _position.getY(), _position.getZ() - 0.2f);
    setPosition(newPosition);
}

void Object::Player::moveRight()
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount) _animFrameCounter = 0;

    Position newPosition(_position.getX() + 0.2f, _position.getY(), _position.getZ());
    setPosition(newPosition);
}

void Object::Player::moveLeft()
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount) _animFrameCounter = 0;

    Position newPosition(_position.getX() - 0.2f, _position.getY(), _position.getZ());
    setPosition(newPosition);
}

void Object::Player::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };

    // if (IsKeyDown(KEY_SPACE))
    // {
    //     _animFrameCounter++;
    //     UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    //     if (_animFrameCounter >= _anims[0].frameCount) _animFrameCounter = 0;
    // }

    DrawModelEx(_model, modelPosition, (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1*_scale, 1*_scale, 1*_scale }, WHITE);

}
