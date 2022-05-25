/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Block
*/

#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include "raylib.h"

#include <memory>

#include <map>

#include "IObject.hpp"

namespace Object
{
    enum MAP_OBJECTS {
        GROUND = 0,
        WALL_MIDDLE,
        WALL_SIDE,
        BOX,
        BONUS
    };

    class Block : public IObject
    {
        public:
            Block(std::string const &pathToModel, std::string const &pathToTexture);
            Block(std::string const &pathToModel, std::string const &pathToTexture, Position const &position);
            Block(std::string const &pathToModel, std::string const &pathToTexture, Position const &position, float scale);
            Block(MAP_OBJECTS const &type);
            Block(MAP_OBJECTS const &type, Position const &position);
            Block(MAP_OBJECTS const &type, Position const &position, float scale);

            ~Block() override;

            void draw() override;

            void setPosition(Position const &position) override { _blockPosition = position; };
            void setPosition(float x, float y) override { _blockPosition.setX(x); _blockPosition.setY(y); };
            void setPosition(float x, float y, float z) override { _blockPosition = {x, y ,z}; };

        protected:
        private:
            Position _blockPosition;
            Position _blockDimensions;

            Model _model;
            Texture2D _texture;

            float _scale;

            std::map<MAP_OBJECTS, std::pair<std::string, std::string>> _obj;
    };
}

#endif /* !BLOCK_HPP_ */
