/*
** EPITECH PROJECT, 2022
** project
** File description:
** SplashScreenScene
*/

#ifndef SPLASHSCREENSCENE_HPP_
    #define SPLASHSCREENSCENE_HPP_

#include "IMenuScene.hpp"

/**
 * @brief The splash screen scene of the game
 * 
 */
namespace Scene {
    class SplashScreenScene : public AScene {
        public:
            SplashScreenScene(std::shared_ptr<Settings> settings);
            ~SplashScreenScene();

        protected:
        private:
    };
}

#endif /* !SPLASHSCREENSCENE_HPP_ */
