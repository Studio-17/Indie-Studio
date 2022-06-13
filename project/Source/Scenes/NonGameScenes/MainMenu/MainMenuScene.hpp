/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_HPP_
    #define MAINMENUSCENE_HPP_

    #include "AScene.hpp"

namespace Scene {

    class MainMenuScene : public AScene {
        public:
            MainMenuScene(std::shared_ptr<Settings> settings);
            ~MainMenuScene();

            Scenes handleEvent() override;
            void draw() override;

        protected:
        private:
            void exitScene();
            void settingsScene();
            void gameScene();
        private:
            std::vector<std::unique_ptr<Object::Image>> _parallax;

            Object::Render::MyTexture _buttonTexture;
    };
}

#endif /* !MAINMENUSCENE_HPP_ */
