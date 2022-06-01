/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Explosion
*/

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include "raylib.h"

#include "Datas/Position/Position.hpp"
#include "AThreeDimensionObject.hpp"

namespace Object {
    class Explosion : public AThreeDimensionObject {
        public:
            Explosion(std::string const &pathToRessources) : AThreeDimensionObject(std::make_pair(pathToRessources, "Ressources/Fire_baseColor.png"), "Ressources/explosionAnim.iqm", 1, Position(0, 20, 0)) {
                // _model = LoadModel(pathToRessources.c_str());
                // _texture = LoadTexture("Ressources/Fire_baseColor.png");

                // SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
                // LoadModelAnimations()

                // _position = {0, 20, 0};
            };

            ~Explosion() { };

            void draw() {
                // _animFrameCounter++;
                // UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
                // if (_animFrameCounter >= _anims[0].frameCount)
                //     _animFrameCounter = 0;

                DrawModel(_model, (Vector3){_position.getX(), _position.getY(), _position.getZ()}, 10, WHITE);
            };

        protected:
        private:
            // Model _model;
            // Position _position;
            // Texture2D _texture;

            // Rectangle _frame;

            // bool status = false;
    };
}

#endif /* !EXPLOSION_HPP_ */
