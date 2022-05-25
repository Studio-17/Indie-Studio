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
    for (auto &mapObject : _mapObjects)
        mapObject.draw();
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

    static const std::map<int, std::pair<std::string, std::string>> keyMap = {
        {'x', {"Assets/models/stone/box.obj", "Assets/models/stone/box.png"}},
        {'A', {"Assets/models/dirt/wall_side.obj", "Assets/models/dirt/wall_side.png"}},
        {'X', {"Assets/models/stone/wall_side.obj", "Assets/models/stone/wall_side.png"}},
        {'O', {"Assets/models/dirt/box.obj", "Assets/models/dirt/box.png"}}
    };

    Vector3 tilePosition = {0, 0, 0};

    for (auto &line : mapLayout) {
        tilePosition.x = 10.0f;
        for (size_t col = 0; col < line.size(); col++) {
            if (keyMap.find(line[col]) != keyMap.end())
                _mapObjects.emplace_back(keyMap.at(line[col]), (Position){tilePosition.x, tilePosition.y, tilePosition.z});
            _mapObjects.emplace_back(std::make_pair("Assets/models/dirt/wall_side.obj", "Assets/models/dirt/wall_side.png"), (Position){tilePosition.x, tilePosition.y - (10.0f - 1), tilePosition.z});
            tilePosition.x += 10.0f;
        }
        tilePosition.z += 10.0f;
    }
}
