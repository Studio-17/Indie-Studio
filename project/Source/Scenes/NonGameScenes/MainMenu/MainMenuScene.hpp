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
    #include "Button.hpp"

namespace Scene {

    enum BUTTONSNAME {
        NEWGAME,
        LOADGAME,
        EXIT,
        SETTINGS
    };
    class MainMenuScene : public AScene {
        public:
            MainMenuScene(std::shared_ptr<Settings> settings);
            ~MainMenuScene();

            Scenes run() override;
            void fadeBlack() override;
            Scenes handelEvent() override;
            void testFunction();
            void draw();

        protected:
        private:
            bool _isRunning;
            Scene::Scenes _scenes;
            Object::Button _button;
            Object::Button _button2;
            Object::Button _button3;

            // std::vector<std::map<BUTTONSNAME, Object::Button>> _buttons;



    };
}

#endif /* !MAINMENUSCENE_HPP_ */
