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
    class EndGameScene : public AScene {
        public:
            EndGameScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::map<std::size_t, Object::PLAYER_ORDER> = {});
            ~EndGameScene();

            void loadSceneAssets();
            void goToMainMenu();
            void draw () override;
            Scenes handleEvent() override;

            void drawPlayerName(Object::PLAYER_ORDER player, std::size_t nbText);
            void drawScore();

        protected:
        private:
            std::vector<std::unique_ptr<Object::Image>> _parallax;
            std::shared_ptr<GameSettings> _gameSettings;
    };
}

#endif /* !ENDGAMESCENE_HPP_ */
