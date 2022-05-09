/*
** EPITECH PROJECT, 2022
** B-EPI-000-PAR-0-0-projectname-user.email
** File description:
** main
*/

#include "Errors/Errors.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 2)
            throw Errors(std::cerr, "Invalid number of arguments");
    } catch (const std::exception &e) {
        std::cerr << "Error(s): " << e.what() << std::endl;
        return (84);
    }
    return (0);
}
