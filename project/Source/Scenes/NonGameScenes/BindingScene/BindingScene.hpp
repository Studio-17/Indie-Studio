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
    /**
     * @brief Binding Scene object to handle and display Binding Scene
     */
    class BindingScene : public AScene {
        public:
            /**
             * @brief Construct a new Binding Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param keyboard Reference to Keyboard object
             * @param playerAction Vector of map of key corresponding of a player action
             * @param bindingFunction Function to bind an action by a key
             */
            BindingScene(std::shared_ptr<Settings> settings, Keyboard &keyboard, std::vector<std::map<PlayerAction, int>> const &playerAction, std::function<void(int, int, int)> bindingFunction);
            ~BindingScene();

            Scenes handleEvent() override;
            void draw() override;

        protected:
        private:
            /**
             * @brief Call back function executed when back button is pressed to set next scene to settings scene
             */
            void back();
            /**
             * @brief Call back function executed when binding button is pressed to display popUp of new key setting
             */
            void bindKey();
            /**
             * @brief Call back function executed when close button of the popUp is pressed to close the popUp
             */
            void cancelBind();

            std::vector<std::unique_ptr<Object::Image>> _parallax; ///< Vector of every Images of the parallax
            std::vector<std::unique_ptr<Object::Image>> _popUp; ///< Vector of every Images of binding popUp
            std::vector<std::unique_ptr<Object::Text>> _popUpText; ///< Vector of every Texts of binding popUp
            std::vector<std::unique_ptr<Object::Button>> _popUpButton; ///< Vector of every Buttons of binding popUp
            Keyboard &_keyboard; ///< Keyboard object to get pressed key
            std::vector<std::map<PlayerAction, int>> _playerAction; ///< Vector of map of key corresponding of a player action
            std::function<void(int, int, int)> _bindingFunction; ///< Function to bind an action by a key
            int _buttonIndex; ///< index of button when handleling an event
            int _buttonOpened; ///< index of button wich opened the popUp
    };
}

#endif /* !BINDINGSCENE_HPP_ */
