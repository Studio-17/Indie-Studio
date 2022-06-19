/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** InformationScene
*/

#ifndef INFORMATIONSCENE_HPP_
#define INFORMATIONSCENE_HPP_

#include "AScene.hpp"

namespace Scene {
    /**
     * @brief The InformationScene class
     */
    class InformationScene : public AScene {
        public:
            /**
             * @brief Construct a new Information Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param parallax Vector of unique pointer of Object::Image class
             */
            InformationScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax);
            /**
             * @brief Destroy the Information Scene object
             */
            ~InformationScene();

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
             * @brief Call back function executed when next button is pressed to set next scene to main menu scene
             */
            void mainMenuScene();
            /**
             * @brief Call back function executed when next button is pressed to set next scene to start game scene
             */
            void startGameScene();

        protected:
        private:
            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax
    };
}

#endif /* !INFORMATIONSCENE_HPP_ */
