/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Map
*/

#include "Map.hpp"

Object::Map::Map(std::string const &pathToFile) : _mapPosition(0, 0, 0)
{
    _pathToMap = pathToFile;
}

Object::Map::Map(std::string const &pathToFile, Position const &position) : Map(pathToFile)
{
    _mapPosition = position;
}

Object::Map::~Map()
{
}

void Object::Map::draw()
{
    // for (auto &mapObject : _mapObjects)
    //     mapObject.draw();
    // DrawSphere(Vector3{0,0,0}, 1, RED);
    _mapObjects.at(0).draw();
}

std::vector<std::string> Object::Map::load(std::string const &pathToFile)
{
    std::ifstream file(pathToFile);
    std::string tmp;
    std::vector<std::string> map;

    if (map.empty()) {
        if (!file.is_open())
            throw Error::FileError("File " + pathToFile + " doesn't exist");
        while (std::getline(file, tmp))
            map.push_back(tmp);
        file.close();
    }
    return (map);
}

void Object::Map::process()
{
    std::vector<std::string> mapLayout = load(_pathToMap);

    Object::Block block("Assets/models/dirt/box.obj", "Assets/models/dirt/box.png", _mapPosition);

    _mapObjects.push_back(block);
}
