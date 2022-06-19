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
    /**
     * @brief Bomb class
     */
    class Bomb : public AThreeDimensionObject {
        public:
            /**
             * @brief Construct a new Bomb object
             *
             * @param pathToRessources pair of path to ressources texture and model
             * @param position 3 dimensional Position
             * @param player enum of player order
             * @param lifeTime float life time value
             * @param range std::size_t range value
             */
            Bomb(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::PLAYER_ORDER player, float lifeTime, std::size_t range);
            /**
             * @brief Destroy the Bomb object
             */
            ~Bomb() override;

            /**
             * @brief draw a tree dimensional object
             */
            void draw() override;

            /**
             * @brief Check if the bomb should explode
             *
             * @return true
             * @return false
             */
            bool checkIfShouldExplode();

            /**
             * @brief Bomb animation
             */
            void animation();

            /**
             * @brief Bomb explosion
             */
            void explode();

            /**
             * @brief Get the Player object
             *
             * @return Object::PLAYER_ORDER
             */
            Object::PLAYER_ORDER getPlayer() { return _player; };

            /**
             * @brief Check if bomb is collide
             *
             * @return true
             * @return false
             */
            bool getCollide() { return _collide; };
            /**
             * @brief Set the collide value
             *
             * @param value _collide value
             */
            void setCollide(bool value) { _collide = value; };

            /**
             * @brief Get range of bomb
             *
             * @return std::size_t
             */
            std::size_t getRange() { return _range; };
            /**
             * @brief Set the Range object
             *
             * @param value std::size_t
             */
            void setRange(std::size_t value) { _range = value; };

            /**
             * @brief Set pause to _bomblock
             */
            void pause();
            /**
             * @brief Set unpause to _bomblock
             */
            void unpause();

        protected:
        private:
            Clock _bombClock; ///< clock for bomb
            float _lifeTime; ///< life time
            std::size_t _range; ///< range
            float _bombScale; ///< scale
            bool _collide; ///< is collide
            Object::PLAYER_ORDER _player; ///< player order value
    };
}

#endif /* !BOMB_HPP_ */
