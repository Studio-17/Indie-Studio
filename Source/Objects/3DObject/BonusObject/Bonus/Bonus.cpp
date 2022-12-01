/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Bonus
*/

#include "Bonus.hpp"
#include "raymath.h"

Object::Bonus::Bonus(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::BONUS_OBJECTS mapObject, Object::MAP_OBJECTS type) : AThreeDimensionObject(pathToRessources, position, type), _bonusObject(mapObject)
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
    if (_isEnable)
        DrawModel(_model, modelPosition, _bonusScale, WHITE);
}
