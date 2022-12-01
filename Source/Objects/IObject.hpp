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

/**
 * @brief A namespace regrouping all objects in the game
 */
namespace Object {
    class IObject {
        public:
            virtual ~IObject() = default;

            /**
             * @brief Draw 2 types of object
             * - two dimensional object
             * - three dimensional object
             */
            virtual void draw() = 0;

            /**
             * @brief Enable an object
             */
            virtual void enable() = 0;
            /**
             * @brief Disable an object
             */
            virtual void disable() = 0;
            /**
             * @brief Check if an object is enable
             *
             * @return true
             * @return false
             */
            virtual bool isEnable() const = 0;

            /**
             * @brief Set the Position object
             *
             * @param position 2 or 3 dimension position class
             */
            virtual void setPosition(Position const &position) = 0;
            /**
             * @brief Set the Position object
             *
             * @param x position x value
             * @param y position y value
             */
            virtual void setPosition(float x, float y) = 0;
            /**
             * @brief Set the Position object
             *
             * @param x position x value
             * @param y position y value
             * @param z position z value
             */
            virtual void setPosition(float x, float y, float z) = 0;
            /**
             * @brief Get the Position object
             *
             * @return 3 dimensional Position
             */
            virtual Position getPosition() const = 0;
        protected:
        private:
    };
}

#endif /* !IOBJECT_HPP_ */
