/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Block
*/

#include "Block.hpp"

Object::Block::Block(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::MAP_OBJECTS mapObject) :
    AThreeDimensionObject(pathToRessources, position), _mapObject(mapObject)
{
    _blockScale = 0.5f;
}

Object::Block::Block(Object::Render::MyModel pathToModel, Object::Render::MyTexture pathToTexture, Position const &position, Object::MAP_OBJECTS mapObjects) :
    AThreeDimensionObject(pathToModel, pathToTexture, position), _mapObject(mapObjects)
{
    _blockScale = 0.5f;
}

Object::Block::~Block()
{
}

void Object::Block::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };

    DrawModel(getModel(), modelPosition, _blockScale, WHITE);
}

Object::MAP_OBJECTS Object::Block::getMapObject() const
{
    return _mapObject;
}
