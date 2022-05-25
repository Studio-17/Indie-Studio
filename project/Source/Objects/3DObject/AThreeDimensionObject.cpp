/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** AThreeDimensionObject
*/

#include "AThreeDimensionObject.hpp"

Object::AThreeDimensionObject::AThreeDimensionObject(std::string const &pathToModel, std::string const &pathToTexture) :
    _position(0, 0, 0),
    _dimension(0, 0, 0)
{
    _model = LoadModel(pathToModel.c_str());
    _texture = LoadTexture(pathToTexture.c_str());

    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;

    _scale = 1;
}

Object::AThreeDimensionObject::AThreeDimensionObject(std::string const &pathToModel, std::string const &pathToTexture, Position const &position) : AThreeDimensionObject(pathToModel, pathToTexture)
{
    _position = position;
}

Object::AThreeDimensionObject::AThreeDimensionObject(std::string const &pathToModel, std::string const &pathToTexture, Position const &position, float scale) : AThreeDimensionObject(pathToModel, pathToTexture, position)
{
    _scale = scale;
}

Object::AThreeDimensionObject::AThreeDimensionObject(std::pair<std::string, std::string> const &pathToRessources) :
    _position(0, 0, 0),
    _dimension(0, 0, 0)
{
    _model = LoadModel(pathToRessources.first.c_str());
    _texture = LoadTexture(pathToRessources.second.c_str());

    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;

    _scale = 1;
}

Object::AThreeDimensionObject::AThreeDimensionObject(std::pair<std::string, std::string> const &pathToRessources, Position const &position) : AThreeDimensionObject(pathToRessources.first, pathToRessources.second)
{
    _position = position;
}

Object::AThreeDimensionObject::AThreeDimensionObject(std::pair<std::string, std::string> const &pathToRessources, Position const &position, float scale) : AThreeDimensionObject(pathToRessources.first, pathToRessources.second)
{
    _scale = scale;
}

Object::AThreeDimensionObject::~AThreeDimensionObject()
{
}
