/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectPlayerScene
*/

#ifndef SELECTPLAYERSCENE_HPP_
    #define SELECTPLAYERSCENE_HPP_

    #include "AScene.hpp"
    #include "GameSettings.hpp"

namespace Scene {
    /**
     * @brief Select Player Scene object to handle and display Option Select Player Scene
     */
    class SelectPlayerScene : public AScene {
        public:
            /**
             * @brief Construct a new Select Player Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param gameSettings Shared pointer to Game Settings class
             * @param parallax Vector of unique pointer of Object::Image class
             * @param applyGameSettings Callback function to apply game settings
             */
            SelectPlayerScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::unique_ptr<Object::Image>> &parallax, std::function<void(void)> applyGameSettings);
            /**
             * @brief Destroy the Select Player Scene object
             */
            ~SelectPlayerScene();

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
            /**
             * @brief handle action
             */
            void handleAction();
        protected:
            /**
             * @brief Exit the scene
             */
            void exitSelectPlayerScene();
            /**
             * @brief Run the game
             */
            void runGame();
            /**
             * @brief Change skin player in the previous skin in the skin list
             *
             * @param index std::size_t of player index
             */
            void leftClick(std::size_t index);
            /**
             * @brief Change skin player in the next skin in the skin list
             *
             * @param index std::size_t of player index
             */
            void rightClick(std::size_t index);
            /**
             * @brief Change the icon that indicates if the player is played by an AI or a human
             *
             * @param index std::size_t of player index
             */
            void SetInfoOfPlayers(std::size_t index);

        private:
            std::shared_ptr<GameSettings> _gameSettings; ///< Shared pointer to game Settings class
            std::vector<std::pair<std::size_t, std::vector<std::unique_ptr<Object::Image>>>> _players; ///< Vector of players with their skins
            std::vector<std::pair<std::size_t, std::vector<std::unique_ptr<Object::Text>>>> _playerColors; ///< Vector of player colors

            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax
            std::vector<std::unique_ptr<Object::Image>> _popPlayerNames; ///< Vector of every Images of the pop player names
            std::vector<std::unique_ptr<Object::Image>> _playersInfo; ///< Vector of every Images of the icon infos
            std::function<void(void)> _applyGameSettings; ///< Function to apply game settings
            std::vector<Position> _colorBar; ///< Vector of every position of the color bar
            std::size_t _activeButton; ///< Index of the active button
    };
}

#endif /* !SELECTPLAYERSCENE_HPP_ */
