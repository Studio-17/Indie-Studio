/*
** EPITECH PROJECT, 2022
** project
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

    #include "AThreeDimensionObject.hpp"
    #include "Player.hpp"
    #include "clock.hpp"

namespace Object
{
    class Bomb : public AThreeDimensionObject {
        public:
            Bomb(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::PLAYER_ORDER player, float lifeTime, std::size_t range);
            ~Bomb() override;

            void draw() override;

            bool checkIfShouldExplode();

            void animation();

            void explode();

            Object::PLAYER_ORDER getPlayer() { return _player; };

            bool getCollide() { return _collide; };
            void setCollide(bool value) { _collide = value; };

            std::size_t getRange() { return _range; };
            void setRange(std::size_t value) { _range = value; };

        protected:
        private:
            Clock _bombClock{};
            float _lifeTime;
            std::size_t _range;
            float _bombScale;
            bool _collide;
            Object::PLAYER_ORDER _player;
    };
}

#endif /* !BOMB_HPP_ */
