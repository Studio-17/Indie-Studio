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

class Map {
    public:
        Map();
        ~Map();
        std::vector<std::string> load(const std::string &filename); // Open the file & return the content in a vector
        void generate(const std::string &filename, std::size_t x, std::size_t y); // Create a file of x & y dimensions with the map
        void render(std::vector<std::string> map); // Render the map

        float getSize() { return (_size); };
        void setSize(float value) { _size = value ;};

    protected:
    private:
        std::vector<std::string> _map;
        std::map<int, std::string> _mapObjects;

        std::map<std::size_t, Model> _model;
        std::map<std::size_t, Texture2D> _texture;

        float _size;
};

#endif /* !MAP_HPP_ */
