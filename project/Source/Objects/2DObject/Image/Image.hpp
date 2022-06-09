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

    #include "Texture.hpp"
    #include "ITwoDimensionObject.hpp"

namespace Object {
    class Image : public ITwoDimensionObject {
        public:
            Image();
            Image(std::string const &imagePath, Position const &position = {0, 0});
            Image(nlohmann::json const &jsonData, Object::Render::MyTexture &texture);
            Image(nlohmann::json const &jsonData);
            ~Image();

            void operator ()(nlohmann::json const &jsonData);
            void draw() override;

            void enable() override;
            void disable() override;
            bool isEnable() const override;

            void setPosition(Position const &position) override;
            void setPosition(float x, float y) override;
            void setPosition(float x, float y, float z) override;
            Position getPosition() const override;

            void setScale(float scale);
        protected:
        private:
            bool _isEnable;
            Position _imagePosition;
            Texture2D _imageTexture;
            float _imageScale = 1.0f;
    };
}

#endif /* !IMAGE_HPP_ */
