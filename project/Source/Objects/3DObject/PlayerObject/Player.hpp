/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <utility>

    #include "AThreeDimensionObject.hpp"

namespace Object {

    enum class PLAYER_ORDER {
        PLAYER1 = 0,
        PLAYER2,
        PLAYER3,
        PLAYER4
    };

    class Player : public AThreeDimensionObject {
        public:
            Player(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position);
            Player(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToRessources, Object::Render::MyAnimation &pathToAnimation, unsigned int numberOfAnimations, Position const &position);

            Player(nlohmann::json const &jsonData);
            ~Player() override;

            void draw() override;
            void animation(std::size_t animNb);
            void move(Position const &position, Position const &direction);

            void dropBomb(Position const &postion, float timeBeforeExplosion, std::size_t range);

        private:
            float _playerScale;

    };
}

#endif /* !PLAYER_HPP_ */
