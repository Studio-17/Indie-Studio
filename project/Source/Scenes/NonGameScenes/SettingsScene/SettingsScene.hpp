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
    #include "IRenderding.hpp"
    #include "Rendering/Texture.hpp"
/**
 * @brief The settings scene of the game
 */
namespace Scene {
    enum class ORIENTATION {
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
            bool isCollidingBlock(Position margin, std::unique_ptr<Object::Player> &player);
            bool isCollidingBomb(Position margin, std::vector<std::unique_ptr<Object::Player>> &players, int playerNb);

            int roundUp(int nb, int multiple);
            void placeBomb(Position pos, float lifetime, std::size_t range, Object::PLAYER_ORDER playerNb);
            void explodeBomb(std::size_t bombPos);

            void setBonus(Position const &position, std::size_t percentageDrop);

            void loadSceneAssets();

        protected:
            bool playerPressesDrop(PlayerAction const &action) { return (action == PlayerAction::Drop); };
            bool playerCanMove(Position const &movement, int playerIndex) { return (!isCollidingBlock(movement, _players.at(playerIndex)) && !isCollidingBomb(movement, _players, playerIndex)); };

        private:
            std::unique_ptr<Object::Map> _gameMap;
            std::vector<std::unique_ptr<Object::Player>> _players;
            std::vector<std::unique_ptr<Object::Bomb>> _bombs;
            std::vector<std::unique_ptr<Object::Bonus>> _bonus;

            // std::unique_ptr<Object::Explosion> _explosion;

            std::vector<Object::Render::MyAnimation> _animations;
            std::vector<Object::Render::MyModel> _models;
            std::vector<Object::Render::MyTexture> _textures;
            std::vector<Position> _playerPositions;
            Vector2 _mapSize;

            std::string _mapFile;

            float _margin;
            float _playerSpeed;
    };
}

#endif /* !SETTINGSSCENE_HPP_ */
