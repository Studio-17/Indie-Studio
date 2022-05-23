/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_

    #include "IUIObject.hpp"

namespace Object {
    class Text : public IUIObject {
        public:
            Text();
            ~Text();

            void draw() override;

            void setPosition(Position const &position) override;
            void setPosition(float x, float y) override;
            void setPosition(float x, float y, float z) override;
        protected:
        private:
            Position _position;
    };
}

#endif /* !TEXT_HPP_ */
