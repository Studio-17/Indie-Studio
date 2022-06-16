/*
** EPITECH PROJECT, 2022
** project
** File description:
** Image
*/

#include "tools.hpp"
#include "Image.hpp"

Object::Image::Image() : _isEnable(false), _imageLoaded(false), _rotation(0.0)
{
}

Object::Image::Image(std::string const &imagePath, Position const &position) :  _isEnable(true), _imageLoaded(true), _imagePosition(position),
    _imageTexture(LoadTexture(imagePath.c_str())),
    _rotation(0.0f)
{
}

Object::Image::Image(nlohmann::json const &jsonData, Object::Render::MyTexture &texture) :
    _isEnable(jsonData.value("isEnable", true)), _imageLoaded(true),
    _imageTexture(texture.getTexture()),
    _imageScale(jsonData.value("scale", 1.0)),
    _rotation(jsonData.value("rotation", 0.0f))
{
    _imagePosition.setFromArray(jsonData.value("position", std::array<float, 3>({0, 0, 0})));
}

Object::Image::Image(nlohmann::json const &jsonData) : _isEnable(jsonData.value("isEnable", true)),
    _imageLoaded(true),
    _imageTexture(LoadTexture(jsonData.value("texture", "default").c_str())),
    _imageScale(jsonData.value("scale", 1.0)),
    _rotation(jsonData.value("rotation", 0.0f))
{
    _imagePosition.setFromArray(jsonData.value("position", std::array<float, 3>({0, 0, 0})));
}

Object::Image::~Image()
{
    if (_imageLoaded)
        UnloadTexture(_imageTexture);
}

void Object::Image::operator ()(nlohmann::json const &jsonData)
{
    _isEnable = jsonData.value("isEnable", true);
    _imageLoaded = true;
    _imageTexture = LoadTexture(jsonData.value("texture", "default").c_str());
    _imageScale = jsonData.value("scale", 1.0);
    _imagePosition.setFromArray(jsonData.value("position", std::array<float, 3>({0, 0, 0})));
}

void Object::Image::draw()
{
    if (_isEnable)
        DrawTextureEx(_imageTexture, (Vector2){_imagePosition.getX(), _imagePosition.getY()}, _rotation, _imageScale, WHITE);
}

void Object::Image::enable()
{
    _isEnable = true;
}

void Object::Image::disable()
{
    _isEnable = false;
}

bool Object::Image::isEnable() const
{
    return _isEnable;
}

void Object::Image::setPosition(Position const &position)
{
    _imagePosition = position;
}

void Object::Image::setPosition(float x, float y)
{
    _imagePosition.setPosition(x, y);
}

void Object::Image::setPosition(float x, float y, float z)
{
    _imagePosition.setPosition(x, y, z);
}

void Object::Image::setScale(float scale)
{
    _imageScale = scale;
}

Position Object::Image::getPosition() const
{
    return _imagePosition;
}

void Object::Image::setRotation(float rotation)
{
    _rotation = rotation;
}

float Object::Image::getRotation() const
{
    return _rotation;
}