/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Button
*/

#include "AudioError.hpp"
#include "tools.hpp"
#include "Button.hpp"

Object::Button::Button(std::string const &buttonPath, int nbFrame, Position const &position) :
    _nbFrame(nbFrame), _state(Default), _position(position), _buttonTexture(LoadTexture(buttonPath.c_str())), _frameHeight((float)_buttonTexture.height/_nbFrame), _isAudio(false),
    _sourceRec({ 0, 0, (float)_buttonTexture.width, _frameHeight }),
    _buttonRect({ _position.getX(),  _position.getY(), (float)_buttonTexture.width, (float)_buttonTexture.height / _nbFrame})
{
}

Object::Button::Button(std::string const &buttonPath, int nbFrame, std::function<void(void)> callBack, std::string const &audioPath, Position const &position) :
    _nbFrame(nbFrame), _position(position), _buttonTexture(LoadTexture(buttonPath.c_str())), _frameHeight((float)_buttonTexture.height/_nbFrame), _audio(audioPath), _isAudio(true), _callBack(callBack),
    _sourceRec({ 0, 0, (float)_buttonTexture.width, _frameHeight }),
    _buttonRect({ _position.getX(),  _position.getY(), (float)_buttonTexture.width, (float)_buttonTexture.height / _nbFrame})
{
}

Object::Button::Button(nlohmann::json const &jsonData) :
    _nbFrame(jsonData.value("nbFrame", 1)),
    _state(Default),
    _buttonTexture(LoadTexture(jsonData.value("texture", "default").c_str())),
    _frameHeight(_buttonTexture.height / _nbFrame),
    _isAudio(false)
{
    _position.setFromArray(jsonData.value("position", std::array<float, 3>({0, 0, 0})));
    _buttonRect = { _position.getX(),  _position.getY(), (float)_buttonTexture.width, _frameHeight};
    _sourceRec = { 0, 0, (float)_buttonTexture.width, _frameHeight };
    try {
        _audio = jsonData.value("audio", "default");
        _isAudio = true;
    } catch (Error::AudioError const &) {
        _isAudio = false;
    }
}

Object::Button::~Button()
{
    UnloadTexture(_buttonTexture);
}

void Object::Button::draw()
{
    _sourceRec.y = _state * _frameHeight;
    DrawTextureRec(_buttonTexture, _sourceRec, (Vector2){ _buttonRect.x, _buttonRect.y }, WHITE); // Draw button frame
}

void Object::Button::setPosition(Position const &position)
{
    _position = position;
}

void Object::Button::setPosition(float x, float y)
{
    _position.setPosition(x, y);
}

void Object::Button::setPosition(float x, float y, float z)
{
    _position.setPosition(x, y, z);
}

Position Object::Button::getPosition() const
{
    return _position;
}

void Object::Button::setCallBack(std::function<void(void)> callBack)
{
    _callBack = callBack;
}

bool Object::Button::onClick()
{
    if (_state == Click)
       return true;
    return false;
}

bool Object::Button::onHover()
{
    if (_state == Hover)
        return true;
    return false;
}

void Object::Button::checkHover(Vector2 const &mousePosition)
{
    if (CheckCollisionPointRec(mousePosition, _buttonRect)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                _state = Click;
        else
                _state = Hover;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (_isAudio)
                _audio.play();
            if (_callBack)
                _callBack();
        }
    }
    else
        _state = Default;
}
