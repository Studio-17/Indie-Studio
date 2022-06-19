/*
** EPITECH PROJECT, 2022
** project
** File description:
** StartGameScene
*/

#ifndef STARTGAMESCENE_HPP_
    #define STARTGAMESCENE_HPP_

    #include <functional>

    #include "AScene.hpp"

namespace Scene {
    /**
     * @brief Settings Scene object to handle and display Option Settings Scene
     */
    class StartGameScene : public AScene {
        public:
            /**
             * @brief Construct a new Start Game Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param parallax Vector of unique pointer of Object::Image class
             * @param updateSaveFiles Callback function to update Save File list
             */
            StartGameScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax, std::function<void(void)> updateSaveFiles);
            /**
             * @brief Destroy the Start Game Scene object
             */
            ~StartGameScene();

            /**
             * @brief Handle the event of the scene
             *
             * @return Scenes
             */
            Scenes handleEvent() override;
            /**
             * @brief Draw the scene
             */
            void draw() override;
            /**
             * @brief handle action
             */
            void handleAction();
        protected:
        private:
            /**
             * @brief Call back function executed when new game button is pressed to set next scene to new game scene
             */
            void newGameScene();
            /**
             * @brief Call back function executed when load save button is pressed to set next scene to load save scene
             */
            void loadSaveScene();
            /**
             * @brief Call back function executed when back button is pressed to set next scene to main menu scene
             */
            void backScene();

            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax

            Object::Render::MyTexture _buttonTexture; ///< Texture of every Button of the Scene
            std::function<void(void)> _updateSaveFiles; ///< Function to update saveFiles to show in select Save Scene
            std::size_t _activeButton; ///< Index of the active button
    };
}

#endif /* !STARTGAMESCENE_HPP_ */
