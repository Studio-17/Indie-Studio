/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** HelpScene
*/

#ifndef HELPSCENE_HPP_
#define HELPSCENE_HPP_

#include "AScene.hpp"

namespace Scene {
    /**
     * @brief The HelpScene class
     */
    class HelpScene : public AScene {
        public:
            /**
             * @brief Construct a new Help Scene object
             *
             * @param settings
             */
            HelpScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax);
            /**
             * @brief Destroy the Help Scene object
             */
            ~HelpScene();

            /**
             * @brief handleEvent
             * @return
             */
            Scenes handleEvent() override;
            /**
             * @brief draw
             */
            void draw() override;

            void backScene();

        protected:
        private:
            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax
    };
}

#endif /* !HELPSCENE_HPP_ */
