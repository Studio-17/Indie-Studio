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
    class Block : public AThreeDimensionObject
    {
        public:
            Block(std::pair<std::string, std::string> const &pathToRessources, Position const &position);
            Block(nlohmann::json const &jsonData);
            ~Block() override;

            void draw() override;

        protected:
        private:
            std::string _type = "block";
    };
}

#endif /* !BLOCK_HPP_ */
