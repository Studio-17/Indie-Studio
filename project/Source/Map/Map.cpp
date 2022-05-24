/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Map
*/

#include "Map.hpp"

Map::Map()
{
    _model.insert({0, LoadModel("Assets/models/dirt/box.obj")});
    _model.insert({1, LoadModel("Assets/models/dirt/ground.obj")});
    _model.insert({2, LoadModel("Assets/models/dirt/wall_middle.obj")});
    _model.insert({3, LoadModel("Assets/models/dirt/wall_side.obj")});
    _model.insert({4, LoadModel("Assets/models/stone/box.obj")});
    _model.insert({5, LoadModel("Assets/models/stone/ground.obj")});
    _model.insert({6, LoadModel("Assets/models/stone/wall_middle.obj")});
    _model.insert({7, LoadModel("Assets/models/stone/wall_side.obj")});

    _texture.insert({0, LoadTexture("Assets/models/dirt/box.png")});
    _texture.insert({1, LoadTexture("Assets/models/dirt/ground.png")});
    _texture.insert({2, LoadTexture("Assets/models/dirt/wall_middle.png")});
    _texture.insert({3, LoadTexture("Assets/models/dirt/wall_side.png")});
    _texture.insert({4, LoadTexture("Assets/models/stone/box.png")});
    _texture.insert({5, LoadTexture("Assets/models/stone/ground.png")});
    _texture.insert({6, LoadTexture("Assets/models/stone/box.png")});
    _texture.insert({7, LoadTexture("Assets/models/stone/wall_side.png")});

    for (auto &i : _model) {
        i.second.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture.at(i.first);
    }
    _mapObjects = {
        {'X', ""},
    };
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

void Map::render([[maybe_unused]] std::vector<std::string> map)
{
    Vector3 tilePosition = { 0.0f, -5.0f, -5.0f };

    for (auto &[id, model] : _model ) {
        DrawModel(model, tilePosition, 0.5f, WHITE);
        tilePosition.x += 10.0f;
    }

}
