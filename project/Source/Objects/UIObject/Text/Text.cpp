/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Text
*/

#include "Text.hpp"

Object::Text::Text(std::string const &filename, std::string const &text, Position const &position = {0, 0}) : _font(LoadFont(filename.c_str())), _text(text), _position(position)
{

}

Object::Text::Text(std::string const &filename, std::string const &text, Color const &color, Position const &position = {0, 0}) : _font(LoadFont(filename.c_str())), _text(text), _color(color), _position(position)
{

}

Object::Text::Text(std::string const &filename, std::string const &text, int fontSize, Color const &color, Position const &position = {0, 0}) : _font(LoadFont(filename.c_str())), _text(text), _fontSize(fontSize), _color(color), _position(position)
{

}

Object::Text::~Text()
{
    UnloadFont(_font);
}

void Object::Text::draw()
{
    DrawText(_text.c_str(), _position.getX(), _position.getY(), _fontSize, _color);
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

void Object::Text::drawFramePerSeconds(Position const &position)
{
    DrawFPS(position.getX(), position.getY());
}

void Object::Text::setColor(Color const &color)
{
    _color = color;
}

void Object::Text::setFontSize(int fontSize)
{
    _fontSize = fontSize;
}
