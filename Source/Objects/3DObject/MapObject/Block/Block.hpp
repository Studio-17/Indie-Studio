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
    /**
     * @brief Block class
     */
    class Block : public AThreeDimensionObject
    {
        public:
            /**
             * @brief Construct a new Block object
             *
             * @param pathToRessources pair of path to ressources texture and model
             * @param position 3 dimensional Position
             * @param type map object type
             * @param scale scale of block
             */
            Block(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::MAP_OBJECTS type, float scale);
            /**
             * @brief Construct a new Block object
             *
             * @param pathToModel path to ressources model
             * @param pathToTexture path to ressources texture
             * @param position 3 dimensional Position
             * @param type map object type
             * @param scale scale of block
             */
            Block(Object::Render::MyModel pathToModel, Object::Render::MyTexture pathToTexture, Position const &position, Object::MAP_OBJECTS type, float scale);
            /**
             * @brief Destroy the Block object
             *
             */
            ~Block() override;

            /**
             * @brief draw a three dimensional block object
             */
            void draw() override;

            /**
             * @brief Set the Block Scale
             *
             * @param blockScale float block scale value
             */
            void setBlockScale(float blockScale) { _blockScale = blockScale; };
            /**
             * @brief Get the Block Scale
             *
             * @return float
             */
            float getBlockScale() { return _blockScale; };

        protected:
        private:
            Object::MAP_OBJECTS _type; ///< map object type
            float _blockScale = 0.5f; ///< block scale
    };
}

#endif /* !BLOCK_HPP_ */
