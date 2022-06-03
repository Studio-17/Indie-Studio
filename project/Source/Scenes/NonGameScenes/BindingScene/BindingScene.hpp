/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** BindingScene
*/

#ifndef BINDINGSCENE_HPP_
    #define BINDINGSCENE_HPP_

    #include "Keyboard.hpp"
    #include "AScene.hpp"

namespace Scene {
    class BindingScene : public AScene {
        public:
            BindingScene(std::shared_ptr<Settings> settings, Keyboard &keyboard, std::vector<std::map<PlayerAction, int>> const &playerAction, std::function<void(int, int, int)> bindingFunction);
            ~BindingScene();

            void fadeBlack() override;
            Scenes handleEvent() override;
            void draw() override;

        protected:
        private:
            void exitScene();
            void settingsScene();
            void newGameScene();

            std::vector<std::unique_ptr<Object::Image>> _parallax;
            Keyboard &_keyboard;
            std::vector<std::map<PlayerAction, int>> _playerAction;
            std::function<void(int, int, int)> _bindingFunction;
            int _buttonIndex;
            int _buttonOpened;
    };
}

#endif /* !BINDINGSCENE_HPP_ */
