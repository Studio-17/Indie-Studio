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
            EndGameScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::map<Object::PLAYER_ORDER, std::size_t> = {});
            ~EndGameScene();

            Scenes handleEvent() override;
            void draw () override;

            void loadSceneAssets();
            /**
             * @brief Call back function executed when next button is pressed to set next scene to main menu scene
             */
            void goToMainMenu();
        protected:
        private:
            std::vector<std::unique_ptr<Object::Image>> _parallax; ///< Vector of every Images of the parallax
            std::map<Object::PLAYER_ORDER, std::size_t> _playerCharacteristics;
    };
}

#endif /* !ENDGAMESCENE_HPP_ */
