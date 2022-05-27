/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Keyboard
*/

#include "Keyboard.hpp"
#include <iostream>

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

bool Keyboard::hasBeenPressed(int key) const
{
    return IsKeyPressed(key);
}

bool Keyboard::isBeingPressed(int key) const
{
    return IsKeyDown(key);
}

bool Keyboard::hasbeenReleased(int key) const
{
    return IsKeyReleased(key);
}

bool Keyboard::isNotBeingPressed(int key) const
{
    return IsKeyUp(key);
}

void Keyboard::setExitKey(int key)
{
    SetExitKey(key);
}

int Keyboard::getPressedKeycode() const
{
    int key = GetKeyPressed();

    return key;
}

int Keyboard::getPressedCharcode() const
{
    int key = GetCharPressed();

    return key;
}

std::map<int, std::pair<int, bool>> Keyboard::getKeysPressed(std::map<int, std::pair<int, bool>> map) const
{
    for (auto &index : map)
        index.second.second = isBeingPressed(index.second.first);
    return map;
}
