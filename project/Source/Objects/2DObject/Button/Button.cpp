/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Button
*/

#include "AudioError.hpp"
#include "tools.hpp"
#include "Button.hpp"

Object::Button::Button(std::string const &buttonPath, int nbFrame, Position const &position) : _isEnable(true), 
    _isClickable(true),
    _nbFrame(nbFrame), _state(Default), _position(position), _buttonTexture(LoadTexture(buttonPath.c_str())), _frameHeight((float)_buttonTexture.height/_nbFrame), _isAudio(false),
    _sourceRec({ 0, 0, (float)_buttonTexture.width, _frameHeight }),
    _buttonRect({ _position.getX(),  _position.getY(), (float)_buttonTexture.width, (float)_buttonTexture.height / _nbFrame}),
    _callBack(nullptr)
{
}

Object::Button::Button(std::string const &buttonPath, int nbFrame, std::function<void(void)> callBack, std::string const &audioPath, Position const &position) : _isEnable(true),
    _isClickable(true),
    _nbFrame(nbFrame), _position(position), _buttonTexture(LoadTexture(buttonPath.c_str())), _frameHeight((float)_buttonTexture.height/_nbFrame), _audio(audioPath), _isAudio(true), _callBack(callBack),
    _sourceRec({ 0, 0, (float)_buttonTexture.width, _frameHeight }),
    _buttonRect({ _position.getX(),  _position.getY(), (float)_buttonTexture.width, (float)_buttonTexture.height / _nbFrame})
{
}

Object::Button::Button(nlohmann::json const &jsonData) :
    _isEnable(jsonData.value("isEnable", true)),
    _isClickable(jsonData.value("isClickable", true)),
    _nbFrame(jsonData.value("nbFrame", 1)),
    _state(Default),
    _buttonTexture(LoadTexture(jsonData.value("texture", "default").c_str())),
    _frameHeight(_buttonTexture.height / _nbFrame),
    _isAudio(false),
    _callBack(nullptr)
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
    if (jsonData.contains("text")) {
        std::cout << "contain text" << std::endl;
        _text(jsonData.at("text"));
        std::cout << "button pos" << getPosition() << std::endl;
        std::cout << "text pos" << _text.getPosition() << std::endl;
        _text.setPosition(getPosition() + _text.getPosition());
    // there is an entry with key "foo"
    }
    // try {
    //     _text(jsonData.value("text"));
    //     std::cout << "text text" << std::endl;
    // } catch (nlohmann::json::out_of_range const &e) {
    //     _text.disable();
    // }
}

Object::Button::Button(nlohmann::json const &jsonData, Object::Render::MyTexture &texture) :
    _isEnable(jsonData.value("isEnable", true)),
    _isClickable(jsonData.value("isClickable", true)),
    _nbFrame(jsonData.value("nbFrame", 1)),
    _state(Default),
    _buttonTexture(texture.getTexture()),
    _frameHeight(_buttonTexture.height / _nbFrame),
    _isAudio(false),
    _callBack(nullptr)
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
    // try {
        // _text(jsonData.at("text"));
    // } catch (nlohmann::json::out_of_range const &e) {
        // _text.disable();
    // }
    if (jsonData.contains("text")) {
        std::cout << "contain text" << std::endl;
        _text(jsonData.at("text"));
        _text.setPosition(getPosition() + _text.getPosition());

    // there is an entry with key "foo"
    }
}

Object::Button::~Button()
{
    UnloadTexture(_buttonTexture);
}

void Object::Button::draw()
{
    if (_nbFrame == 2 && _state == Button::State::Click)
        _sourceRec.y = _frameHeight;
    else
        _sourceRec.y = _state * _frameHeight;
    if (_isEnable) {
        DrawTextureRec(_buttonTexture, _sourceRec, (Vector2){ _buttonRect.x, _buttonRect.y }, WHITE); // Draw button frame
        _text.draw();
    }
}

void Object::Button::enable()
{
    _isEnable = true;
}

void Object::Button::disable()
{
    _isEnable = false;
}

bool Object::Button::isEnable() const
{
    return _isEnable;
}

void Object::Button::enableClick()
{
    _isClickable = true;
}

void Object::Button::disableClick()
{
    _isClickable = false;
}

bool Object::Button::isClickable() const
{
    return _isClickable;
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

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && _isClickable) {
            if (_isAudio)
                _audio.play();
            if (_callBack)
                _callBack();
        }
    }
    else
        _state = Default;
}
