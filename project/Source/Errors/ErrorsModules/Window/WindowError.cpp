/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** WindowError
*/

#include "WindowError.hpp"

WindowError::WindowError(std::ostream &os, std::string const &message) : Errors(os, "Raylib Window: " + message)
{
}

WindowError::~WindowError()
{
}
