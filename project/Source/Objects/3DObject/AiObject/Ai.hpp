/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Ai
*/

#ifndef AI_HPP_
    #define AI_HPP_

    #include <utility>

    #include "Player.hpp"
    #include "Settings.hpp"
    #include "Map.hpp"
    #include "Position.hpp"
    #include "Bomb.hpp"

namespace Object {

    /**
     * @brief Ai class
     */
    class Ai {
        public:
            /**
             * @brief Construct a new Ai object
             *
             * @param id index of the player
             * @param player player who is assigned to Ai
             * @param gameMap map of the game
             */
            Ai(Object::PLAYER_ORDER id, std::shared_ptr<Object::Player> const &player, std::shared_ptr<Object::Map> const &gameMap);
            /**
             * @brief Destroy the Ai object
             */
            ~Ai();

            /**
             * @brief AI event management
             *
             * @param aiAction map of ai action
             * @param bombs list of all bombs in map
             */
            void handleEvent(std::map<PlayerAction, bool> &aiAction, std::vector<std::unique_ptr<Object::Bomb>> const &bombs);

            /**
             * @brief Get possible direction for Ai (ex: left, right, up, down)
             *
             * @return std::vector<PlayerAction>
             */
            std::vector<PlayerAction> getPossibleDir();
            /**
             * @brief Storing AI bombs to avoid going there
             *
             * @param bombs list of all bombs in map
             * @return std::vector<std::pair<int, int>>
             */
            std::vector<std::pair<int, int>> stockForbiddenCells(std::vector<std::unique_ptr<Object::Bomb>> const &bombs);
            /**
             * @brief Looking ai position to determine if he is safe
             *
             * @return true
             * @return false
             */
            bool checkAiIsSafe();
            bool checkAiIsSafe(std::pair<int, int> newPosAi);
            bool validDir(PlayerAction action);

        protected:
        private:
            Object::PLAYER_ORDER _id; ///< index of the player
            std::shared_ptr<Object::Player> _aiPlayer; ///< player who is assigned to Ai
            std::shared_ptr<Object::Map> _gameMap; ///< map of the game

            float _margin; ///< margin for collision detection
            std::map<PlayerAction, Position> _collisionCondition; ///< condition for collision detection

            bool _isMoving = false; ///< is moving
            bool _isSafe = true; ///< is safe
            int _actionMove = 0; ///< action move
            std::vector<PlayerAction> _possibleDirection; ///< ia possible direction
            std::vector<std::pair<int, int>> _forbiddenCells; ///< ai forbidden cells
    };
}

#endif /* !AI_HPP_ */
