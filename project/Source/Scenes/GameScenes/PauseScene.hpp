/*
** EPITECH PROJECT, 2022
** project
** File description:
** PauseScene
*/

#ifndef PAUSESCENE_HPP_
#define PAUSESCENE_HPP_

    #include "AScene.hpp"
    #include "Settings.hpp"
    #include "GameSettings.hpp"
    #include "tools.hpp"

namespace Scene {
    class PauseScene : public AScene {
        public:
            PauseScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::function<void(void)> callBack, std::function<void(void)> saveCallBack);
            ~PauseScene();

            Scenes handleEvent() override;
            void handlePauseState(bool &isPaused);
            void draw() override;
            void exitGame();

            void printExitPopUp();
            void unPrintExitPopUp();

        protected:
        private:
            bool _shouldPrintExitPopUp = false;
    };
}

#endif /* !PAUSESCENE_HPP_ */
