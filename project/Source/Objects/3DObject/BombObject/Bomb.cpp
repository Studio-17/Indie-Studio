/*
** EPITECH PROJECT, 2022
** project
** File description:
** Bomb
*/

#include "Bomb.hpp"

Object::Bomb::Bomb(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position, float lifeTime, std::size_t range) : AThreeDimensionObject(pathToRessources, pathToAnimation, nbAnimation, position)
{
    _bombClock.start();
    _bombScale = 2.0f;
    _lifeTime = lifeTime;
    _range = range;
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
    DrawModel(_model, modelPosition, _bombScale, WHITE);
}

bool Object::Bomb::checkIfShouldExplode()
{
    int toSecond = 1000;

    if (_lifeTime * toSecond >= _bombClock.getElapsedTime()) {
        explode();
        return true;
    }
    return false;
}

void Object::Bomb::animation()
{
    // faire l'animation de la bomb (augmenter et réduire la taille de la bombe)
}

void Object::Bomb::explode()
{
    // ajouter l'animation des exposions des flammes sur chaques cases (en fonction de la portée de la bombe)
}


