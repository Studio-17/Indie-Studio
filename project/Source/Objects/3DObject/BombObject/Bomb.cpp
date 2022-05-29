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
    _range = 0; // Portabilité de la bombe
    // Ressources/models/bomb/bomb.obj (Path to '.obj')
    // Ressources/models/bomb/bomb.png (Path to '.png')
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


