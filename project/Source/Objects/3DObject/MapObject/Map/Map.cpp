/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Map
*/

#include "Map.hpp"

Object::Map::Map() : _mapPosition(0, 0, 0)
{
}

Object::Map::Map(Position const &position) : Map()
{
    _mapPosition = position;
}

Object::Map::~Map()
{
}

void Object::Map::createFile(const std::string &filename)
{
    _file.open(filename, std::ios::out);
    if (!_file) {
        _file.close();
        throw Error::FileError("file failed to open");
    }
}

void Object::Map::generate(const std::string &filename, std::size_t width, std::size_t height)
{
    if ((width % 2) == 0 && (height % 2) == 0)
        throw Error::FileError("Height and Width are not compatible !");
    createFile(filename);
    for (size_t x = 0; x < height; x++) {
        for (size_t y = 0; y < width; y++) {
            if (x % 2 && y % 2)
                _file << "x";
            else
                _file << " ";
        }
        _file << std::endl;
    }

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

void Object::Map::process(std::string const &pathToFile)
{
    _pathToMap = pathToFile;
    std::vector<std::string> mapLayout = load(_pathToMap);

    static const std::map<Object::MAP_OBJECTS, std::pair<std::string, std::string>> keyMap = {
        {MAP_OBJECTS::WALL_MIDDLE, {"Ressources/Assets/models/stone/box.obj", "Ressources/Assets/models/stone/box.png"}},
        {MAP_OBJECTS::GROUND, {"Ressources/Assets/models/dirt/wall_side.obj", "Ressources/Assets/models/dirt/wall_side.png"}},
        {MAP_OBJECTS::WALL_SIDE, {"Ressources/Assets/models/stone/wall_side.obj", "Ressources/Assets/models/stone/wall_side.png"}},
        {MAP_OBJECTS::BOX, {"Ressources/Assets/models/dirt/box.obj", "Ressources/Assets/models/dirt/box.png"}}
    };

    static const float blockSize = 10.0f;

    Vector3 tilePosition = {0, 0, 0};

    for (auto &line : mapLayout) {
        tilePosition.x = blockSize;
        for (std::size_t col = 0; col < line.size(); col++) {
            if (line[col] == 'X')
                _mapObjects.emplace_back(
                    keyMap.at(MAP_OBJECTS::WALL_SIDE),
                    (Position){tilePosition.x, tilePosition.y - 10, tilePosition.z});
            else
                _mapObjects.emplace_back(
                    keyMap.at(MAP_OBJECTS::GROUND),
                    (Position){tilePosition.x, tilePosition.y - (blockSize - 1), tilePosition.z});

            if (keyMap.find(static_cast<MAP_OBJECTS>(line[col])) != keyMap.end())
                _mapObjects.emplace_back(
                    keyMap.at(static_cast<MAP_OBJECTS>(line[col])),
                    (Position){tilePosition.x, tilePosition.y, tilePosition.z});
            tilePosition.x += blockSize;
        }
        tilePosition.z += blockSize;
    }
}
