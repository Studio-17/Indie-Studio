/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** tools
*/

#ifndef TOOLS_HPP_
    #define TOOLS_HPP_

    #include <string>
    #include <vector>

    #include <nlohmann/json.hpp>

    #include "SettingsParams.hpp"

std::string readFile(std::string const &filename, std::string const &sep);
std::vector<std::string> strToWordArr(std::string const &_line, char delim);

nlohmann::json getJsonData(std::string const &filepath);

#endif /* !TOOLS_HPP_ */
