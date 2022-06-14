/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** ITwoDimensionObject
*/

#ifndef ITWODIMENSIONOBJECT_HPP_
    #define ITWODIMENSIONOBJECT_HPP_

    #include "IObject.hpp"

/**
 * @brief An interface of every two dimensional object
 */
namespace Object
{
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

#endif /* !ITWODIMENSIONOBJECT_HPP_ */
