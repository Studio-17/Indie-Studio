/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_HPP_
    #define MAINMENUSCENE_HPP_

    #include "AScene.hpp"
    #include "Music.hpp"
    #include "Image.hpp"

namespace Scene {

    class MainMenuScene : public AScene {
        public:
            MainMenuScene(std::shared_ptr<Settings> settings);
            ~MainMenuScene();

            void fadeBlack() override;
            Scenes handelEvent() override;
            void draw() override;

        protected:
            void exitScene();
            void settingsScene();
            void newGameScene();
        private:
    };
}

#endif /* !MAINMENUSCENE_HPP_ */
