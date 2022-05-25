/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include "raylib.h"

    #include "Errors.hpp"
    #include <string>
    #include <vector>
    #include <map>
    #include <iostream>
    #include <fstream>

enum MAP_OBJECTS {
    GROUND = 0,
    WALL_MIDDLE,
    WALL_SIDE,
    BOX,
    BONUS
};

class Map {
    public:
        Map();
        ~Map();
        std::vector<std::string> load(const std::string &filename); // Open the file & return the content in a vector
        void generate(const std::string &filename, std::size_t width, std::size_t height); // Create a file of x & y dimensions with the map
        void render(std::vector<std::string> map); // Render the map
        Vector3 getCenteredPosition(std::vector<std::string> map);
        void createFile(const std::string &filename); //create a file

        float getSize() { return (_size); };
        void setSize(float value) { _size = value ;};

    protected:
    private:
        std::vector<std::string> _map;
        std::map<int, MAP_OBJECTS> _mapObjects;

        std::map<std::size_t, Model> _model;
        std::map<std::size_t, Texture2D> _texture;

        std::ofstream _file;

        float _size;
};

#endif /* !MAP_HPP_ */
