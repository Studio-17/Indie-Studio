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

            std::vector<std::vector<std::shared_ptr<AThreeDimensionObject>>> getMapPositionsObjects() { return _mapPositionsObjects; };

            float getBlockSize() { return _blockSize; };
            Object::MAP_OBJECTS isColliding(Position const &direction, Position const &playerPosition);
            int roundUp(int nb, int multiple);

            template<typename T>
            void placeObjectInMap(Position &position, std::shared_ptr<T> objectToPlace)
            {
                std::pair<int, int> tempPair = transposeFrom3Dto2D(position);
                _mapPositionsObjects[tempPair.second][tempPair.first] = objectToPlace;
            }

            template<typename T>
            void placeObjectInMap(std::pair<int, int> const &position, std::shared_ptr<T> objectToPlace)
            {
                _mapPositionsObjects[position.second][position.first] = objectToPlace;
            }

            std::pair<int, int> transposeFrom3Dto2D(Position const &position);

            void clearMap() {
                if (!_mapPositionsObjects.empty())
                    _mapPositionsObjects.clear();
                if (!_groundMap.empty())
                    _groundMap.clear();
            };

            std::vector<Object::Render::MyModel> getMapModels() { return _mapModels; };
            std::vector<Object::Render::MyTexture> getMapTextures() { return _mapTextures; };


            void save(std::string const &mapPath);
        protected:
        private:

            std::vector<std::vector<std::shared_ptr<AThreeDimensionObject>>> _mapPositionsObjects;
            std::vector<std::vector<std::shared_ptr<AThreeDimensionObject>>> _groundMap;

            bool _isEnable;

            Position _mapPosition;

            float _blockSize;

            std::vector<Object::Render::MyModel> _mapModels;
            std::vector<Object::Render::MyTexture> _mapTextures;
    };
}

#endif /* !MAP_HPP_ */
