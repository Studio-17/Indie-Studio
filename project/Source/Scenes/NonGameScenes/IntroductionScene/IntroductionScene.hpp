/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** IntroductionScene
*/

#ifndef INTRODUCTIONSCENE_HPP_
    #define INTRODUCTIONSCENE_HPP_

    #include "Keyboard.hpp"
    #include "AScene.hpp"
    #include "clock.hpp"

namespace Scene {
    /**
     * @brief The IntroductionScene class
     */
    class IntroductionScene : public AScene {
        public:
            /**
             * @brief IntroductionScene
             *
             * @param settings Shared pointer to Settings class
             * @param parallax Vector of unique pointer of Object::Image class
             * @param keyboard
             */
            IntroductionScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax, Keyboard &keyboard);
            /**
             * @brief ~IntroductionScene
             */
            ~IntroductionScene();

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
             * @brief handleKey
             */
            void handleKey();

            /**
             * @brief Set text to blink it
             */
            void BlinkText();

        protected:
        private:
            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax
            Keyboard &_keyboard; ///< Keyboard object to get pressed key
            Clock _clock; ///< Clock object to get time
            bool _shouldPrintText; ///< To know if we should print text
    };
}

#endif /* !INTRODUCTIONSCENE_HPP_ */
