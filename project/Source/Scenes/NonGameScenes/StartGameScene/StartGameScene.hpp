/*
** EPITECH PROJECT, 2022
** project
** File description:
** StartGameScene
*/

#ifndef STARTGAMESCENE_HPP_
    #define STARTGAMESCENE_HPP_

    #include "AScene.hpp"

namespace Scene {
    class StartGameScene : public AScene {
        public:
            StartGameScene(std::shared_ptr<Settings> settings);
            ~StartGameScene();

            Scenes handleEvent() override;
            void draw() override;

        protected:

        private:
            void newGameScene();
            void loadSaveScene();
            void backScene();
        private:
            std::vector<std::unique_ptr<Object::Image>> _parallax;
    };
}

#endif /* !STARTGAMESCENE_HPP_ */
