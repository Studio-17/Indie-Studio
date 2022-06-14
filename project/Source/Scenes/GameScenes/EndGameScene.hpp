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
            EndGameScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::map<Object::PLAYER_ORDER, std::size_t> = {});
            ~EndGameScene();

            void loadSceneAssets();
            void goToMainMenu();
            void draw () override;
            Scenes handleEvent() override;

        protected:
        private:
            std::vector<std::unique_ptr<Object::Image>> _parallax;
            std::map<Object::PLAYER_ORDER, std::size_t> _playerCharacteristics;
    };
}

#endif /* !ENDGAMESCENE_HPP_ */
