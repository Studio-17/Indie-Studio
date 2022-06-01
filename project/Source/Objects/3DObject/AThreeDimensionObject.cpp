/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** AThreeDimensionObject
*/

#include "AThreeDimensionObject.hpp"

Object::AThreeDimensionObject::AThreeDimensionObject(std::pair<std::string, std::string> const &pathToRessources, Position const &position) : _position(position),
    _model(LoadModel(pathToRessources.first.c_str())),
    _texture(LoadTexture(pathToRessources.second.c_str())),
    _isAnimated(false), _scale(0.5f)
{
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
}

Object::AThreeDimensionObject::AThreeDimensionObject(Object::Render::MyModel pathToModel, Object::Render::MyTexture pathToTexture, Position const &position) : _position(position),
    _model(pathToModel.getModel()),
    _texture(pathToTexture.getTexture()),
    _isAnimated(false), _scale(0.5f)
{
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
}

Object::AThreeDimensionObject::AThreeDimensionObject(std::pair<std::string, std::string> const &pathToRessources, std::string const &pathToAnimation, unsigned int nbAnimation, Position const &position) : _position(position),
    _model(LoadModel(pathToRessources.first.c_str())),
    _texture(LoadTexture(pathToRessources.second.c_str())),
    _animsCount(nbAnimation),
    _anims(LoadModelAnimations(pathToAnimation.c_str(), &_animsCount)),
    _isAnimated(true)
{
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
}

Object::AThreeDimensionObject::AThreeDimensionObject(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToRessources, Object::Render::MyAnimation &pathToAnimation, unsigned int numberOfAnimations, Position const &position) : _position(position),
    _model(pathToModel.getModel()),
    _texture(pathToRessources.getTexture()),
    _animsCount(numberOfAnimations),
    _anims(pathToAnimation.getAnimation()),
    _isAnimated(true)
{
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
}

Object::AThreeDimensionObject::AThreeDimensionObject(nlohmann::json const &jsonData) :
    _texture(LoadTexture(jsonData.value("texture", "").c_str())),
    _model(LoadModel(jsonData.value("model", "default").c_str())),
    _animsCount(jsonData.value("nbAnims", 0)),
    _animFrameCounter(0),
    _anims(LoadModelAnimations(jsonData.value("anims", "default").c_str(), &_animsCount)),
    _isAnimated(false), _scale(jsonData.value("scale", 0.5))

{
    _position.setFromArray(jsonData.value("position", std::array<float, 3>({0, 0, 0})));
    _dimensions.setFromArray(jsonData.value("dimensions", std::array<float, 3>({0, 0, 0})));
    if (_animsCount) {
        _anims = LoadModelAnimations(jsonData.value("anims", "default").c_str(), &_animsCount);
        _isAnimated = true;
    }
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
}

void Object::AThreeDimensionObject::setPosition(Position const &position)
{
    _position = position;
}

void Object::AThreeDimensionObject::setPosition(float x, float y)
{
    _position.setX(x);
    _position.setY(y);
}

void Object::AThreeDimensionObject::setPosition(float x, float y, float z)
{
    _position.setPosition(x, y, z);
}

Texture2D Object::AThreeDimensionObject::getTexture() const
{
    return _texture;
}

Model Object::AThreeDimensionObject::getModel() const
{
    return _model;
}

Position Object::AThreeDimensionObject::getPosition() const
{
    return _position;
}

Position Object::AThreeDimensionObject::getDimensions() const
{
    return _dimensions;
}

float Object::AThreeDimensionObject::getScale() const
{
    return _scale;
}

void Object::AThreeDimensionObject::setScale(float scale)
{
    _scale = scale;
}
