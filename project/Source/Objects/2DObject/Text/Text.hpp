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

    #include "ITwoDimensionObject.hpp"

namespace Object {
    class Text : public ITwoDimensionObject {
        public:
            Text(std::string const &filename, std::string const &text, Position const &position);
            Text(std::string const &filename, std::string const &text, Color const &color, Position const &position = {0, 0});
            Text(std::string const &filename, std::string const &text, int fontSize, Color const &color, Position const &position = {0, 0});
            Text(nlohmann::json const &jsonData);
            ~Text();

            void draw() override;
            void drawFramePerSeconds(Position const &position);

            void setPosition(Position const &position) override;
            void setPosition(float x, float y) override;
            void setPosition(float x, float y, float z) override;
            Position getPosition() const override;

            void setColor(Color const &color);
            void setFontSize(int fontSize);

        protected:
        private:
            Position _position;
            Font _font;
            Color _color;

            std::string _text;
            int _fontSize = 20;
    };
}

#endif /* !TEXT_HPP_ */
