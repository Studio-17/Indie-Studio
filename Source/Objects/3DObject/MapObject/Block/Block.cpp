/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Block
*/

#include "Block.hpp"

Object::Block::Block(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::MAP_OBJECTS type, float scale) :
    AThreeDimensionObject(pathToRessources, position, type), _type(type), _blockScale(scale)
{
}

Object::Block::Block(Object::Render::MyModel pathToModel, Object::Render::MyTexture pathToTexture, Position const &position, Object::MAP_OBJECTS type, float scale) :
    AThreeDimensionObject(pathToModel, pathToTexture, position, type), _type(type), _blockScale(scale)
{
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

    if (_isEnable)
        DrawModel(_model, modelPosition, _blockScale, WHITE);
}
