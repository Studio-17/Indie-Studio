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

    #include "FileError.hpp"
    #include "Block.hpp"

namespace Object
{
    class Map : public IObject
    {
        public:
            Map();
            Map(Position const &position);

            ~Map();

            void draw();

            void setPosition(Position const &position) override { _mapPosition = position; };
            void setPosition(float x, float y) override { _mapPosition.setX(x); _mapPosition.setY(y); };
            void setPosition(float x, float y, float z) override { _mapPosition = {x, y ,z}; };

            std::vector<std::string> load(std::string const &pathToFile);
            void process(std::string const &pathToFile);

            void generate(const std::string &filename, std::size_t width, std::size_t height);

            void createFile(const std::string &filename);

            std::vector<std::shared_ptr<Object::Block>> getMapObjects() { return _mapObjects; };

            void printLine(std::size_t height);
            Position getDimensions() { return _mapDimensions; };

            float getBlockSize() { return _blockSize; };

            bool removeBlock(std::size_t index);

        protected:
        private:
            std::vector<std::shared_ptr<Object::Block>> _mapObjects;

            Position _mapPosition;

            std::string _pathToMap;
            std::ofstream _file;

            Position _mapDimensions;

            float _blockSize;
    };
}

#endif /* !MAP_HPP_ */
