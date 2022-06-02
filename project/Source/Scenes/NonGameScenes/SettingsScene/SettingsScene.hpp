/*
** EPITECH PROJECT, 2022
** project
** File description:
** SettingsScene
*/

#ifndef SETTINGSSCENE_HPP_
    #define SETTINGSSCENE_HPP_

    #include <vector>
    #include <map>

    #include "AScene.hpp"
    #include "Music.hpp"
    #include "Map.hpp"
    #include "Explosion.hpp"
    #include "Player.hpp"
    #include "Bonus.hpp"
    #include "Bomb.hpp"
/**
 * @brief The settings scene of the game
 */
namespace Scene {
    enum ORIENTATION {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };

    class SettingsScene : public AScene {
        public:
            SettingsScene(std::shared_ptr<Settings> settings);
            ~SettingsScene();

            void fadeBlack() override;
            Scenes handelEvent() override;
            void exitScene();
            void settingsScene();
            void newGameScene();
            void mainMenuScene();
            void draw();

            int getMovingKeys();
            bool isCollidingBomb(Position margin, std::vector<std::unique_ptr<Object::Player>> &players, int playerNb);

            void placeBomb(Position pos, float lifetime, std::size_t range, Object::PLAYER_ORDER playerNb);

            void setBonus(Position const &position, std::size_t percentageDrop);

        protected:
            bool playerPressesDrop(PlayerAction const &action) { return (action == PlayerAction::Drop); };


        private:
            std::unique_ptr<Object::Map> _gameMap;
            std::vector<std::unique_ptr<Object::Player>> _players;
            std::vector<std::unique_ptr<Object::Bomb>> _bombs;
            std::vector<std::unique_ptr<Object::Bonus>> _bonus;

            std::vector<Position> _playerPositions;
            Vector2 _mapSize;

            std::string _mapFile;

            float _margin;
            float _playerSpeed;
    };
}

#endif /* !SETTINGSSCENE_HPP_ */
