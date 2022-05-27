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
    enum class MAP_OBJECTS {
        GROUND = 'A',
        WALL_MIDDLE = 'x',
        WALL_SIDE = 'X',
        BOX = 'O',
    };

    class Map : public IObject
    {
        public:
            Map();
            Map(Position const &position);

            ~Map();

            void draw();

            void handleEvent(std::shared_ptr<Settings> settings) override {};

            void setPosition(Position const &position) override { _mapPosition = position; };
            void setPosition(float x, float y) override { _mapPosition.setX(x); _mapPosition.setY(y); };
            void setPosition(float x, float y, float z) override { _mapPosition = {x, y ,z}; };

            std::vector<std::string> load(std::string const &pathToFile);
            void process(std::string const &pathToFile);

            void generate(const std::string &filename, std::size_t width, std::size_t height);

            void createFile(const std::string &filename);

        protected:
        private:

            void printLine(std::size_t height);

            std::vector<Object::Block> _mapObjects;
            Position _mapPosition = {0, 0, 0};

            std::string _pathToMap;
            std::ofstream _file;

            Position _mapDimensions = { 0, 0, 0};
    };
}

#endif /* !MAP_HPP_ */
