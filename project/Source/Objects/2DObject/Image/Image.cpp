/*
** EPITECH PROJECT, 2022
** project
** File description:
** Image
*/

#include "tools.hpp"
#include "Image.hpp"

Object::Image::Image(std::string const &imagePath, Position const &position) : _imagePosition(position),
    _imageTexture(LoadTexture(imagePath.c_str()))
{
}

Object::Image::Image(nlohmann::json const &jsonData)
{
    _imagePosition.setFromArray(jsonData.value("position", std::array<float, 3>({0, 0, 0})));
    _imageTexture = LoadTexture(jsonData.value("texture", "default").c_str());
    _imageScale = jsonData.value("scale", 1.0);
}

Object::Image::~Image()
{
    UnloadTexture(_imageTexture);
}

void Object::Image::draw()
{
    DrawTextureEx(_imageTexture, (Vector2){_imagePosition.getX(), _imagePosition.getY()}, 0.0f, _imageScale, WHITE);
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
