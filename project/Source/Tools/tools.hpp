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

    #include "FileError.hpp"
    #include "IObject.hpp"

std::string readFile(std::string const &filename, std::string const &sep);
std::vector<std::string> strToWordArr(std::string const &_line, char delim);

nlohmann::json getJsonData(std::string const &filepath);

Rectangle setRectangle(std::array<float, 4> const &array);

std::vector<std::unique_ptr<Object::IObject>> loadGenericObjects(std::string const &filepath);
template <typename Obj>
std::vector<std::unique_ptr<Obj>> loadObjects(std::string const &filepath)
{
    nlohmann::json jsonData;
    std::vector<std::unique_ptr<Obj>> objects;

    try {
        jsonData = getJsonData(filepath);
    } catch (Error::FileError const &e) {
        std::cerr << e.what() << std::endl;
        return {};
    }
    for (auto oneData : jsonData) {
        objects.emplace_back(std::make_unique<Obj>(oneData));
    }
    return objects;
};

Color createColor(std::array<float, 4> const &array);

#endif /* !TOOLS_HPP_ */
