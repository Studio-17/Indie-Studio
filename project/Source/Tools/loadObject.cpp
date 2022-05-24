/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** loadObject
*/

#include <map>
#include <memory>
#include <unordered_map>

#include "tools.hpp"
#include "IObject.hpp"
#include "Button.hpp"
#include "Text.hpp"

static void setPosition(Position &position, std::string const &pos)
{
    std::vector<std::string> allPos = strToWordArr(pos, ',');

    float x = std::stof(allPos.at(0));
    float y = std::stof(allPos.at(1));
    float z = 0;
    if (allPos.size() == 3)
        z = std::stof(allPos.at(2));
    position.setPosition(x, y, z);
}

// template <typename T>
// static std::unique_ptr<Object::IObject> takeObject()
// {
//     return std::make_unique<T>();
// }

// static std::unique_ptr<Object::IObject> setObject(std::string const &type, std::string const &filepath, std::vector<std::string> const &audios, std::size_t nbFrame, Position const &position)
// {
//     std::unordered_map<std::string, std::unique_ptr<Object::IObject> (*)(const std::string &type)> constructor {
//         {"Button", takeObject<Object::Button>},
//         {"Text", takeObject<Object::Text>},
//     };

//     return constructor.at(type)
// }

std::vector<std::shared_ptr<Object::IObject>> loadObject(std::string const &filepath)
{
    std::string fileContent = readFile(filepath, "\n");
    std::vector<std::string> allObj = strToWordArr(fileContent, '\n');
    std::vector<std::shared_ptr<Object::IObject>> objects;

    for (auto oneObj : allObj) {
        std::vector<std::string> objData = strToWordArr(oneObj, ' ');
        std::map<std::string, std::string> objDataSplit;

        for (auto obj : objData) {
            std::vector<std::string> tmp = strToWordArr(obj, '=');

            objDataSplit.insert({tmp.at(0), tmp.at(1)});
        }
        std::string type = "";
        std::string filapth = "";
        std::vector<std::string> audios;
        std::size_t nbFrame = 1;
        Position pos(0, 0);
        if (objDataSplit.find("type") != objDataSplit.end())
            type = objDataSplit.at("type");
        if (objDataSplit.find("position") != objDataSplit.end())
            setPosition(pos, objDataSplit.at("position"));
        if (objDataSplit.find("filepath") != objDataSplit.end())
            filapth = objDataSplit.at("filepath");
        if (objDataSplit.find("audio") != objDataSplit.end())
            audios = strToWordArr(objDataSplit.at("audio"), ',');
        if (objDataSplit.find("nbFrame") != objDataSplit.end())
            nbFrame = std::stoi(objDataSplit.at("nbFrame"));

    }
}
