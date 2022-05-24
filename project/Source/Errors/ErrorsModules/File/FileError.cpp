/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** PositionError
*/

#include "FileError.hpp"

Error::FileError::FileError(std::ostream &os, std::string const &message) throw()
: Errors(os, "File: " + message)
{
}

Error::FileError::~FileError()
{
}