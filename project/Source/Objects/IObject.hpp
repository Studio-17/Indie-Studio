/*
** EPITECH PROJECT, 2022
** project
** File description:
** IObject
*/

#ifndef IOBJECT_HPP_
    #define IOBJECT_HPP_

    #include <memory>

    #include <nlohmann/json.hpp>

    #include "Settings.hpp"
    #include "Position.hpp"

namespace Object {
    class IObject {
        public:
            virtual ~IObject() = default;

            virtual void draw() = 0;

            virtual void enable() = 0;
            virtual void disable() = 0;
            virtual bool isEnable() const = 0;

            virtual void setPosition(Position const &position) = 0;
            virtual void setPosition(float x, float y) = 0;
            virtual void setPosition(float x, float y, float z) = 0;
            virtual Position getPosition() const = 0;
        protected:
        private:
    };
}

#endif /* !IOBJECT_HPP_ */
