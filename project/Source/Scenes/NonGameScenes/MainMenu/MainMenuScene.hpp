/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_HPP_
    #define MAINMENUSCENE_HPP_

    #include "IMenuScene.hpp"

namespace Scene {
    class MainMenuScene : public IMenuScene {
        public:
            MainMenuScene();
            ~MainMenuScene();

            Scenes run() override;
            void fadeBlack() override;
            void handelEvent() override;
            void draw();

        protected:
        private:
            bool _isRunning;
    };
}

#endif /* !MAINMENUSCENE_HPP_ */
