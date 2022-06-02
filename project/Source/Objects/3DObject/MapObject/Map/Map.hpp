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
            Map(std::vector<Object::Render::MyModel> models, std::vector<Object::Render::MyTexture> texture);
            Map(std::vector<Object::Render::MyModel> models, std::vector<Object::Render::MyTexture> texture, Position const &position);

            ~Map();

            void draw();

            void enable() override { _isEnable = true; };
            void disable() override { _isEnable = false; };
            bool isEnable() const override { return _isEnable; };

            void setPosition(Position const &position) override { _mapPosition = position; };
            void setPosition(float x, float y) override { _mapPosition.setX(x); _mapPosition.setY(y); };
            void setPosition(float x, float y, float z) override { _mapPosition = {x, y ,z}; };
            Position getPosition() const override { return _mapPosition; };

            std::vector<std::string> load(std::string const &pathToFile);
            void process(std::string const &pathToFile);

            std::vector<Position> getMapCorners(std::size_t width, std::size_t height);
            void generate(const std::string &filename, std::size_t width, std::size_t height, std::size_t percentageDrop);

            void createFile(const std::string &filename);

            std::vector<std::shared_ptr<Object::Block>> getMapObjects() { return _mapObjects; };
            std::vector<std::vector<std::shared_ptr<AThreeDimensionObject>>> getMapPositionsObjects() { return _mapPositionsObjects; };


            void printLine(std::size_t height);
            Position getDimensions() { return _mapDimensions; };

            float getBlockSize() { return _blockSize; };
            void removeBlock(std::size_t index);
            Object::MAP_OBJECTS isColliding(Position &direction, Position playerPosition);
            int roundUp(int nb, int multiple);

            template<typename T>
            void placeObjectInMap(Position &position, std::shared_ptr<T> objectToPlace)
            {
                std::pair<int, int> tempPair = transposeFrom3Dto2D(position);
                _mapPositionsObjects[tempPair.second][tempPair.first] = objectToPlace;
            }

            std::pair<int, int> transposeFrom3Dto2D(Position &position);

            std::vector<std::vector<std::shared_ptr<AThreeDimensionObject>>> _mapPositionsObjects;

            void exploseBomb(Position const &bombPosition, int radius);

        protected:
        private:
            std::vector<std::shared_ptr<Object::Block>> _mapObjects;

            std::vector<std::vector<std::shared_ptr<AThreeDimensionObject>>> _groundMap;

            Position _mapPosition;

            bool _isEnable;
            std::string _pathToMap;
            std::ofstream _file;


            Position _mapPosition;
            Position _mapDimensions;

            float _blockSize;


            std::vector<std::shared_ptr<Object::Block>> _mapObjects;

            std::vector<Object::Render::MyModel> _mapModels;
            std::vector<Object::Render::MyTexture> _mapTextures;
    };
}

#endif /* !MAP_HPP_ */
