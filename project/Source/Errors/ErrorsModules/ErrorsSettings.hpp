/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** ErrorsSettings
*/

#ifndef ERRORSSETTINGS_HPP_
#define ERRORSSETTINGS_HPP_

#include "../Errors.hpp"

namespace Error
{
    class ErrorsSettings : public Errors
    {
    public:
        virtual ~ErrorsSettings() throw();

        ErrorsSettings(std::ostream &os, std::string const &message) throw();
    };
}

#endif /* !ERRORSSETTINGS_HPP_ */
