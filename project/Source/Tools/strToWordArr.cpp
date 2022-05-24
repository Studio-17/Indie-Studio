/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-clement.fernandes
** File description:
** strToWordArr
*/

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> strToWordArr(std::string const &_line, char delim)
{
    std::vector<std::string> arr;
    std::stringstream str(_line);
    std::string tmp;

    while (std::getline(str, tmp, delim))
        if (tmp.size())
            arr.push_back(tmp);
    return arr;
}
