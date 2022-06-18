/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectSave
*/

#ifndef SELECTSAVE_HPP_
    #define SELECTSAVE_HPP_

    #include "AScene.hpp"
    #include "Map.hpp"
    #include "GameSettings.hpp"

    #include <vector>
    #include <memory>
    #include <utility>

namespace Scene {

    class SelectSaveScene : public AScene {
        public:
            /**
             * @brief Construct a new Select Save Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param gameSettings Shared pointer to Game Settings class
             */
            SelectSaveScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::function<void(void)> applyGameSettings);
            /**
             * @brief Destroy the Select Save Scene object
             */
            ~SelectSaveScene();

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
            void updateSaveFiles();

        protected:
            /**
             * @brief Exit the scene
             */
            void exitSelectSaveScene();
            /**
             * @brief Run the game
             */
            void runGame();
            void previousSave();
            void nextSave();
            void newGameScene();
            bool isGoodSaveFile(std::string const &filename, std::string const &suffix);
            std::vector<std::string> getFilesListFromDirectory(std::string const &directory, std::string const &suffix);

        private:
            void reset();

            std::shared_ptr<GameSettings> _gameSettings; ///< Shared pointer to game Settings class
            std::vector<std::unique_ptr<Object::Image>> _parallax; ///< Vector of every Images of the parallax
            std::vector<std::string> _savesFilesList; ///< Vector of every saves files list
            int _indexListFiles; ///< Integer representing the index of the list of files
            std::function<void(void)> _applyGameSettings; ///< Function to apply the game settings
            std::string _directory; ///< String representing the directory of the saves files
    };
}

#endif /* !SELECTSAVE_HPP_ */
