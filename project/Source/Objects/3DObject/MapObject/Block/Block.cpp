/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Block
*/

#include "Block.hpp"

Object::Block::Block(std::string const &pathToModel, std::string const &pathToTexture, Position const &position) : _position(position), _dimensions(0,0,0)
{
    _model = LoadModel(pathToModel.c_str());
    _texture = LoadTexture(pathToTexture.c_str());

    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;

    _scale = 1;
}

Object::Block::~Block()
{
}

void Object::Block::draw()
{
    Vector3 modelPosition = {
        _position.getX(),
        _position.getY(),
        _position.getZ()
    };

    DrawModel(_model, modelPosition, _scale, WHITE);
}
