/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** IGameObject
*/

#ifndef IGAMEOBJECT_HPP_
    #define IGAMEOBJECT_HPP_

    #include "IObject.hpp"

namespace Object {
    class IGameObject : public IObject {
        public:
            virtual ~IGameObject() = default;

            virtual void draw() = 0;

            virtual void setPosition(Position const &position) = 0;
            virtual void setPosition(float x, float y) = 0;
            virtual void setPosition(float x, float y, float z) = 0;
    };
}

#endif /* !IGAMEOBJECT_HPP_ */
