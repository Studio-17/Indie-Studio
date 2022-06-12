/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Map
*/

#include "Map.hpp"

Object::Map::Map(std::vector<Object::Render::MyModel> models, std::vector<Object::Render::MyTexture> texture) : _isEnable(true)
{
    _mapTextures = texture;
    _mapModels = models;
    _blockSize = 10.0f;
}

Object::Map::Map(std::vector<Object::Render::MyModel> models, std::vector<Object::Render::MyTexture> texture, Position const &position) : _isEnable(true)
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

    corners.push_back({_blockSize, 0.0f, _blockSize});
    corners.push_back({(_blockSize * width) - (_blockSize * 2), 0.0f, _blockSize});
    corners.push_back({_blockSize, 0.0f, (_blockSize * height) - (_blockSize * 2)});
    corners.push_back({(_blockSize * width)- (_blockSize * 2), 0.0f, (_blockSize * height) - (_blockSize * 2)});
    return corners;
}

void Object::Map::generate(const std::string &filename, std::size_t width, std::size_t height, std::size_t percentageDrop)
{
    srand(time(NULL));
    std::size_t randomNumber = 1 + (rand() % 100);
    width -= 2;
    height -= 2;

    if ((width % 2) == 0 || (height % 2) == 0)
        throw Error::Errors("Height and Width are not compatible !");
    createFile(filename);
    printLine(height);
    for (size_t x = 0; x < height; x++) {
        _file << static_cast<char>(MAP_OBJECTS::WALL_SIDE);
        for (size_t y = 0; y < width; y++) {
            if (x % 2 && y % 2)
                _file << static_cast<char>(MAP_OBJECTS::WALL_MIDDLE);
            else {
                randomNumber = 1 + (rand() % 100);
                if (randomNumber > percentageDrop || (x <= 1 || x >= height - 2) && (y <= 1 || y >= width - 2))
                    _file << static_cast<char>(MAP_OBJECTS::EMPTY);
                else
                    _file << static_cast<char>(MAP_OBJECTS::BOX);
            }
        }
        _file << static_cast<char>(MAP_OBJECTS::WALL_SIDE);
        _file << std::endl;
    }
    printLine(height);
}

void Object::Map::draw()
{
    for (int index = 0; index < _mapPositionsObjects.size(); index++) {
        for (int idx = 0; idx < _mapPositionsObjects[index].size(); idx++) {
            _mapPositionsObjects[index][idx]->draw();

        }
    }
    for (int index = 0; index < _groundMap.size(); index++) {
        for (int idx = 0; idx < _groundMap[index].size(); idx++) {
            _groundMap[index][idx]->draw();

        }
    }
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
    if (_mapObjects.at(index)->getType() == MAP_OBJECTS::BOX)
        _mapObjects.erase(_mapObjects.begin() + index);
}

