/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Map
*/

#include "Map.hpp"

Map::Map()
{
    _model.insert({0, LoadModel("Assets/models/dirt/wall_side.obj")});
    _model.insert({1, LoadModel("Assets/models/stone/box.obj")});
    _model.insert({2, LoadModel("Assets/models/stone/wall_side.obj")});
    _model.insert({3, LoadModel("Assets/models/dirt/box.obj")});

    _texture.insert({0, LoadTexture("Assets/models/dirt/wall_side.png")});
    _texture.insert({1, LoadTexture("Assets/models/stone/box.png")});
    _texture.insert({2, LoadTexture("Assets/models/stone/wall_side.png")});
    _texture.insert({3, LoadTexture("Assets/models/dirt/box.png")});

    for (auto &i : _model) {
        i.second.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture.at(i.first);
    }

    _mapObjects = {
        {'x', WALL_MIDDLE},
        {'A', GROUND},
        {'X', WALL_SIDE},
        {'O', BOX}
    };
    setSize(10.0f);
}

Map::~Map()
{

}

std::vector<std::string> Map::load(const std::string &filename)
{
    std::ifstream f(filename);
    std::string tmp;

    if (_map.empty()) {
        if (!f.is_open())
            throw Error::Errors(std::cerr, "File " + filename + " doesn't exist");
        while (std::getline(f, tmp))
            _map.push_back(tmp);
        f.close();
    }
    return _map;
}

void Map::generate([[maybe_unused]] const std::string &filename, [[maybe_unused]] std::size_t x, [[maybe_unused]] std::size_t y)
{

}

// Vector3 Map::getCenteredPosition(std::vector<std::string> map)
// {
//     // return ((Vector3){(map.at(0).size() / 2), 0.0f, (map.size() / 2)});
//     return((Vector3){-75, 0, -35});

// }

void Map::render([[maybe_unused]] std::vector<std::string> map)
{
    // Vector3 tilePosition = getCenteredPosition(map);
        Vector3 tilePosition = {getSize()};


    for (auto &line : map) {
        tilePosition.x = getSize();
        for (size_t col = 0; col < line.size(); col++) {
            if (_mapObjects.find(line[col]) != _mapObjects.end())
                DrawModel(_model.at(_mapObjects.at(line[col])), tilePosition, 0.5f, WHITE);
            DrawModel(_model.at(GROUND), (Vector3){tilePosition.x, tilePosition.y - (getSize() - 1), tilePosition.z}, 0.5f, WHITE);
            tilePosition.x += getSize();
        }
        tilePosition.z += getSize();
    }
}
