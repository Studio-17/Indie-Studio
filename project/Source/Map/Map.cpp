/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Map
*/

#include "Map.hpp"

Map::Map()
{
    Model _model = LoadModel("assets/OBJFormat/wallA.obj");
    Texture2D texture = LoadTexture("assets/OBJFormat/Textures/concrete.png");
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    // // _texture = LoadTextureFromImage(image);

    setSize(0.5f);
    _mapObjects = {
        {'X', ""},
    };
}

Map::~Map()
{
    // UnloadTexture(_texture);
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

// void Map::generate(const std::string &filename, std::size_t x, std::size_t y)
// {

// }

void Map::render(std::vector<std::string> map)
{
    Vector3 tilePosition = { 0.0f, 0.5f, 0.0f };

    // Define the map used
    // for (auto tile : map)
    // {
    //     tilePosition.x = 0.0f;
    //     for (std::size_t index = 0; index < tile.size(); index += 1) {
            // DrawCubeTexture(_texture, tilePosition, _size, _size, _size, WHITE);
            DrawModel(_model, tilePosition, 1.0f, WHITE);
        //     tilePosition.x += _size;
        // }
        // tilePosition.z += _size;
    // }
}
