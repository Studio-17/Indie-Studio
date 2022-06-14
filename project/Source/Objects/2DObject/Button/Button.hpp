/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include <raylib.h>
    #include <nlohmann/json.hpp>

    #include <string>
    #include <functional>

    #include "MySound.hpp"
    #include "Texture.hpp"
    #include "Text.hpp"
    #include "Image.hpp"
    #include "ITwoDimensionObject.hpp"

/**
 * @brief Button class
 */
namespace Object {
    class Button : public ITwoDimensionObject {
        public:
            /**
             * @brief Construct a new Button object from path to texture, number of frame and positions sent as parameter
             *
             * @param buttonPath path to button texture
             * @param nbFrame number of frame
             * @param position 2 dimension Position
             */
            Button(std::string const &buttonPath, int nbFrame, Position const &position = {0, 0});
            /**
             * @brief Construct a new Button object from path to texture, number of frame, callback event, path to audio click and 2 dimension Position
             *
             * @param buttonPath path to button texture
             * @param nbFrame number of frame
             * @param callBack call back event
             * @param audioPath path to audio click
             * @param position 2 dimension Position
             */
            Button(std::string const &buttonPath, int nbFrame, std::function<void(void)> callBack, std::string const &audioPath, Position const &position = {0, 0});
            /**
             * @brief Construct a new Button object from JSON file
             *
             * @param jsonData path to JSON file
             */
            Button(nlohmann::json const &jsonData);
            /**
             * @brief Construct a new Button object from JSON file and MyTexture object
             *
             * @param jsonData path to JSON file
             * @param texture MyTexture object
             */
            Button(nlohmann::json const &jsonData, Object::Render::MyTexture &texture);
            /**
             * @brief Destroy the Button object
             */
            ~Button() override;

            void draw() override;

            void enable() override;
            void disable() override;
            bool isEnable() const override;

            /**
             * @brief Enable clickable object
             */
            void enableClick();
            /**
             * @brief Disable clickable object
             */
            void disableClick();
            /**
             * @brief Check if clickable object is enable
             *
             * @return true
             * @return false
             */
            bool isClickable() const;

            void setPosition(Position const &position) override;
            void setPosition(float x, float y) override;
            void setPosition(float x, float y, float z) override;
            Position getPosition() const override;

            void setText(std::string const &text);
            std::string getText() const;

            void setTextPosition(Position const &position);
            void setTextPosition(float x, float y);
            Position getTextPosition() const;

            /**
             * @brief Set the call back event
             *
             * @param callBack function call back event
             */
            void setCallBack(std::function<void(void)> callBack);

            /**
             * @brief Check if mouse is on click
             *
             * @return true
             * @return false
             */
            bool onClick();
            /**
             * @brief Check if mouse is on hover
             *
             * @return true
             * @return false
             */
            bool onHover();
            /**
             * @brief Set mouse state on button
             *
             * @param mousePosition position of mouse on the screen
             */
            void checkHover(Vector2 const &mousePosition);
        protected:
        private:
            /**
             * @brief An enumeration of every state button
             */
            enum State {
                Default = 0,
                Hover = 1,
                Click = 2
            };
            bool _isEnable; ///< button is enable
            bool _isClickable; ///< button is clickable
            int _nbFrame; ///< number of frame of a button
            State _state; ///< state of a button object
            Position _position; ///< 2 or 3 dimensional position

            Texture2D _buttonTexture; ///< button texture from raylib
            Rectangle _buttonRect; ///< button rectangle from raylib
            Rectangle _sourceRec; ///< source rectangle from raylib

            float _frameHeight; ///< height of each frame

            MySound _audio; ///< audio object
            bool _isAudio; ///< audio is present or not

            Text _text; ///< text object
            Image _image; ///< image object
            std::function<void(void)> _callBack; ///< call back event function

    };
}

#endif /* !BUTTON_HPP_ */
