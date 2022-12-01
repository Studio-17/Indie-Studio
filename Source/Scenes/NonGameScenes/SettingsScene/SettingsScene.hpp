/*
** EPITECH PROJECT, 2022
** project
** File description:
** SettingsScene
*/

#ifndef SETTINGSSCENE_HPP_
    #define SETTINGSSCENE_HPP_

    #include "AScene.hpp"
    #include "VolumeSettingsScene.hpp"
    #include "FramerateScene.hpp"

namespace Scene {
    /**
     * @brief Settings Scene object to handle and display Option Settings Scene
     */
    class SettingsScene : public AScene {
        public:
            /**
             * @brief Construct a new Settings Scene object
             *
             * @param settings Shared pointer to Settings class
             */
            SettingsScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax);
            /**
             * @brief Destroy the Option Settings Scene object
             */
            ~SettingsScene();

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
             * @brief handle action
             */
            void handleAction();
        protected:
        private:
            /**
             * @brief Call back function executed when credits button is pressed to set next scene to credits scene
             */
            void credits();
            /**
             * @brief Call back function executed when help button is pressed to set next scene to help scene
             */
            void help();
            /**
             * @brief Call back function executed when volume button is pressed to display a popUp to handle volume
             */
            void volume();
            /**
             * @brief Call back function executed when framerate button is pressed to display a popUp to handle framerate
             */
            void framerate();
            /**
             * @brief Call back function executed when controls button is pressed to set next scene to binding scene
             */
            void controls();
            /**
             * @brief Call back function executed when back button is pressed to set next scene to main menu scene
             */
            void back();
            /**
             * @brief Call closePopupVolume function executed when back button in popup volume is pressed to close it
             */
            void closePopupVolume();
            /**
             * @brief Call closePopupFramerate function executed when back button in popup volume is pressed to close it
             */
            void closePopupFramerate();

            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax
            std::unique_ptr<Scene::VolumeSettingsScene> _volumeSettingsScene; ///< Unique pointer to Volume Settings Scene
            bool _isVolumeSettings; ///< Boolean to know if the volume settings scene is displayed
            std::unique_ptr<Scene::FramerateScene> _framerateScene; ///< Unique pointer to Framerate Settings Scene
            bool _isFramerate; ///< Boolean to know if the volume settings scene is displayed
            std::size_t _activeButton; ///< Index of the active button
    };
}

#endif /* !SETTINGSSCENE_HPP_ */
