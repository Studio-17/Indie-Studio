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

namespace Scene {
    class EndGameScene : public AScene {
        public:
            EndGameScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings);
            ~EndGameScene();

            void loadSceneAssets();
            void goToMainMenu();
            void draw () override;
            Scenes handleEvent() override;

        protected:
        private:
            std::vector<std::unique_ptr<Object::Image>> _parallax;
    };
}

#endif /* !ENDGAMESCENE_HPP_ */
