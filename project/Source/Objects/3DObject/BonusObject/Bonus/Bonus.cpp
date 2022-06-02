/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Bonus
*/

#include "Bonus.hpp"
#include "raymath.h"

Object::Bonus::Bonus(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::BONUS_OBJECTS mapObject) : AThreeDimensionObject(pathToRessources, position), _bonusObject(mapObject)
{
    _bonusScale = 8;
}

Object::Bonus::~Bonus()
{
}

void Object::Bonus::draw()
{
    Position direction = {40, 180, 0};

    Vector3 modelPosition = {
        getPosition().getX(),
        (getPosition().getY() + 5),
        getPosition().getZ()
    };
    _model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * direction.getX(), DEG2RAD * direction.getY(), DEG2RAD * direction.getZ()});
    DrawModel(getModel(), modelPosition, _bonusScale, WHITE);
}

Object::BONUS_OBJECTS Object::Bonus::getMapObject() const
{
    return _bonusObject;
}
