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
             */
            CreditsScene(std::shared_ptr<Settings> settings);
            ~CreditsScene();

            Scenes handleEvent() override;
            void draw() override;

        protected:
        private:
            /**
             * @brief Call back function executed when back button is pressed to set next scene to settings scene
             */
            void back();

            std::vector<std::unique_ptr<Object::Image>> _parallax; //< Vector of every Images of the parallax

    };
}

#endif /* !CREDITSSCENE_HPP_ */
