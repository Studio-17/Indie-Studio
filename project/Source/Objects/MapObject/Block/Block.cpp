/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Block
*/

#include "Block.hpp"

Object::Block::Block(std::string const &pathToModel, std::string const &pathToTexture) :
    _blockPosition(0, 0, 0),
    _blockDimensions(0, 0, 0)
{
    _model = LoadModel(pathToModel.c_str());
    _texture = LoadTexture(pathToTexture.c_str());

    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;

    _scale = 1;
}

Object::Block::Block(std::string const &pathToModel, std::string const &pathToTexture, Position const &position) : Block(pathToModel, pathToTexture)
{
    _blockPosition = position;
}

Object::Block::Block(std::string const &pathToModel, std::string const &pathToTexture, Position const &position, float scale) : Block(pathToModel, pathToTexture, position)
{
    _scale = scale;
}

Object::Block::Block(MAP_OBJECTS const &type) :
    _blockPosition(0, 0, 0),
    _blockDimensions(0, 0, 0)
{
    _obj = {
        {GROUND, {"Ressources/Assets/models/dirt/wall_side.obj", "Ressources/Assets/models/dirt/wall_side.png"}},
        {WALL_MIDDLE, {"Ressources/Assets/models/stone/box.obj", "Ressources/Assets/models/stone/box.png"}},
        {WALL_SIDE, {"Ressources/Assets/models/stone/wall_side.obj", "Ressources/Assets/models/stone/wall_side.png"}},
        {BOX, {"Ressources/Assets/models/dirt/box.obj", "Ressources/Assets/models/dirt/box.png"}}
    };

    _model = LoadModel(_obj[type].first.c_str());
    _texture = LoadTexture(_obj[type].second.c_str());

    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;

    _scale = 1;
}

Object::Block::Block(MAP_OBJECTS const &type, Position const &position) : Block(type)
{
    _blockPosition = position;
}

Object::Block::Block(MAP_OBJECTS const &type, Position const &position, float scale) : Block(type, position)
{
    _scale = scale;
}

Object::Block::~Block()
{
}

void Object::Block::draw()
{
    Vector3 modelPosition = {
        _blockPosition.getX(),
        _blockPosition.getY(),
        _blockPosition.getZ()
    };

    DrawModel(_model, modelPosition, _scale, WHITE);
}
