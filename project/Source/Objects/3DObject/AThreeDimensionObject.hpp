/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** AThreeDimensionObject
*/

#ifndef ATHREEDIMENSIONOBJECT_HPP_
#define ATHREEDIMENSIONOBJECT_HPP_

#include "raylib.h"

#include "IThreeDimensionObject.hpp"

namespace Object
{
    class AThreeDimensionObject : public IThreeDimensionObject {
        public:
            AThreeDimensionObject();

            AThreeDimensionObject(std::string const &pathToModel, std::string const &pathToTexture);
            AThreeDimensionObject(std::string const &pathToModel, std::string const &pathToTexture, Position const &position);
            AThreeDimensionObject(std::string const &pathToModel, std::string const &pathToTexture, Position const &position, float scale);

            AThreeDimensionObject(std::pair<std::string, std::string> const &pathToRessources);
            AThreeDimensionObject(std::pair<std::string, std::string> const &pathToRessources, Position const &position);
            AThreeDimensionObject(std::pair<std::string, std::string> const &pathToRessources, Position const &position, float scale);

            virtual ~AThreeDimensionObject() = default;

            void setPosition(Position const &position) override;
            void setPosition(float x, float y) override;
            void setPosition(float x, float y, float z) override;

            virtual void draw() = 0;

        protected:
        private:
            Position _position;
            Position _dimension;

            Model _model;
            Texture2D _texture;

            float _scale;
    };
}

#endif /* !ATHREEDIMENSIONOBJECT_HPP_ */
