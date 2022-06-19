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

    #include "Texture.hpp"
    #include "FileError.hpp"
    #include "IObject.hpp"

/**
 * @brief Read the content of a file and return it as a string
 *
 * @param filename
 * @param sep
 * @return std::string
 */
std::string readFile(std::string const &filename, std::string const &sep);
/**
 * @brief Convert string to word array
 *
 * @param _line
 * @param delim
 * @return std::vector<std::string>
 */
std::vector<std::string> strToWordArr(std::string const &_line, char delim);

/**
 * @brief Get the Json Data object
 *
 * @param filepath
 * @return nlohmann::json
 */
nlohmann::json getJsonData(std::string const &filepath);

/**
 * @brief Set the Rectangle object
 *
 * @param array
 * @return Rectangle
 */
Rectangle setRectangle(std::array<float, 4> const &array);

/**
 * @brief Load generic objects from a json file to a vectr of objects
 *
 * @param filepath
 * @return std::vector<std::unique_ptr<Object::IObject>>
 */
std::vector<std::unique_ptr<Object::IObject>> loadGenericObjects(std::string const &filepath);
/**
 * @brief Load objects from a json file to a vectr of objects
 *
 * @tparam Obj
 * @param filepath
 * @return std::vector<std::unique_ptr<Obj>>
 */
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
    for (auto &oneData : jsonData)
        objects.emplace_back(std::make_unique<Obj>(oneData));
    return objects;
};

/**
 * @brief Load objects from a json file to a vectr of objects
 *
 * @tparam Obj
 * @param filepath
 * @param genericTexture
 * @return std::vector<std::unique_ptr<Obj>>
 */
template <typename Obj>
std::vector<std::unique_ptr<Obj>> loadObjects(std::string const &filepath, Object::Render::MyTexture &genericTexture)
{
    nlohmann::json jsonData;
    std::vector<std::unique_ptr<Obj>> objects;

    try {
        jsonData = getJsonData(filepath);
    } catch (Error::FileError const &e) {
        std::cerr << e.what() << std::endl;
        return {};
    }
    for (auto &oneData : jsonData)
        objects.emplace_back(std::make_unique<Obj>(oneData, genericTexture));
    return objects;
};

/**
 * @brief Create a Color object
 *
 * @param array
 * @return Color
 */
Color createColor(std::array<float, 4> const &array);

/**
 * @brief Convert an action to a string
 *
 * @param key
 * @return std::string
 */
std::string setActionToString(int key);

#endif /* !TOOLS_HPP_ */
