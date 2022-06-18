/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** loadObjects
*/

#include <string>
#include <vector>
#include <memory>

#include "Button.hpp"
#include "Text.hpp"
#include "Image.hpp"

#include "tools.hpp"
#include "FileError.hpp"

template <typename T>
static std::unique_ptr<Object::IObject> takeComponent(nlohmann::json const &jsonData)
{
    return std::make_unique<T>(jsonData);
}

std::vector<std::unique_ptr<Object::IObject>> loadGenericObjects(std::string const &filepath)
{
    nlohmann::json jsonData;
    std::vector<std::unique_ptr<Object::IObject>> objects;
    std::map<std::string, std::unique_ptr<Object::IObject> (*)(nlohmann::json const &jsonData)> allConstruct {
        {"button", takeComponent<Object::Button>},
        {"text", takeComponent<Object::Text>},
        {"image", takeComponent<Object::Image>},
    };

    try {
        jsonData = getJsonData(filepath);
    } catch (Error::FileError const &e) {
        std::cerr << e.what() << std::endl;
        return {};
    }
    for (auto oneData : jsonData) {
        std::string type = oneData.value("type", "default");
        std::function<std::unique_ptr<Object::IObject>(nlohmann::json const &jsonData)> func;

        if (type == "default")
            throw Error::FileError("undefined type in " + filepath + " configuration file");
        try {
            func = allConstruct.at(type);
        } catch (std::out_of_range const &e) {
            throw Error::FileError("type " + type + " is undefined");
        }
        objects.emplace_back(func(oneData));
    }
    return objects;
}
