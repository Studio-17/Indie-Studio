/*
** EPITECH PROJECT, 2022
** B-EPI-000-PAR-0-0-projectname-user.email
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <exception>
#include <iostream>
#include <string>

class Errors : public std::exception
{
    public:
        Errors(std::ostream &os, const std::string &message) throw();
        virtual ~Errors() throw();
        const char *what() const throw();

    private:
        std::string _message;
        std::ostream &_os;
};

#endif /* !ERRORS_HPP_ */
