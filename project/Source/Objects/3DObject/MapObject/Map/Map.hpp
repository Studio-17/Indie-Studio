/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <memory>

#include <fstream>


#include "Errors/Errors.hpp"
#include "Errors/ErrorsModules/File/FileError.hpp"

#include "Objects/3DObject/MapObject/Block/Block.hpp"

#include "Objects/IObject.hpp"

namespace Object
{
    class Map : public IObject
    {
        public:
            Map(std::string const &pathToFile);
            Map(std::string const &pathToFile, Position const &position);

            ~Map();

            void draw();

            void setPosition(Position const &position) override { _mapPosition = position; };
            void setPosition(float x, float y) override { _mapPosition.setX(x); _mapPosition.setY(y); };
            void setPosition(float x, float y, float z) override { _mapPosition = {x, y ,z}; };

            std::vector<std::string> load(std::string const &pathToFile);
            void process();

            void generate() {};

        protected:
        private:
            std::vector<Object::Block> _mapObjects;
            Position _mapPosition = {0, 0, 0};

            std::string _pathToMap;
    };
}

#endif /* !MAP_HPP_ */
