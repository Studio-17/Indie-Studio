/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Bonus
*/

#include "Bonus.hpp"

Object::Bonus::Bonus(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::BONUS_OBJECTS mapObject) :
    AThreeDimensionObject(pathToRessources, position), _bonusObject(mapObject)
{
    _bonusScale = 10;
}

Object::Bonus::~Bonus()
{
}

void Object::Bonus::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };

    DrawModel(getModel(), modelPosition, _bonusScale, WHITE);
}

Object::BONUS_OBJECTS Object::Bonus::getMapObject() const
{
    return _bonusObject;
}
