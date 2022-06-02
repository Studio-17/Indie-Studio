/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Map
*/

#include "Map.hpp"

Object::Map::Map(std::vector<Object::Render::MyModel> models, std::vector<Object::Render::MyTexture> texture)
{
    _mapTextures = texture;
    _mapModels = models;
}

Object::Map::Map(std::vector<Object::Render::MyModel> models, std::vector<Object::Render::MyTexture> texture, Position const &position)
{
    _mapPosition = position;
    _blockSize = 10.0f;
}

Object::Map::~Map()
{
}

void Object::Map::createFile(const std::string &filename)
{
    _file.open(filename, std::ios::out);
    if (!_file) {
        _file.close();
        throw Error::FileError("file failed to open " + filename);
    }
}

void Object::Map::printLine(std::size_t height)
{
    for (size_t one = 0; one < height + 2; one++) {
        _file << static_cast<char>(MAP_OBJECTS::WALL_SIDE);
    }
    _file << std::endl;
}

std::vector<Position> Object::Map::getMapCorners(std::size_t width, std::size_t height)
{
    std::vector<Position> corners;

    width * _blockSize;
    corners.push_back({10.0f, 0.0f, 10.0f});
    corners.push_back({static_cast<float>(width * 10), 0.0f, 10.0f});
    corners.push_back({10.0f, 0.0f, static_cast<float>(height * 10)});
    corners.push_back({static_cast<float>(width * 10), 0.0f, static_cast<float>(height * 10)});
    return corners;
}

void Object::Map::generate(const std::string &filename, std::size_t width, std::size_t height)
{
    if ((width % 2) == 0 || (height % 2) == 0)
        throw Error::Errors("Height and Width are not compatible !");
    createFile(filename);
    printLine(height);
    for (size_t x = 0; x < height; x++) {
        _file << static_cast<char>(MAP_OBJECTS::WALL_SIDE);
        for (size_t y = 0; y < width; y++) {
            if (x % 2 && y % 2)
                _file << static_cast<char>(MAP_OBJECTS::WALL_MIDDLE);
            else
                _file << " ";
        }
        _file << static_cast<char>(MAP_OBJECTS::WALL_SIDE);
        _file << std::endl;
    }
    printLine(height);
}

void Object::Map::draw()
{
    for (auto &mapObject : _mapObjects)
        mapObject->draw();
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

void Object::Map::removeBlock(std::size_t index)
{
    if (_mapObjects.at(index)->getMapObject() == MAP_OBJECTS::BOX)
        _mapObjects.erase(_mapObjects.begin() + index);
}

void Object::Map::process(std::string const &pathToFile)
{
    _pathToMap = pathToFile;

    std::vector<std::string> mapLayout = load(_pathToMap);


    std::cout << "Models size : " << _mapModels.size() << std::endl;

    static const std::map<Object::MAP_OBJECTS, std::pair<Object::Render::MyModel, Object::Render::MyTexture>> keyMap = {
        {MAP_OBJECTS::WALL_MIDDLE, {_mapModels.at(4), _mapTextures.at(6)}},
        {MAP_OBJECTS::GROUND, {_mapModels.at(5), _mapTextures.at(7)}},
        {MAP_OBJECTS::WALL_SIDE, {_mapModels.at(6), _mapTextures.at(8)}},
        {MAP_OBJECTS::BOX, {_mapModels.at(7), _mapTextures.at(9)}}
    };

    srand(time(NULL));

    _blockSize = 10.0f;
    _mapDimensions.setX((mapLayout.size() * _blockSize) / 2);
    _mapDimensions.setY(0);
    _mapDimensions.setZ((mapLayout[0].size() * _blockSize) / 2);
    std::cout <<_mapDimensions<<std::endl;

    Vector3 tilePosition = {0, 0, 0};

    for (std::size_t line = 0; line < mapLayout.size(); line += 1) {
        for (std::size_t col = 0; col < mapLayout.at(line).size(); col++) {
            if (mapLayout.at(line).at(col) == static_cast<char>(Object::MAP_OBJECTS::WALL_SIDE))
                _mapObjects.emplace_back(std::make_shared<Object::Block>(keyMap.at(MAP_OBJECTS::WALL_SIDE).first, keyMap.at(MAP_OBJECTS::WALL_SIDE).second,
                    (Position){tilePosition.x, tilePosition.y - _blockSize, tilePosition.z}, MAP_OBJECTS::WALL_SIDE));
            else if ((col >= 3 && col <= mapLayout.at(line).size() - 4) || ( line >= 3 && line <= mapLayout.size() - 4)) {
                if (((rand() % 8) + 1) != 1) {
                    _mapObjects.emplace_back(std::make_shared<Object::Block>(
                        keyMap.at(MAP_OBJECTS::BOX).first, keyMap.at(MAP_OBJECTS::BOX).second,
                        (Position){tilePosition.x, tilePosition.y, tilePosition.z}, MAP_OBJECTS::BOX));
                }
            }

            if (keyMap.find(static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))) != keyMap.end())
                _mapObjects.emplace_back(std::make_shared<Object::Block>(
                    keyMap.at(static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))).first, keyMap.at(static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))).second,
                    (Position){tilePosition.x, tilePosition.y, tilePosition.z}, static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))));
            else
                _mapObjects.emplace_back(std::make_shared<Object::Block>(
                    keyMap.at(MAP_OBJECTS::GROUND).first, keyMap.at(MAP_OBJECTS::GROUND).second,
                    (Position){tilePosition.x, tilePosition.y - (_blockSize - 1), tilePosition.z}, MAP_OBJECTS::GROUND));

            tilePosition.x += _blockSize;
        }
        tilePosition.z += _blockSize;
        tilePosition.x = 0;
    }
}
