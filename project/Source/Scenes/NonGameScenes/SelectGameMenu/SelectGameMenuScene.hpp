/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectGameMenuScene
*/

#ifndef SELECTGAMEMENUSCENE_HPP_
    #define SELECTGAMEMENUSCENE_HPP_

    #include "AScene.hpp"
    #include "Music.hpp"
    #include "Image.hpp"

namespace Scene {

    class SelectGameMenuScene : public AScene {
        public:
            SelectGameMenuScene(std::shared_ptr<Settings> settings);
            ~SelectGameMenuScene();

            void fadeBlack() override;
            Scenes handelEvent() override;
            void draw() override;

        protected:
            void mainMenuScene();
            void loadGameScene();
            void newGameScene();
        private:
    };
}

#endif /* !SELECTGAMEMENUSCENE_HPP_ */
