/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MyTexture
*/

#ifndef MYTEXTURE_HPP_
#define MYTEXTURE_HPP_

#include <string>
#include <memory>

#include "raylib.h"

namespace Object {
    namespace Render {
        class MyTexture {
            public:
                MyTexture(std::string const &pathToTexture) { _texture = LoadTexture(pathToTexture.c_str()); };
                ~MyTexture() { /* UnloadTexture(_texture) */ } ;

                Texture2D getTexture() { return _texture; };

            protected:
            private:
                Texture2D _texture;
        };
    }
}

#endif /* !MYTEXTURE_HPP_ */
