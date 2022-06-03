/*
** EPITECH PROJECT, 2022
** project
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
    #define GAMESCENE_HPP_


    #include <vector>
    #include <map>

    #include "AScene.hpp"
    #include "GameSettings.hpp"
    #include "Music.hpp"
    #include "Map.hpp"
    #include "Explosion.hpp"
    #include "Player.hpp"
    #include "Bonus.hpp"
    #include "Bomb.hpp"
    #include "IRenderding.hpp"
    #include "Rendering/Texture.hpp"

/**
 * @brief Represents the main game scene
 */
namespace Scene {

    enum class ORIENTATION {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };

    class GameScene : public AScene {
        public:
            GameScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings);
            ~GameScene();

            void fadeBlack() override;
            Scenes handleEvent() override;
            void exitScene();
            void settingsScene();
            void newGameScene();
            void mainMenuScene();
            void draw();

            int getMovingKeys();
            bool isCollidingBomb(Position const &direction, Position const &playerPosition, Object::PLAYER_ORDER playerNb);

            void placeBomb(Position pos, float lifetime, std::size_t range, Object::PLAYER_ORDER playerNb);

            void setBonus(Position const &position, std::size_t percentageDrop);

            void loadSceneAssets();

        protected:
            bool playerPressesDrop(PlayerAction const &action) { return (action == PlayerAction::Drop); };


        private:
            std::shared_ptr<GameSettings> _gameSettings;

            std::unique_ptr<Object::Map> _gameMap;
            std::vector<std::unique_ptr<Object::Player>> _players;
            std::vector<std::unique_ptr<Object::Bomb>> _bombs;
            std::vector<std::unique_ptr<Object::Bonus>> _bonus;

            std::vector<Object::Render::MyAnimation> _animations;
            std::vector<Object::Render::MyModel> _models;
            std::vector<Object::Render::MyTexture> _textures;
            std::vector<Position> _playerPositions;
            Vector2 _mapSize;

            std::string _mapFile;

            float _margin;
            float _playerSpeed;
            const std::map<PlayerAction, std::pair<Position, Position>> _actionMap;
            std::map<PlayerAction, Position> _collisionCondition;
    };
}

#endif /* !GAMESCENE_HPP_ */
