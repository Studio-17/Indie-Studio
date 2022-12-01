/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** IThreeDimensionObject
*/

#ifndef ITHREEDIMENSIONOBJECT_HPP_
    #define ITHREEDIMENSIONOBJECT_HPP_

    #include "IObject.hpp"

namespace Object
{
    /**
     * @brief enum of 3D object type present in map
     */
    enum class MAP_OBJECTS {
        GROUND = 'A',
        WALL_MIDDLE = 'x',
        WALL_SIDE = 'X',
        BOX = 'O',
        EMPTY = ' ',
        BOMB = 'B',
        BONUS = 'b',
        PLAYER = 'P',
        EXPLOSION = 'E'
    };

    /**
     * @brief An interface of every three dimensional object
     */
    class IThreeDimensionObject : public IObject {
        public:
            /**
             * @brief Destroy the IThreeDimensionObject object
             */
            virtual ~IThreeDimensionObject() = default;

            /**
             * @brief draw a three dimensional object
             */
            virtual void draw() = 0;

            /**
             * @brief Enable drawing an object
             *
             */
            virtual void enable() = 0;
            /**
             * @brief Disable drawing an object
             *
             */
            virtual void disable() = 0;
            /**
             * @brief Check if an object is enabled
             *
             * @return true
             * @return false
             */
            virtual bool isEnable() const = 0;

            /**
             * @brief Set the Position object
             *
             * @param position
             */
            virtual void setPosition(Position const &position) = 0;
            /**
             * @brief Set the Position object
             *
             * @param x
             * @param y
             */
            virtual void setPosition(float x, float y) = 0;
            /**
             * @brief Set the Position object
             *
             * @param x
             * @param y
             * @param z
             */
            virtual void setPosition(float x, float y, float z) = 0;

        protected:
        private:
    };
}

#endif /* !ITHREEDIMENSIONOBJECT_HPP_ */
