/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include "AThreeDimensionObject.hpp"

namespace Object {
    class Player : public AThreeDimensionObject {
        public:
            Player(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position);
            Player(nlohmann::json const &jsonData);
            ~Player() override;

            void draw() override;
            void move(Position const &position);

            void resetAnimation();

            void dropBomb();

        private:

    };
}

#endif /* !PLAYER_HPP_ */
