/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Block
*/

#ifndef BLOCK_HPP_
    #define BLOCK_HPP_

    #include <raylib.h>

    #include <memory>
    #include <map>

    #include "AThreeDimensionObject.hpp"

namespace Object
{
    enum class MAP_OBJECTS {
        GROUND = 'A',
        WALL_MIDDLE = 'x',
        WALL_SIDE = 'X',
        BOX = 'O',
    };

    class Block : public AThreeDimensionObject
    {
        public:
            Block(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::MAP_OBJECTS mapObject);
            ~Block() override;

            void draw() override;

            Object::MAP_OBJECTS getMapObject() const;
        protected:
        private:
            Object::MAP_OBJECTS _mapObject;
            std::string _type = "block";
    };
}

#endif /* !BLOCK_HPP_ */
