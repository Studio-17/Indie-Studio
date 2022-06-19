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
    /**
     * @brief Map class
     */
    class Map : public IObject
    {
        public:
            /**
             * @brief Construct a new Map object
             *
             * @param models vector of MyModel
             * @param texture vector of MyTexture
             */
            Map(std::vector<Object::Render::MyModel> models, std::vector<Object::Render::MyTexture> texture);
            /**
             * @brief Construct a new Map object
             *
             * @param models vector of MyModel
             * @param texture vector of MyTexture
             * @param position 3 dimensional vector
             */
            Map(std::vector<Object::Render::MyModel> models, std::vector<Object::Render::MyTexture> texture, Position const &position);
            /**
             * @brief Destroy the Map object
             */
            ~Map();

            /**
             * @brief draw a three dimensional map object
             */
            void draw();

            /**
             * @brief Enable drawing an object
             *
             */
            void enable() override { _isEnable = true; };
            /**
             * @brief Disable drawing an object
             *
             */
            void disable() override { _isEnable = false; };
            /**
             * @brief Check if an object is enabled
             *
             * @return true
             * @return false
             */
            bool isEnable() const override { return _isEnable; };

            /**
             * @brief Set the Position object
             *
             * @param position
             */
            void setPosition(Position const &position) override { _mapPosition = position; };
            /**
             * @brief Set the Position object
             *
             * @param x
             * @param y
             */
            void setPosition(float x, float y) override { _mapPosition.setX(x); _mapPosition.setY(y); };
            /**
             * @brief Set the Position object
             *
             * @param x
             * @param y
             * @param z
             */
            void setPosition(float x, float y, float z) override { _mapPosition = {x, y ,z}; };
            /**
             * @brief Get the Position object
             *
             * @return Position
             */
            Position getPosition() const override { return _mapPosition; };

            /**
             * @brief Load map
             *
             * @param pathToFile path to map file
             * @return std::vector<std::string>
             */
            std::vector<std::string> load(std::string const &pathToFile);
            /**
             * @brief Create map
             *
             * @param pathToFile path to map file
             */
            void process(std::string const &pathToFile);

            /**
             * @brief Get the map corners Position
             *
             * @param width width of map
             * @param height height of map
             * @return std::vector<Position>
             */
            std::vector<Position> getMapCorners(std::size_t width, std::size_t height);
            /**
             * @brief Get objects position in map
             *
             * @return std::vector<std::vector<std::shared_ptr<AThreeDimensionObject>>>
             */
            std::vector<std::vector<std::shared_ptr<AThreeDimensionObject>>> getMapPositionsObjects() { return _mapPositionsObjects; };

            /**
             * @brief Get block size
             *
             * @return float
             */
            float getBlockSize() { return _blockSize; };
            /**
             * @brief Is collision with block
             *
             * @param direction new position player
             * @param playerPosition original position player
             * @return Object::MAP_OBJECTS
             */
            Object::MAP_OBJECTS isColliding(Position const &direction, Position const &playerPosition);
            /**
             * @brief Round up a number
             *
             * @param nb number to round up
             * @param multiple number to round up with
             * @return int
             */
            int roundUp(int nb, int multiple);

            /**
             * @brief Object to place in map
             *
             * @tparam T
             * @param position position of object to place
             * @param objectToPlace object to place
             */
            template<typename T>
            void placeObjectInMap(Position &position, std::shared_ptr<T> objectToPlace)
            {
                std::pair<int, int> tempPair = transposeFrom3Dto2D(position);
                _mapPositionsObjects[tempPair.second][tempPair.first] = objectToPlace;
            }

            /**
             * @brief Object to place in map
             *
             * @tparam T
             * @param position position of object to place
             * @param objectToPlace object to place
             */
            template<typename T>
            void placeObjectInMap(std::pair<int, int> const &position, std::shared_ptr<T> objectToPlace)
            {
                _mapPositionsObjects[position.second][position.first] = objectToPlace;
            }

            /**
             * @brief Transpose an object from 3D to 2D
             *
             * @param position object position
             * @return std::pair<int, int>
             */
            std::pair<int, int> transposeFrom3Dto2D(Position const &position);

            /**
             * @brief Clear the content of the map
             */
            void clearMap() {
                if (!_mapPositionsObjects.empty())
                    _mapPositionsObjects.clear();
                if (!_groundMap.empty())
                    _groundMap.clear();
            };

            /**
             * @brief Get the map model
             *
             * @return std::vector<Object::Render::MyModel>
             */
            std::vector<Object::Render::MyModel> getMapModels() { return _mapModels; };
            /**
             * @brief Get the map texture
             *
             * @return std::vector<Object::Render::MyTexture>
             */
            std::vector<Object::Render::MyTexture> getMapTextures() { return _mapTextures; };

            /**
             * @brief Save map in file
             */
            void save(std::string const &mapPath);

        protected:
        private:
            std::vector<std::vector<std::shared_ptr<AThreeDimensionObject>>> _mapPositionsObjects; ///< map positions objects
            std::vector<std::vector<std::shared_ptr<AThreeDimensionObject>>> _groundMap; ///< ground map objects

            bool _isEnable; ///< is enable


            Position _mapPosition; ///< map position

            float _blockSize; ///> block size

            std::vector<Object::Render::MyModel> _mapModels; ///< map of MyModels
            std::vector<Object::Render::MyTexture> _mapTextures; ///< map of MyTextures
    };
}

#endif /* !MAP_HPP_ */
