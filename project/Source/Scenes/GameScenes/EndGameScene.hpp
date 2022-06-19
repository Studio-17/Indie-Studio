/*
** EPITECH PROJECT, 2022
** project
** File description:
** EndGameScene
*/

#ifndef ENDGAMESCENE_HPP_
    #define ENDGAMESCENE_HPP_

    #include "AScene.hpp"
    #include "GameSettings.hpp"
    #include "tools.hpp"
    #include "Settings.hpp"
    #include "Player.hpp"

namespace Scene {
    /**
     * @brief End game Scene object to handle and display end game Scene
     */
    class EndGameScene : public AScene {
        public:
            /**
             * @brief Construct a new End Game Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param gameSettings Shared pointer to Game Settings class
             */
            EndGameScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::unique_ptr<Object::Image>> &parallax, std::function<void(void)> _restartCallBack);
            ~EndGameScene();

            Scenes handleEvent() override;
            void draw () override;

            /**
             * @brief Call back function executed when next button is pressed to set next scene to main menu scene
            */
            void goToMainMenu();

            /**
             * @brief Call back function executed to restart the game
            */
            void restartGame();

            void drawPlayerNameAndScore(Object::PLAYER_ORDER player, std::size_t score, std::size_t nbText);
            void drawScore();

        protected:
        private:
            std::vector<std::unique_ptr<Object::Image>> &_parallax;
            std::vector<std::unique_ptr<Object::Image>> _winner;
            std::shared_ptr<GameSettings> _gameSettings;
            int _winnerId;
            std::function<void(void)> _restartGameCallBack;
    };
}

#endif /* !ENDGAMESCENE_HPP_ */
