/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** ITwoDimensionObject
*/

#ifndef ITWODIMENSIONOBJECT_HPP_
    #define ITWODIMENSIONOBJECT_HPP_

    #include "IObject.hpp"

namespace Object
{
    /**
     * @brief An interface of every two dimensional object
     */
    class ITwoDimensionObject : public IObject  {
        public:
            /**
             * @brief Destroy the ITwoDimensionObject object
             */
            virtual ~ITwoDimensionObject() = default;

            /**
             * @brief draw a two dimensional object
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
            /**
             * @brief Get the Position object
             *
             * @return Position
             */
            virtual Position getPosition() const = 0;
        protected:
        private:
    };
}

#endif /* !ITWODIMENSIONOBJECT_HPP_ */
