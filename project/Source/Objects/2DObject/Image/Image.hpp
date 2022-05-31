/*
** EPITECH PROJECT, 2022
** project
** File description:
** Image
*/

#ifndef IMAGE_HPP_
    #define IMAGE_HPP_

    #include <raylib.h>
    #include <nlohmann/json.hpp>

    #include "ITwoDimensionObject.hpp"

namespace Object {
    class Image : public ITwoDimensionObject {
        public:
            Image(std::string const &imagePath, Position const &position = {0, 0});
            Image(nlohmann::json const &jsonData);
            ~Image();

            void draw() override;

            void setPosition(Position const &position) override;
            void setPosition(float x, float y) override;
            void setPosition(float x, float y, float z) override;
            Position getPosition() const override;

            void setScale(float scale);

        protected:
        private:
            Position _imagePosition;
            Texture2D _imageTexture;
            float _imageScale = 1.0f;
    };
}

#endif /* !IMAGE_HPP_ */
