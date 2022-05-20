/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** PositionError
*/

#include "PositionError.hpp"

Error::PositionError::PositionError(std::ostream &os, std::string const &message) throw()
: Errors(os, "Position: " + message)
{
}

Error::PositionError::~PositionError()
{
}