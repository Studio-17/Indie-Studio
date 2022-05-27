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
    class AThreeDimensionObject : public IThreeDimensionObject
    {
    public:
        AThreeDimensionObject(std::pair<std::string, std::string> const &pathToRessources, Position const &position) : _position(position)
        {
            _model = LoadModel(pathToRessources.first.c_str());
            _texture = LoadTexture(pathToRessources.second.c_str());

            _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;

            _isAnimated = false;
            _scale = 0.5f;
        };

        AThreeDimensionObject(std::pair<std::string, std::string> const &pathToRessources, std::string const &pathToAnimation, unsigned int nbAnimation, Position const &position) : _position(position)
        {
            _model = LoadModel(pathToRessources.first.c_str());
            _texture = LoadTexture(pathToRessources.second.c_str());

            SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);

            _animsCount = nbAnimation;
            _anims = LoadModelAnimations(pathToAnimation.c_str(), &_animsCount);

            _isAnimated = true;
        };

        virtual ~AThreeDimensionObject() = default;

        virtual void draw() = 0;

        void setPosition(Position const &position) override { _position = position; };
        void setPosition(float x, float y) override
        {
            _position.setX(x);
            _position.setY(y);
        };
        void setPosition(float x, float y, float z) override { _position = {x, y, z}; };

        Texture2D getTexture() const { return _texture; };
        Model getModel() const { return _model; };
        Position getPosition() const { return _position; };
        Position getDimensions() const { return _dimensions; };
        float getScale() const { return _scale; };

        void setScale(float scale) {_scale = scale;};

    protected:
        Texture2D _texture;
        Model _model;

        Position _position;
        Position _dimensions;
        bool _isAnimated;

        unsigned int _animsCount = 0;
        int _animFrameCounter = 0;
        ModelAnimation *_anims;

        float _scale = 1;
    private:
    };
}

#endif /* !ATHREEDIMENSIONOBJECT_HPP_ */
