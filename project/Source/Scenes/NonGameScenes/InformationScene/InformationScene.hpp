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
     * 
     */
    class InformationScene : public AScene {
        public:
            /**
             * @brief Construct a new Information Scene object
             * 
             * @param settings 
             * @param parallax 
             */
            InformationScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax);
            /**
             * @brief Destroy the Information Scene object
             * 
             */
            ~InformationScene();

            /**
             * @brief handleEvent
             * @return
             */
            Scenes handleEvent() override;
            /**
             * @brief draw
             */
            void draw() override;

            void mainMenuScene();
            void startGameScene();

        protected:
        private:
            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax
    };
}

#endif /* !INFORMATIONSCENE_HPP_ */
