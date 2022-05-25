/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_HPP_
    #define MAINMENUSCENE_HPP_


    #include <vector>
    #include <map>

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
            void exitScene();
            void settingsScene();
            void newGameScene();
            void draw();

        protected:
        private:
            // bool _isRunning;
            // Scene::Scenes _nextScene;

            // std::map<BUTTONSNAME, std::unique_ptr<Object::Button>> _buttons;
            // std::unique_ptr<MyMusic> _mainMusic;



    };
}

#endif /* !MAINMENUSCENE_HPP_ */
