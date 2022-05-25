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

#include "Objects/3DObject/IThreeDimensionObject.hpp"

namespace Object
{
    class Block : public IThreeDimensionObject
    {
        public:
            Block(std::string const &pathToModel, std::string const &pathToTexture, Position const &position);

            ~Block() override;

            void draw() override;

            void setPosition(Position const &position) override { _position = position; };
            void setPosition(float x, float y) override { _position.setX(x); _position.setY(y); };
            void setPosition(float x, float y, float z) override { _position = {x, y ,z}; };

        protected:
        private:
            std::string _type = "block";

            Texture2D _texture;
            Model _model;

            Position _position;
            Position _dimensions;

            float _scale;
    };
}

#endif /* !BLOCK_HPP_ */
