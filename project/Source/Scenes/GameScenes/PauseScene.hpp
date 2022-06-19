/*
** EPITECH PROJECT, 2022
** project
** File description:
** PauseScene
*/

#ifndef PAUSESCENE_HPP_
    #define PAUSESCENE_HPP_

    #include "AScene.hpp"
    #include "GameSettings.hpp"
    #include "VolumeSettingsScene.hpp"

namespace Scene {
    /**
     * @brief Pause Scene object to handle and display Pause Scene
     */
    class PauseScene : public AScene {
        public:
            /**
             * @brief Construct a new Pause Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param gameSettings Shared pointer to Game Settings class
             * @param callBack
             * @param saveCallBack Call back function to save game
             */
            // PauseScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::function<void(void)> callBack, std::function<void(void)> saveCallBack);
            PauseScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::function<void(void)>> callBacks);
            ~PauseScene();

            Scenes handleEvent() override;
            void draw() override;

        protected:
        private:
            /**
             * @brief Call back function executed when exit without save button is pressed to set next scene to main menu scene
             */
            void exitGame();
            /**
             * @brief Call back function executed when exit without save button is pressed to set next scene to main menu scene
             */
            void save();
            /**
             * @brief Call back function executed when exit button is pressed to show exit popUp
             */
            void printExitPopUp();
            /**
             * @brief Call back function executed when back button of popUp is pressed to unshow exit popUp
             */
            void unPrintExitPopUp();

            /**
             * @brief Call back function executed when settings button is pressed to show exit settings
             */
            void printSettingsPopUp();
            /**
             * @brief Call back function executed when back button of popUp is pressed to unshow settings popUp
             */
            void unPrintSettingsPopUp();


            bool _shouldPrintExitPopUp; ///< To know if we should display exit popUp
            bool _shouldPrintSettingsPopUp; ///< To know if we should display settings popUp
            std::function<void(void)> _saveFunction;
            std::shared_ptr<VolumeSettingsScene> _volumeSettingsScene;
    };
}

#endif /* !PAUSESCENE_HPP_ */
