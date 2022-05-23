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

bool Keyboard::hasBeenPressed(int key)
{
    return (IsKeyPressed(key));
}

bool Keyboard::isBeingPressed(int key)
{
    return (IsKeyDown(key));
}

bool Keyboard::hasbeenReleased(int key)
{
    return (IsKeyReleased(key));
}

bool Keyboard::isNotBeingPressed(int key)
{
    return (IsKeyUp(key));
}

void Keyboard::setExitKey(int key)
{
    SetExitKey(key);
}

int Keyboard::getPressedKeycode(void)
{
    int key = GetKeyPressed();
    return (key);
}

int Keyboard::getPressedCharcode(void)
{
    int key = GetCharPressed();

        // if ((key >= 32) && (key <= 127))
        //     return key;
    return (key);
}

#include <iostream>
std::map<int, std::pair<int, bool>> Keyboard::getKeysPressed(std::map<int, std::pair<int, bool>> map)
{
    for (auto &index : map)
        index.second.second = isBeingPressed(index.second.first);
    return map;
}

// std::map<int, std::pair<int, bool>> Keyboard::getKeysPressed(std::map<int, std::pair<int, bool>> map)
// {
//     for (auto &index : map) {
//         if (isBeingPressed(index.second.first))
//         std::cout << "pressed" << std::endl;
//     }
//     return map;
// }