/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** tools
*/

#ifndef TOOLS_HPP_
    #define TOOLS_HPP_

    #include <nlohmann/json.hpp>

    #include <string>
    #include <vector>

    #include "IObject.hpp"
    #include "SettingsParams.hpp"

std::string readFile(std::string const &filename, std::string const &sep);
std::vector<std::string> strToWordArr(std::string const &_line, char delim);

nlohmann::json getJsonData(std::string const &filepath);

Rectangle setRectangle(std::array<float, 4> const &array);

std::vector<std::shared_ptr<Object::IObject>> loadObject(std::string const &filepath);
Color createColor(std::array<float, 4> const &array);

#endif /* !TOOLS_HPP_ */
