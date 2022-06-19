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
        /**
         * @brief Class to handle generic loading of textures objects
         *
         */
        class MyTexture {
            public:
                /**
                 * @brief Construct a new My Texture object
                 *
                 * @param pathToTexture
                 */
                MyTexture(std::string const &pathToTexture) { _texture = LoadTexture(pathToTexture.c_str()); };

                /**
                 * @brief Destroy the My Texture object
                 *
                 */
                ~MyTexture() {};

                /**
                 * @brief Get the Texture object
                 *
                 * @return Texture2D
                 */
                Texture2D getTexture() { return _texture; };
                /**
                 * @brief RAII Unload texture
                 *
                 */
                void unload() { UnloadTexture(_texture); };

            protected:
            private:
                Texture2D _texture; ///< The texture object
        };
    }
}

#endif /* !MYTEXTURE_HPP_ */
