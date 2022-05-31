/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Explosion
*/

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include "raylib.h"

#include "Datas/Position.hpp"

namespace Object {
    class Explosion {
        public:
            Explosion(std::string const &pathToRessources) {
                _model = LoadModel(pathToRessources.c_str());
                _texture = LoadTexture("Ressources/models/explosion.png");

                SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);

                _position = {0, 20, 0};
            };

            ~Explosion() { UnloadTexture(_texture); };

            void setPosistion(Position const &position) {
                _position = position;
            };

            void draw() {
                DrawModel(_model, (Vector3){_position.getX(), _position.getY(), _position.getZ()}, 10, WHITE);
            };

        protected:
        private:
            Model _model;
            Position _position;
            Texture2D _texture;

            Rectangle _frame;

            bool status = false;
    };
}

#endif /* !EXPLOSION_HPP_ */
