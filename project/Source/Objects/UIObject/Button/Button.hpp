/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include <raylib.h>

    #include <string>
    #include <functional>

    #include "MySound.hpp"
    #include "IUIObject.hpp"

namespace Object {
    class Button : public IUIObject {
        public:
            Button(std::string const &buttonPath, int nbFrame, Position const &position = {0, 0});
            // Button(std::string const &buttonPath, int nbFrame, std::string const &audioPath, Position const &position = {0, 0});
            Button(std::string const &buttonPath, int nbFrame, std::function<void(void)> callBack, std::string const &audioPath, Position const &position = {0, 0});
            ~Button() override;

            void draw() override;

            void setPosition(Position const &position) override;
            void setPosition(float x, float y) override;
            void setPosition(float x, float y, float z) override;

            bool onClick();
            bool onHover();
            void checkHover(Vector2 const &mousePosition);
        protected:
        private:
            enum State {
                Default = 0,
                Hover = 1,
                Click = 2
            };
            // float _width;
            // float _height;
            int _nbFrame;
            State _state;
            Position _position;

            Texture2D _buttonTexture;
            Rectangle _buttonRect;
            Rectangle _sourceRec;

            float _frameHeight;

            MySound _audio;
            bool _isAudio;

            std::function<void(void)> _callBack;


            //Audio
            //Mouse Input
            // Texture
    };
}

#endif /* !BUTTON_HPP_ */
