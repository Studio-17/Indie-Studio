/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Gamepad
*/

#include "Gamepad.hpp"

bool Gamepad::isAvailable(int gamepad)
{
    return IsGamepadAvailable(gamepad);
}

std::string Gamepad::getName(int gamepad)
{
    return GetGamepadName(gamepad);
}

bool Gamepad::isButtonPressed(int gamepad, int button)
{
    return IsGamepadButtonPressed(gamepad, button);
}

bool Gamepad::isButtonDown(int gamepad, int button)
{
    return IsGamepadButtonDown(gamepad, button);
}

bool Gamepad::isButtonReleased(int gamepad, int button)
{
    return IsGamepadButtonReleased(gamepad, button);
}

bool Gamepad::isButtonUp(int gamepad, int button)
{
    return IsGamepadButtonUp(gamepad, button);
}

int Gamepad::getButtonPressed(void)
{
    return GetGamepadButtonPressed();
}

int Gamepad::getAxisCount(int gamepad)
{
    return GetGamepadAxisCount(gamepad);
}

float getAxisMovement(int gamepad, int axis)
{
    return GetGamepadAxisMovement(gamepad, axis);
}

int setMappings(const char *mappings)
{
    return SetGamepadMappings(mappings);
}
