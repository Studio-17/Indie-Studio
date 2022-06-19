/*
** EPITECH PROJECT, 2022
** project
** File description:
** CreditsScene
*/

#ifndef CREDITSSCENE_HPP_
    #define CREDITSSCENE_HPP_

    #include "AScene.hpp"

namespace Scene {
    /**
     * @brief Credit Scene object to handle and display Credit Scene
     */
    class CreditsScene : public AScene {
        public:
            /**
             * @brief Construct a new Credits Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param parallax Vector of unique pointer of Object::Image class
             */
            CreditsScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax);
            /**
             * @brief Destroy the Option Credits Scene object
             */
            ~CreditsScene();

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

        protected:
        private:
            /**
             * @brief Call back function executed when back button is pressed to set next scene to settings scene
             */
            void back();

            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax

    };
}

#endif /* !CREDITSSCENE_HPP_ */
