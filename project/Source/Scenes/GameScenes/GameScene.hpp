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
            /**
             * @brief Construct a new Game Scene object
             * 
             * @param settings 
             * @param gameSettings 
             */
            GameScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings);
            /**
             * @brief Destroy the Game Scene object
             * 
             */
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


            void handleAi(std::map<PlayerAction, bool> &tmp, std::shared_ptr<Object::Player> const &ai, int indexAi);
            std::vector<PlayerAction> getPossibleDir(std::shared_ptr<Object::Player> const &ai, int indexAi);
            std::vector<std::pair<int, Position>> checkPlayerPos(Position const &aiPos, int indexAi);
            std::vector<std::pair<int, int>> stockForbiddenCells(std::shared_ptr<Object::Player> const &ai, int indexAi);
            bool checkAiIsSafe(std::shared_ptr<Object::Player> const &ai);
            bool checkAiIsSafe(std::shared_ptr<Object::Player> const &ai, std::pair<int, int> const &aiPos);


        protected:
            bool playerPressesDrop(PlayerAction const &action) { return (action == PlayerAction::Drop); };

            bool isCollidingBomb(Position const &direction, Position const &playerPosition, Object::PLAYER_ORDER playerNb);

            /* Draw part */
            void drawObjects();

            /*              */
            void resumeGame();

            void save();

        protected:
        private:
            void setCameraView();

            std::shared_ptr<GameSettings> _gameSettings; //!< Shared pointer to Game Settings class

            std::vector<std::unique_ptr<Object::Image>> _backgroundImage; //!< Vector of unique pointer to Image class

            bool _3dcameraVue; //!< Boolean to know if 3d camera is enabled or not

            Clock _clockGame; //!< Clock to manage game time

            std::size_t _timePerRound; //!< Time per round

            std::shared_ptr<Object::Map> _gameMap; //!< Shared pointer to Map class
            std::size_t _placement; //!< Placement of the map
            std::map<std::size_t, Object::PLAYER_ORDER> _mapStatistics; //!< Map of statistics of the map

            bool _endGame; //!< Boolean to know if game is ended or not

            std::map<Object::PLAYER_ORDER, std::shared_ptr<Object::Player>> _players; //!< Map of players
            std::vector<std::size_t> _playerSkin; //!< Vector of player skin
            std::vector<std::pair<std::size_t, std::vector<std::unique_ptr<Object::Image>>>> _playersIcons; //!< Vector of players with their skins
            std::vector<std::unique_ptr<Object::Text>> _playerParameters; //!< Vector of player with their writed parameters
            float _playerSpeed; //!< Player speed

            std::vector<std::unique_ptr<Object::Bomb>> _bombs; //!< Vector of bombs
            float _timeBeforeBombExplosion; //!< Time before bomb explosion

            std::map<int, std::map<int, float>> _explosions; //!< Map of explosions

            std::map<int, std::map<int, std::unique_ptr<Object::Bonus>>> _bonus; //!< Map of bonuses

            std::vector<Object::Render::MyAnimation> _animations; //!< Vector of animations
            std::vector<Object::Render::MyModel> _models; //!< Vector of models
            std::vector<Object::Render::MyTexture> _textures; //!< Vector of textures

            std::map<std::string, std::pair<float, float>> _defaultAttributes; //!< Map of default attributes
            std::size_t _percentageBonusDrop; //!< Percentage of bonus drop
            std::size_t _percentageBoxDrop; //!< Percentage of box drop

            float _margin; //!< Margin
            std::map<PlayerAction, Position> _collisionCondition; //!< Map of collision conditions

            // int _action;
            // std::vector<PlayerAction> _iaPossibleDirection;
            // std::vector<std::pair<int, int>> _aiForbiddenCells;

            // std::vector<int, std::vector<std::pair<PlayerAction, std::vector<Position>>>> _aiBombExplosion;

            const std::map<PlayerAction, std::pair<Position, Position>> _actionMap; //!< Map of actions

            std::unique_ptr<Scene::PauseScene> _pauseScene; //!< Pause scene
            bool _isPaused; //!< Is paused
    };
}

#endif /* !GAMESCENE_HPP_ */
