/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Text
*/

#include "tools.hpp"
#include "Text.hpp"

Object::Text::Text() :
    _isEnable(true),
    _font(LoadFont("Ressources/fonts/primetime/PRIMETIME.ttf"))
{
}

Object::Text::Text(std::string const &filename, std::string const &text, Position const &position) : _isEnable(true),
 _position(position), _font(LoadFont(filename.c_str())), _text(text)
{

}

Object::Text::Text(std::string const &filename, std::string const &text, Color const &color, Position const &position) : _isEnable(true),
 _position(position), _font(LoadFont(filename.c_str())), _color(color), _text(text)
{

}

Object::Text::Text(std::string const &filename, std::string const &text, int fontSize, Color const &color, Position const &position) : _isEnable(true),
 _position(position), _font(LoadFont(filename.c_str())), _color(color), _text(text), _fontSize(fontSize)
{

}

Object::Text::Text(nlohmann::json const &jsonData, Object::Render::MyTexture &) : _isEnable(jsonData.value("isEnable", true)),
    _font(LoadFont(jsonData.value("font", "default").c_str())),
    _color(createColor(jsonData.value("color", std::array<float, 4>({255, 255, 255, 255})))),
    _text(jsonData.value("text", "")),
    _fontSize(jsonData.value("fontSize", 50))
{
    _position.setFromArray(jsonData.value("position", std::array<float, 3>({0, 0, 0})));
}

Object::Text::Text(nlohmann::json const &jsonData) : _isEnable(jsonData.value("isEnable", true)),
    _font(LoadFont(jsonData.value("font", "default").c_str())),
    _color(createColor(jsonData.value("color", std::array<float, 4>({255, 255, 255, 255})))),
    _text(jsonData.value("text", "")),
    _fontSize(jsonData.value("fontSize", 50))
{
    _position.setFromArray(jsonData.value("position", std::array<float, 3>({0, 0, 0})));
}

Object::Text::~Text()
{
    UnloadFont(_font);
}

void Object::Text::operator ()(nlohmann::json const &jsonData)
{
    _position.setFromArray(jsonData.value("position", std::array<float, 3>({0, 0, 0})));
    _isEnable = jsonData.value("isEnable", true);
    _font = LoadFont(jsonData.value("font", "default").c_str());
    _color = createColor(jsonData.value("color", std::array<float, 4>({255, 255, 255, 255})));
    _text = jsonData.value("text", "");
    _fontSize = jsonData.value("fontSize", 50);
}

void Object::Text::draw()
{
    if (_isEnable)
        DrawText(_text.c_str(), _position.getX(), _position.getY(), _fontSize, _color);
}

void Object::Text::enable()
{
    _isEnable = true;
}

void Object::Text::disable()
{
    _isEnable = false;
}

bool Object::Text::isEnable() const
{
    return _isEnable;
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

Position Object::Text::getPosition() const
{
    return _position;
}

void Object::Text::drawFramePerSeconds(Position const &position)
{
    DrawFPS(position.getX(), position.getY());
}

std::string Object::Text::getText() const
{
    return _text;
}

void Object::Text::setText(std::string const &text)
{
    _text = text;
}

void Object::Text::setColor(Color const &color)
{
    _color = color;
}

void Object::Text::setFontSize(int fontSize)
{
    _fontSize = fontSize;
}
