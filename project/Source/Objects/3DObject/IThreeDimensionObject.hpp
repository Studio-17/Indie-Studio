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
    class IThreeDimensionObject : public IObject {
        public:
            virtual ~IThreeDimensionObject() = default;

            virtual void draw() = 0;

            virtual void handleEvent(std::shared_ptr<Settings> settings) = 0;

            virtual void setPosition(Position const &position) = 0;
            virtual void setPosition(float x, float y) = 0;
            virtual void setPosition(float x, float y, float z) = 0;

        protected:
        private:
    };
}

#endif /* !ITHREEDIMENSIONOBJECT_HPP_ */
