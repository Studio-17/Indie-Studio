/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** loadObject
*/

#include <string>
#include <vector>
#include <memory>

#include "Button.hpp"
#include "Text.hpp"

#include "tools.hpp"
#include "FileError.hpp"
#include "IObject.hpp"

template <typename T>
static std::shared_ptr<Object::IObject> takeComponent(nlohmann::json const &jsonData)
{
    return std::make_shared<T>(jsonData);
}

std::vector<std::shared_ptr<Object::IObject>> loadObject(std::string const &filepath)
{
    nlohmann::json jsonData;
    std::vector<std::shared_ptr<Object::IObject>> objects;
    std::map<std::string, std::shared_ptr<Object::IObject> (*)(nlohmann::json const &jsonData)> allConstruct {
        {"button", takeComponent<Object::Button>},
        {"text", takeComponent<Object::Text>},
    };

    try {
        jsonData = getJsonData(filepath);
    } catch (Error::FileError const &e) {
        std::cerr << e.what() << std::endl;
        return {};
    }
    std::cout << jsonData.size() << std::endl;
    for (auto oneData : jsonData) {
        std::string type = oneData.value("type", "default");
        std::function<std::shared_ptr<Object::IObject>(nlohmann::json const &jsonData)> func;

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
