/*
** EPITECH PROJECT, 2022
** project
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
    #define GAMESCENE_HPP_

    #include "AScene.hpp"
    #include "GameSettings.hpp"
    #include "Map.hpp"
    #include "Player.hpp"
    #include "Bonus.hpp"
    #include "Bomb.hpp"
    #include "IRenderding.hpp"
    #include "Texture.hpp"
    #include "PauseScene.hpp"

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

            void loadSceneAssets();
            void applyGameParams();

            Scenes handleEvent() override;
            void draw() override;

            /* Handle part */
            void handleWin();

            void handlePlayers();
            void placeBomb(Position const &pos, Object::PLAYER_ORDER playerNb);
            void CollideObject(Position const &playerPosition, Object::PLAYER_ORDER playerNb);
            void AwardBonus(Object::PLAYER_ORDER playerNb, Object::BONUS_OBJECTS bonus);

            void handleBombs();
            void exploseBomb(Position const &position, int radius);
            void placeExplosions(float time, Position position);
            void checkIfPlayerIsInRange(std::pair<int, int> const &explosionPos);
            void placeBonus(std::pair<int, int> position, std::size_t percentageDrop);

            void handlePause();
            void setBombToPause(bool pause);

            void handleExplosions();
            void handleTimer();

            bool isCollidingBomb(Position const &direction, Position const &playerPosition, Object::PLAYER_ORDER playerNb);

            /* Draw part */
            void drawObjects();

            /*              */
            void resumeGame();

            void save();

        protected:
        private:
            void setCameraView();

            std::shared_ptr<GameSettings> _gameSettings;

            std::vector<std::unique_ptr<Object::Image>> _backgroundImage;

            bool _3dcameraVue;

            Clock _clockGame;

            std::size_t _timePerRound;

            std::shared_ptr<Object::Map> _gameMap;

            std::map<Object::PLAYER_ORDER, std::shared_ptr<Object::Player>> _players;
            float _playerSpeed;

            std::vector<std::unique_ptr<Object::Bomb>> _bombs;
            float _timeBeforeBombExplosion;

            std::map<int, std::map<int, float>> _explosions;

            std::map<int, std::map<int, std::unique_ptr<Object::Bonus>>> _bonus;

            std::vector<Object::Render::MyAnimation> _animations;
            std::vector<Object::Render::MyModel> _models;
            std::vector<Object::Render::MyTexture> _textures;

            std::map<std::string, std::pair<float, float>> _defaultAttributes;
            std::size_t _percentageBonusDrop;
            std::size_t _percentageBoxDrop;

            float _margin;
            std::map<PlayerAction, Position> _collisionCondition;
            const std::map<PlayerAction, std::pair<Position, Position>> _actionMap;

            std::unique_ptr<Scene::PauseScene> _pauseScene;
            bool _isPaused;
    };
}

#endif /* !GAMESCENE_HPP_ */
