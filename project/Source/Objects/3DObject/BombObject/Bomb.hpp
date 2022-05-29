/*
** EPITECH PROJECT, 2022
** project
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

    #include "AThreeDimensionObject.hpp"
    #include "clock.hpp"

namespace Object
{
    class Bomb : public AThreeDimensionObject {
        public:
            Bomb(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position, float lifeTime);
            ~Bomb() override;

            void draw() override;

            bool checkIfShouldExplode();
            void animation();
            void explode();


        protected:
        private:
            Clock _bombClock{};
            float _lifeTime;
            std::size_t _range;
    };
}

#endif /* !BOMB_HPP_ */
