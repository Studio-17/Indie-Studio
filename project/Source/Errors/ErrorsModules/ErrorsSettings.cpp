/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** ErrorsSettings
*/

#include "ErrorsSettings.hpp"

Error::ErrorsSettings::ErrorsSettings(std::ostream &os, std::string const &message) : Error::ErrorsSettings(os, "Error [Settings]: " + message)
{
}

Error::ErrorsSettings::~ErrorsSettings()
{
}
