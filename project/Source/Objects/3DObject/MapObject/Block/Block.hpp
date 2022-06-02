/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Block
*/

#ifndef BLOCK_HPP_
    #define BLOCK_HPP_

    #include <raylib.h>

    #include <memory>
    #include <map>

    #include "AThreeDimensionObject.hpp"

namespace Object
{
    enum class MAP_OBJECTS {
        GROUND = 'A',
        WALL_MIDDLE = 'x',
        WALL_SIDE = 'X',
        BOX = 'O',
        EMPTY = ' '
    };

    class Block : public AThreeDimensionObject
    {
        public:
            Block(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::MAP_OBJECTS mapObject);
            Block(Object::Render::MyModel pathToModel, Object::Render::MyTexture pathToTexture, Position const &position, Object::MAP_OBJECTS mapObjects);
            ~Block() override;

            void draw() override;

            Object::MAP_OBJECTS getMapObject() const;

            void setBlockScale(float blockScale) { _blockScale = blockScale; };
            float getBlockScale() { return _blockScale; };

        protected:
        private:
            Object::MAP_OBJECTS _mapObject;
            std::string _type = "block";
            float _blockScale;
    };
}

#endif /* !BLOCK_HPP_ */
