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
    /**
     * @brief Image class
     */
    class Image : public ITwoDimensionObject {
        public:
            /**
             * @brief Construct a new Image object
             */
            Image();
            /**
             * @brief Construct a new Image object
             *
             * @param imagePath path to image texture
             * @param position 2 dimensional Position
             */
            Image(std::string const &imagePath, Position const &position = {0, 0});
            /**
             * @brief Construct a new Image object
             *
             * @param jsonData path to JSON file
             */
            Image(nlohmann::json const &jsonData);
            /**
             * @brief Construct a new Image object
             *
             * @param jsonData path to JSON file
             * @param texture MyTexture object
             */
            Image(nlohmann::json const &jsonData, Object::Render::MyTexture &texture);
            /**
             * @brief Destroy the Image object
             */
            ~Image();

            /**
             * @brief Reconstruct from JSON file
             *
             * @param jsonData path to JSON file
             */
            void operator ()(nlohmann::json const &jsonData);
            void draw() override;

            void enable() override;
            void disable() override;
            bool isEnable() const override;

            void setPosition(Position const &position) override;
            void setPosition(float x, float y) override;
            void setPosition(float x, float y, float z) override;
            Position getPosition() const override;
            void setRotation(float rotation);
            float getRotation() const;

            /**
             * @brief Set scale of object
             *
             * @param scale float scale value
             */
            void setScale(float scale);
        protected:
        private:
            bool _isEnable; ///< image is enable
            bool _imageLoaded; ///< image is loaded
            Position _imagePosition; ///< 2 dimensional position
            Texture2D _imageTexture; ///< image texture from raylib
            float _imageScale = 1.0f; ///< float scale value
            float _rotation;
    };
}

#endif /* !IMAGE_HPP_ */