void Object::Map::process(std::string const &pathToFile)
{
    _pathToMap = pathToFile;

    std::vector<std::string> mapLayout = load(_pathToMap);

    static const std::map<Object::MAP_OBJECTS, std::pair<Object::Render::MyModel, Object::Render::MyTexture>> keyMap = {
        {MAP_OBJECTS::WALL_MIDDLE, {_mapModels.at(4), _mapTextures.at(6)}},
        {MAP_OBJECTS::GROUND, {_mapModels.at(5), _mapTextures.at(7)}},
        {MAP_OBJECTS::WALL_SIDE, {_mapModels.at(6), _mapTextures.at(8)}},
        {MAP_OBJECTS::BOX, {_mapModels.at(7), _mapTextures.at(9)}},
        {MAP_OBJECTS::EMPTY, {_mapModels.at(8), _mapTextures.at(10)}},
        {MAP_OBJECTS::EXPLOSION, {_mapModels.at(9), _mapTextures.at(11)}}
    };
    static const std::map<Object::MAP_OBJECTS, float> mapScale = {
        {MAP_OBJECTS::WALL_MIDDLE, 0.5f},
        {MAP_OBJECTS::GROUND, 0.5f},
        {MAP_OBJECTS::WALL_SIDE, 0.5f},
        {MAP_OBJECTS::BOX, 0.5f},
        {MAP_OBJECTS::EMPTY, 0.1f},
        {MAP_OBJECTS::EXPLOSION, 10.0f}
    };

    srand(time(NULL));

    _mapDimensions.setX((mapLayout.size() * _blockSize) / 2);
    _mapDimensions.setY(0);
    _mapDimensions.setZ((mapLayout[0].size() * _blockSize) / 2);

    Vector3 tilePosition = {0, 0, 0};

    for (std::size_t line = 0; line < mapLayout.size(); line += 1) {
        std::vector<std::shared_ptr<AThreeDimensionObject>> tempVector;
        std::vector<std::shared_ptr<AThreeDimensionObject>> tempGrass;
        for (std::size_t col = 0; col < mapLayout.at(line).size(); col++) {
            if (keyMap.find(static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))) != keyMap.end())
                tempVector.emplace_back(std::make_shared<Object::Block>(keyMap.at(static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))).first, keyMap.at(static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))).second, (Position){tilePosition.x, tilePosition.y, tilePosition.z}, static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col)), mapScale.at(static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col)))));
            if (mapLayout.at(line).at(col) == static_cast<char>(Object::MAP_OBJECTS::WALL_SIDE))
                tempGrass.emplace_back(std::make_shared<Object::Block>(keyMap.at(MAP_OBJECTS::WALL_SIDE).first, keyMap.at(MAP_OBJECTS::WALL_SIDE).second, (Position){tilePosition.x, tilePosition.y - _blockSize, tilePosition.z}, MAP_OBJECTS::WALL_SIDE, mapScale.at(MAP_OBJECTS::WALL_SIDE)));
            else
                tempGrass.emplace_back(std::make_shared<Object::Block>(keyMap.at(MAP_OBJECTS::GROUND).first, keyMap.at(MAP_OBJECTS::GROUND).second, (Position){tilePosition.x, tilePosition.y - (_blockSize - 1), tilePosition.z}, MAP_OBJECTS::GROUND, mapScale.at(MAP_OBJECTS::GROUND)));
            tilePosition.x += _blockSize;
        }
        _mapPositionsObjects.emplace_back(tempVector);
        _groundMap.emplace_back(tempGrass);
        tilePosition.z += _blockSize;
        tilePosition.x = 0;
        tempVector.emplace_back(std::make_shared<Object::Block>(keyMap.at(MAP_OBJECTS::BOX).first, keyMap.at(MAP_OBJECTS::BOX).second, (Position){tilePosition.x, tilePosition.y, tilePosition.z}, MAP_OBJECTS::BOX, mapScale.at(MAP_OBJECTS::WALL_MIDDLE)));
    }
}

int Object::Map::roundUp(int nb, int multiple)
{
    if (multiple == 0)
        return nb;

    int remainder = abs(nb) % multiple;

    if (remainder == 0)
        return nb;

    if (nb < 0)
        return (-(abs(nb) - remainder));
    else
        return (nb + multiple - remainder);
}

Object::MAP_OBJECTS Object::Map::isColliding(Position const &direction, Position const &playerPosition)
{
    Position temppos = playerPosition;
    temppos +=  direction;

    std::pair<int, int> position = transposeFrom3Dto2D(temppos);
    return (_mapPositionsObjects.at(position.second).at(position.first)->getType());
}

std::pair<int, int> Object::Map::transposeFrom3Dto2D(Position const &position)
{
    int x = roundUp(static_cast<int>(position.getX()), (_blockSize / 2));
    int z = roundUp(static_cast<int>(position.getZ()), (_blockSize / 2));

    if (x % 10 == (_blockSize / 2))
        x -= static_cast<int>(_blockSize / 2);
    if (z % 10 == (_blockSize / 2))
        z -= static_cast<int>(_blockSize / 2);
    return {x / static_cast<int>(_blockSize), z / static_cast<int>(_blockSize)};
}

void Object::Map::save()
{
    std::ofstream o(_pathToMap);
    for (auto &line : _mapPositionsObjects) {
        for (auto &elem : line)
            o << static_cast<char>(elem->getType());
        o << std::endl;
    }

}
