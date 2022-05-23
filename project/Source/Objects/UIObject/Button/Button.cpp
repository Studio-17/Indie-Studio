/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Button
*/

#include "Button.hpp"

Object::Button::Button(std::string const &buttonPath, int nbFrame, Position const &position) :
    _nbFrame(nbFrame), _state(Default), _position(position), _buttonTexture(LoadTexture(buttonPath.c_str())), _frameHeight((float)_buttonTexture.height/_nbFrame), _isAudio(false)
{
    _sourceRec = { 0, 0, (float)_buttonTexture.width, _frameHeight };
    _buttonRect = { _position.getX(),  _position.getY(), (float)_buttonTexture.width, (float)_buttonTexture.height / _nbFrame};
    // Sound fxButton = LoadSound("resources/buttonfx.wav");   // Load button sound
}

Object::Button::Button(std::string const &buttonPath, int nbFrame, std::string const &audioPath, Position const &position) :
    _nbFrame(nbFrame), _position(position), _buttonTexture(LoadTexture(buttonPath.c_str())), _frameHeight((float)_buttonTexture.height/_nbFrame), _isAudio(true)
{
    _sourceRec = { 0, 0, (float)_buttonTexture.width, _frameHeight };
    _buttonRect = { _position.getX(),  _position.getX(), (float)_buttonTexture.width, (float)_buttonTexture.height / _nbFrame};

}

Object::Button::~Button()
{
    UnloadTexture(_buttonTexture);  // Unload button texture
}

void Object::Button::draw()
{
    _sourceRec.y = _state * _frameHeight;
    BeginDrawing();
        DrawTextureRec(_buttonTexture, _sourceRec, (Vector2){ _buttonRect.x, _buttonRect.y }, WHITE); // Draw button frame
    EndDrawing();
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

        // if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else
        _state = Default;
}
