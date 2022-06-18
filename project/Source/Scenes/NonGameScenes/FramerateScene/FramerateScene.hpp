/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** FramerateScene
*/

#ifndef FRAMERATESCENE_HPP_
    #define FRAMERATESCENE_HPP_

    #include "AScene.hpp"
    #include "GameSettings.hpp"

namespace Scene {
    /**
     * @brief Framerate Scene object to handle and display Framerate Scene
     */
    class FramerateScene : public AScene {
        public:
            /**
             * @brief Construct a new Framerate Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param gameSettings Shared pointer to Game Settings class
             * @param callBack
             * @param saveCallBack Call back function to save game
             */
            FramerateScene(std::shared_ptr<Settings> settings, std::vector<std::function<void(void)>> callBacks);
            /**
             * @brief Destroy the Framerate Scene object
             * 
             */
            ~FramerateScene();

            /**
             * @brief Handle the event of the scene
             * 
             * @return Scenes 
             */
            Scenes handleEvent() override;
            /**
             * @brief Draw the scene
             * 
             */
            void draw() override;

        protected:
        private:
            /**
             * @brief upgrade sound volume by 10
             */
            void downgradeFramerate();
            /**
             * @brief downgrade sound volume by 10
             */
            void upgradeFramerate();
    };
}

#endif /* !FRAMERATESCENE_HPP_ */
