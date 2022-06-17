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
            Ai(Object::PLAYER_ORDER id, std::shared_ptr<Object::Player> const &player, std::shared_ptr<Object::Map> const &gameMap);
            ~Ai();

            void handleEvent(std::map<PlayerAction, bool> &aiAction, std::vector<std::unique_ptr<Object::Bomb>> const &bombs);

            std::vector<PlayerAction> getPossibleDir();
            std::vector<std::pair<int, int>> stockForbiddenCells(std::vector<std::unique_ptr<Object::Bomb>> const &bombs);

        protected:
        private:
            Object::PLAYER_ORDER _id;
            std::shared_ptr<Object::Player> _aiPlayer;
            std::shared_ptr<Object::Map> _gameMap;
            float _margin;
            std::map<PlayerAction, Position> _collisionCondition;


            bool _isMoving = false; ///< is moving
            // bool _isSafe = true; ///< is safe
            // bool _allowForbiddenCells = false; ///< allow forbidden cells
            int _actionMove = 0; ///< action move
            std::vector<PlayerAction> _possibleDirection; ///< ia possible direction
            std::vector<std::pair<int, int>> _forbiddenCells; ///< ai forbidden cells


    };
}

#endif /* !AI_HPP_ */
