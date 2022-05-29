/*
** EPITECH PROJECT, 2022
** project
** File description:
** Bomb
*/

#include "Bomb.hpp"

Object::Bomb::Bomb(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position, float lifeTime) : AThreeDimensionObject(pathToRessources, pathToAnimation, nbAnimation, position)
{
    _bombClock.start();
    _lifeTime = lifeTime;
}

Object::Bomb::~Bomb()
{
}

void Object::Bomb::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };
    DrawModelEx(_model, modelPosition, (Vector3){ 0.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1 * _scale, 1 * _scale, 1 * _scale }, WHITE);
}

bool Object::Bomb::checkIfShouldExplose()
{
    if (_lifeTime * 1000 >= _bombClock.getElapsedTime()) {
        explose();
        return true;
    }
    return false;
}

void Object::Bomb::explose()
{
    // ajouter l'anim de la bomb
}


