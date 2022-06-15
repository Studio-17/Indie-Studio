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
    /**
     * @brief Settings Scene object to handle and display Option Settings Scene
     */
    class StartGameScene : public AScene {
        public:
            /**
             * @brief Construct a new Start Game Scene object
             *
             * @param settings Shared pointer to Settings class
             */
            StartGameScene(std::shared_ptr<Settings> settings);
            ~StartGameScene();

            Scenes handleEvent() override;
            void draw() override;

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

            std::vector<std::unique_ptr<Object::Image>> _parallax; ///< Vector of every Images of the parallax

            Object::Render::MyTexture _buttonTexture; ///< Texture of every Button of the Scene
    };
}

#endif /* !STARTGAMESCENE_HPP_ */
