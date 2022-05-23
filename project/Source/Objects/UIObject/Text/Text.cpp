/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Text
*/

#include "Text.hpp"

Object::Text::Text()
{
}

Object::Text::~Text()
{
}

void Object::Text::draw()
{

}

void Object::Text::setPosition(Position const &position)
{
    _position = position;
}

void Object::Text::setPosition(float x, float y)
{
    _position.setPosition(x, y);
}

void Object::Text::setPosition(float x, float y, float z)
{
    _position.setPosition(x, y, z);
}

