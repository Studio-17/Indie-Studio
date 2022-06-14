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
    #include "Player.hpp"
    #include "Bonus.hpp"
    #include "Bomb.hpp"
    #include "IRenderding.hpp"
    #include "Rendering/Texture.hpp"
    #include "PauseScene.hpp"
    #include "tools.hpp"
    #include "Settings.hpp"

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

            Scenes handleEvent() override;
            void exitScene();
            void settingsScene();
            void newGameScene();
            void mainMenuScene();
            void draw() override;

            int getMovingKeys();

            void setCameraVue();

            bool isCollidingObject(Position const &direction, Position const &playerPosition, Object::PLAYER_ORDER playerNb);

            void handleBombs();
            void placeBomb(Position pos, float lifetime, std::size_t range, Object::PLAYER_ORDER playerNb);
            void exploseBomb(Position const &position, int radius);

            void placeExplosions(float time, Position position);
            void handleExplosions();

            void handlePlayers();

            void handleButtons();

            void handlePause();

            void placeBonus(std::pair<int, int> position, std::size_t percentageDrop);
            void AwardBonus(Object::PLAYER_ORDER playerNb, Object::BONUS_OBJECTS bonus);
            void drawObjects();

            void loadSceneAssets();

            void ai(std::map<PlayerAction, bool> &tmp, std::shared_ptr<Object::Player> const &player, int indexPlayer);
            std::vector<PlayerAction> getPossibleDir(Position const &aiPos);
            std::vector<std::pair<int, Position>> checkPlayerPos(Position const &aiPos, int indexPlayer);
            // void dropBombToPlayer();
            // std::vector<Position> getExplodedCells(PlayerAction const &action, Position const &bombPos);
            std::vector<std::pair<int, int>> stockForbiddenCells(std::shared_ptr<Object::Player> const &ai);
            bool checkAiIsSafe(std::unique_ptr<Object::Player> const &ai);


        protected:
            bool playerPressesDrop(PlayerAction const &action) { return (action == PlayerAction::Drop); };
            void checkIfPlayerIsInRange(std::pair<int, int> const &explosionPos);

            void printTimer();

            void handleWin();

            void resumeGame();

            void save();

            void setBombToPause(bool pause);


        protected:
        private:
            std::shared_ptr<GameSettings> _gameSettings;

            std::vector<std::unique_ptr<Object::Image>> _backgroundImage;

            bool _3dcameraVue;

            Clock _clockGame;

            std::size_t _timePerRound;
            std::size_t _actualMinutes;

            std::shared_ptr<Object::Map> _gameMap;
            std::string _mapFile;
            Vector2 _mapSize;

            bool _endGame;

            std::map<std::size_t, std::shared_ptr<Object::Player>> _players;
            std::vector<Position> _playerPositions;
            float _playerSpeed;

            std::vector<std::unique_ptr<Object::Bomb>> _bombs;

            // std::map<size_t, std::pair<Position, float>> _explosions;
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

            int _action;
            bool _aiSafe;
            std::vector<PlayerAction> _dirs;
            std::vector<std::pair<int, int>> _aiForbiddenCells;
            // std::vector<int, std::vector<std::pair<PlayerAction, std::vector<Position>>>> _aiBombExplosion;

            const std::map<PlayerAction, std::pair<Position, Position>> _actionMap;

            std::unique_ptr<Scene::PauseScene> _pauseScene;
            bool _isPaused;
    };
}

#endif /* !GAMESCENE_HPP_ */
