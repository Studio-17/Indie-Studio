/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_HPP_
    #define MAINMENUSCENE_HPP_

    #include "AScene.hpp"

namespace Scene {
    /**
     * @brief Main Menu Scene object to handle and display Main Menu Scene
     */
    class MainMenuScene : public AScene {
        public:
            /**
             * @brief Construct a new Main Menu Scene object
             *
             * @param settings Shared pointer to Settings class
             */
            MainMenuScene(std::shared_ptr<Settings> settings);
            ~MainMenuScene();

            Scenes handleEvent() override;
            void draw() override;

        protected:
        private:
            /**
             * @brief Call back function executed when exit button is pressed to exit program
             */
            void exitScene();
            /**
             * @brief Call back function executed when settings button is pressed to set next scene to settings scene
             */
            void settingsScene();
            /**
             * @brief Call back function executed when start game button is pressed to set next scene to start game scene
             */
            void gameScene();

            std::vector<std::unique_ptr<Object::Image>> _parallax; ///< Vector of every Images of the parallax

            Object::Render::MyTexture _buttonTexture; ///< Texture of every Button of the Scene
    };
}

#endif /* !MAINMENUSCENE_HPP_ */
