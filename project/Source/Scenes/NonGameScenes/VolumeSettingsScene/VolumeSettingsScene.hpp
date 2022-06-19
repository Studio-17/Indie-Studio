/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** VolumeSettingsScene
*/

#ifndef VOLUMESETTINGSSCENE_HPP_
    #define VOLUMESETTINGSSCENE_HPP_

    #include "AScene.hpp"
    #include "GameSettings.hpp"

namespace Scene {
    /**
     * @brief Pause Scene object to handle and display Pause Scene
     */
    class VolumeSettingsScene : public AScene {
        public:
            /**
             * @brief Construct a new Pause Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param callBack
             */
            VolumeSettingsScene(std::shared_ptr<Settings> settings, std::vector<std::function<void(void)>> callBacks);
            /**
             * @brief Destroy the Pause Scene object
             * 
             */
            ~VolumeSettingsScene();

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
            void upgradeSound();
            /**
             * @brief downgrade sound volume by 10
             */
            void downgradeSound();
            /**
             * @brief upgrade music volume by 10
             */
            void downgradeMusic();
            /**
             * @brief upgrade music volume by 10
             */
            void upgradeMusic();
    };
}

#endif /* !VOLUMESETTINGSSCENE_HPP_ */
