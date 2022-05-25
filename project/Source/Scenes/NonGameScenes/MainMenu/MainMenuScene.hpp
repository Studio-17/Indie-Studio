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

    enum class BUTTONSNAME {
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

            std::map<BUTTONSNAME, std::unique_ptr<Object::Button>> _buttons;



    };
}

#endif /* !MAINMENUSCENE_HPP_ */
