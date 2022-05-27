/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Objects/3DObject/AThreeDimensionObject.hpp"

namespace Object {
    class Player : public AThreeDimensionObject {
        public:
            Player(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position);
            ~Player() override;

            void draw() override;
            void moveUp();
            void moveDown();
            void moveRight();
            void moveLeft();
            void dropBomb();

        private:

    };
}

#endif /* !PLAYER_HPP_ */
