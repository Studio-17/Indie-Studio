/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_

    #include <raylib.h>
    #include <nlohmann/json.hpp>

    #include <string>

    #include "Texture.hpp"
    #include "ITwoDimensionObject.hpp"

namespace Object {
    /**
     * @brief Text class
     */
    class Text : public ITwoDimensionObject {
        public:
            /**
             * @brief Construct a new Text object
             */
            Text();
            /**
             * @brief Construct a new Text object
             *
             * @param filename path to font file
             * @param text string to display
             * @param position 2 dimensional Position
             */
            Text(std::string const &filename, std::string const &text, Position const &position);
            /**
             * @brief Construct a new Text object
             *
             * @param filename path to font file
             * @param text string to display
             * @param color color of text from raylib
             * @param position 2 dimensional Position
             */
            Text(std::string const &filename, std::string const &text, Color const &color, Position const &position = {0, 0});
            /**
             * @brief Construct a new Text object
             *
             * @param filename path to font file
             * @param text string to display
             * @param fontSize size of font
             * @param color colot of text from raylib
             * @param position 2 dimensional Position
             */
            Text(std::string const &filename, std::string const &text, int fontSize, Color const &color, Position const &position = {0, 0});
            /**
             * @brief Construct a new Text object
             *
             * @param jsonData path to JSON file
             */
            Text(nlohmann::json const &jsonData);
            /**
             * @brief Construct a new Text object
             *
             * @param jsonData path to JSON file
             * @param texture unused parameter
             */
            Text(nlohmann::json const &jsonData, Object::Render::MyTexture &texture);
            /**
             * @brief Destroy the Text object
             */
            ~Text();

            /**
             * @brief Reconstruct from JSON file
             *
             * @param jsonData path to JSON file
             */
            void operator ()(nlohmann::json const &jsonData);
            /**
             * @brief draw a two dimensional object
             *
             */
            void draw() override;

            /**
             * @brief Enable drawing an object
             *
             */
            void enable() override;
            /**
             * @brief Disable drawing an object
             *
             */
            void disable() override;
            /**
             * @brief Check if an object is enabled
             *
             * @return true
             * @return false
             */
            bool isEnable() const override;

            /**
             * @brief Set the Position object
             *
             * @param position
             */
            void setPosition(Position const &position) override;
            /**
             * @brief Set the Position object
             *
             * @param x
             * @param y
             */
            void setPosition(float x, float y) override;
            /**
             * @brief Set the Position object
             *
             * @param x
             * @param y
             * @param z
             */
            void setPosition(float x, float y, float z) override;
            /**
             * @brief Get the Position object
             *
             * @return Position
             */
            Position getPosition() const override;

            /**
             * @brief Draw FPS on screen
             *
             * @param position 2 dimensional Position
             */
            void drawFramePerSeconds(Position const &position);

            /**
             * @brief Get button text
             *
             * @return std::string
             */
            std::string getText() const;
            /**
             * @brief Set button text
             *
             * @param text
             */
            void setText(std::string const &text = "");
            /**
             * @brief Set color of text
             *
             * @param color color of text from raylib
             */
            void setColor(Color const &color);
            /**
             * @brief Set font size of text
             *
             * @param fontSize size of font
             */
            void setFontSize(int fontSize);

        protected:
        private:
            bool _isEnable; ///< text is enable
            Position _position; ///< 2 dimensional Position
            Font _font; ///< font from raylib
            Color _color; ///< color from raylib

            std::string _text; ///< string to display
            int _fontSize = 20; ///< size of font
    };
}

#endif /* !TEXT_HPP_ */
