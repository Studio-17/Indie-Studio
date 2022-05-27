/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Gamepad
*/

#include "Gamepad.hpp"

Gamepad::Gamepad()
{
}

Gamepad::~Gamepad()
{
}


bool Gamepad::isAvailable(int gamepad) const
{
    return IsGamepadAvailable(gamepad);
}

std::string Gamepad::getName(int gamepad) const
{
    return GetGamepadName(gamepad);
}

bool Gamepad::isButtonPressed(int gamepad, int button) const
{
    return IsGamepadButtonPressed(gamepad, button);
}

bool Gamepad::isButtonDown(int gamepad, int button) const
{
    return IsGamepadButtonDown(gamepad, button);
}

bool Gamepad::isButtonReleased(int gamepad, int button) const
{
    return IsGamepadButtonReleased(gamepad, button);
}

bool Gamepad::isButtonUp(int gamepad, int button) const
{
    return IsGamepadButtonUp(gamepad, button);
}

int Gamepad::getButtonPressed() const
{
    return GetGamepadButtonPressed();
}

int Gamepad::getAxisCount(int gamepad) const
{
    return GetGamepadAxisCount(gamepad);
}

float Gamepad::getAxisMovement(int gamepad, int axis) const
{
    return GetGamepadAxisMovement(gamepad, axis);
}

int Gamepad::setMappings(const char *mappings)
{
    return SetGamepadMappings(mappings);
}
