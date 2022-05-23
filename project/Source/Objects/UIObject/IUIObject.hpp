/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** IUIObject
*/

#ifndef IUIOBJECT_HPP_
    #define IUIOBJECT_HPP_

    #include "IObject.hpp"

namespace Object {
    class IUIObject {
        public:
            virtual ~IUIObject() = default;

            virtual void draw() = 0;

            virtual void setPosition(Position const &position) = 0;
            virtual void setPosition(float x, float y) = 0;
            virtual void setPosition(float x, float y, float z) = 0;
    };
}

#endif /* !IUIOBJECT_HPP_ */
