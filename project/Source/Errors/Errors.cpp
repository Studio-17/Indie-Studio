/*
** EPITECH PROJECT, 2022
** B-EPI-000-PAR-0-0-projectname-user.email
** File description:
** Errors
*/

#include "Errors.hpp"

Errors::Errors(std::ostream &os, const std::string &message) throw() : _os(os)
{
	_message = message;
}

Errors::~Errors() throw()
{
}

const char *Errors::what() const throw()
{
	return _message.c_str();
}