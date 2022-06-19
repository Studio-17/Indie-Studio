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
    #include "Ai.hpp"
    #include "Bonus.hpp"
    #include "Bomb.hpp"
    #include "IRenderding.hpp"
    #include "Texture.hpp"
    #include "PauseScene.hpp"

namespace Scene {

    /**
     * @brief Enum to define the orientation
     */
    enum class ORIENTATION {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };

    /**
     * @brief Game Scene object to handle and display Game Scene
     */
    class GameScene : public AScene {
        public:
            /**
             * @brief Construct a new Game Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param gameSettings Shared pointer to Game Settings class
             */
            GameScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings);
            /**
             * @brief Destroy the Game Scene object
             */
            ~GameScene();
            /**
             * @brief Initialize the Game Scene object
             */
            void loadSceneAssets();

            /**
             * @brief apply game params
             */
            void applyGameParams();

            /**
             * @brief restart set
             */
            void restartSet();
            /**
             * @brief load Game from json Data
             *
             * @param jsonData list containing all datas of game
             */
            void loadFromSave(nlohmann::json const &jsonData);

            /**
             * @brief Handle the event of the scene
             *
             * @return Scenes
             */
            Scenes handleEvent() override;
            /**
             * @brief Draw the scene
             */
            void draw() override;

            /* Handle part */
            /**
             * @brief Check if the game is end and set the scores
             */
            void handleWin();

            /**
             * @brief handle player the action of the players
             */
            void handlePlayers();
            /**
             * @brief place a bomb at position by a player
             *
             * @param pos position to place the bomb
             * @param playerNb index of the player who place the bomb
             */
            void placeBomb(Position const &pos, Object::PLAYER_ORDER playerNb);
            /**
             * @brief handle the collision of players with bonus
             *
             * @param playerPosition position of the player
             * @param playerNb index of the player
             */
            void CollideObject(Position const &playerPosition, Object::PLAYER_ORDER playerNb);
            /**
             * @brief attribute bonus to a player
             *
             * @param playerNb index of the player
             * @param bonus type of bonus
             */
            void AwardBonus(Object::PLAYER_ORDER playerNb, Object::BONUS_OBJECTS bonus);

            /**
             * @brief handle bomb explosion and countdown
             */
            void handleBombs();
            /**
             * @brief explosion bomb
             *
             * @param position bomb position
             * @param radius size of bomb explosion
             */
            void exploseBomb(Position const &position, int radius);
            /**
             * @brief draw explosion animation
             *
             * @param time time of explosion animation
             * @param position position of explosion animation
             */
            void placeExplosions(float time, Position position);
            /**
             * @brief Check if player is in range of an explosion
             *
             * @param explosionPos list of explosions positions
             */
            void checkIfPlayerIsInRange(std::pair<int, int> const &explosionPos);
            /**
             * @brief place a bonus on the map
             *
             * @param position bonus position
             * @param percentageDrop percentage of the bonus to drop
             */
            void placeBonus(std::pair<int, int> position, std::size_t percentageDrop);
            /**
             * @brief handle bonus parameters
             */
            void handleBonusParameters();

            /**
             * @brief handle pause menu
             */
            void handlePause();
            /**
             * @brief Set the Bomb To Pause object
             *
             * @param pause is game in pause
             */
            void setBombToPause(bool pause);

            /**
             * @brief handle explosions
             */
            void handleExplosions();
            /**
             * @brief handle game timer
             */
            void handleTimer();
            /**
             * @brief print the actual set of the game
             * 
             */
            void handleSets();
            /**
             * @brief print the winner at the end of every set;
             * 
             */
            void handleEndSet(std::size_t winner);

            /**
             * @brief handle camera in the cinematic
             */
            void handleCinematicCamera();
        protected:
            /**
             * @brief Check if the player want to drop a bomb
             *
             * @param action tyoe of action
             * @return true if player press the key to drop a bomb
             * @return false if player doesn't press the key to drop a bomb
             */
            bool playerPressesDrop(PlayerAction const &action) { return (action == PlayerAction::Drop); };

            /**
             * @brief Check if player is colliding a bomb
             *
             * @param direction vector of player direction
             * @param playerPosition position of the player
             * @param playerNb index of the player
             * @return true if player is colliding a bomb
             * @return false if player is not colliding a bomb
             */
            bool isCollidingBomb(Position const &direction, Position const &playerPosition, Object::PLAYER_ORDER playerNb);

            /* Draw part */
            /**
             * @brief draw objects
             */
            void drawObjects();
            void drawUserInterface();

            /*              */
            /**
             * @brief resume game when the game is in pause
             */
            void resumeGame();

            /**
             * @brief save the game
             */
            void save();

        protected:
        private:
            /**
             * @brief switch camera view
             */
            void changeCameraView();
            /**
             * @brief Set the Camera View object
             */
            void setCameraView();

            std::shared_ptr<GameSettings> _gameSettings; //!< Shared pointer to Game Settings class

            std::vector<std::unique_ptr<Object::Image>> _backgroundImage; //!< Background image of the game
            std::vector<std::unique_ptr<Object::Text>> _endingGameText; //!< Text of the ending game

            bool _3dcameraVue; //!< Boolean to know if 3d camera is enabled or not

            Clock _gameClock; //!< Clock to manage game time
            Clock _cameraClock; //!< Clock to manage the cinematic camera time
            Clock _endSetClock; //!< Clock to manage the end of the set time

            std::size_t _timePerRound; //!< Time per round
            int _elapsedTime; //!< Elapsed time

            std::shared_ptr<Object::Map> _gameMap; //!< Shared pointer to Map class
            std::vector<std::pair<std::size_t, Object::PLAYER_ORDER>> _mapStatistics; //!< Statistics of the players for the podium

            bool _endGame; //!< Boolean to know if game is ended or not
            bool _endSet; //!< Boolean to know if set is ended or not

            std::map<Object::PLAYER_ORDER, std::shared_ptr<Object::Player>> _players; //!< Map of players
            std::map<Object::PLAYER_ORDER, std::shared_ptr<Object::Ai>> _ai;
            std::vector<std::size_t> _playerSkin; //!< Vector of player skin
            std::vector<std::vector<std::unique_ptr<Object::Image>>> _playersIcons; //!< Vector of players with their skins
            std::vector<std::vector<std::unique_ptr<Object::Image>>> _setsIcons; //!< Vector of stars for sets for each player
            std::vector<std::unique_ptr<Object::Text>> _playerParameters; //!< Vector of player with their writed parameters
            float _playerSpeed; //!< Player speed

            std::vector<std::unique_ptr<Object::Text>> _startingGameTexts;

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

            const std::map<PlayerAction, std::pair<Position, Position>> _actionMap; //!< Map of actions

            std::unique_ptr<Scene::PauseScene> _pauseScene; //!< Pause scene
            bool _isPaused; //!< Is paused
            std::size_t _actualSet; //!< Actual set
            bool _cinematicCamera; //!< Cinematic camera

    };
}

#endif /* !GAMESCENE_HPP_ */
