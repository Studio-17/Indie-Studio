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

/**
 * @brief The IntroductionScene class
 * @details This class is used to display the introduction scene
 */
namespace Scene {
    /**
     * @brief The IntroductionScene class
     */
    class IntroductionScene : public AScene {
        public:
            /**
             * @brief IntroductionScene
             * @param settings
             * @param keyboard
             */
            IntroductionScene(std::shared_ptr<Settings> settings, Keyboard &keyboard);
            /**
             * @brief ~IntroductionScene
             */
            ~IntroductionScene();
            /**
             * @brief handleEvent
             * @return
             */
            Scenes handleEvent() override;
            /**
             * @brief draw
             */
            void draw() override;
            /**
             * @brief handleKey
             */
            void handleKey();

            void BlinkText();

        protected:
        private:
            std::vector<std::unique_ptr<Object::Image>> _parallax; ///< Vector of every Images of the parallax
            Keyboard &_keyboard; ///< Keyboard object to get pressed key
            Clock _clock; ///< Clock object to get time
            bool _shouldPrintText;
    };
}

#endif /* !INTRODUCTIONSCENE_HPP_ */
