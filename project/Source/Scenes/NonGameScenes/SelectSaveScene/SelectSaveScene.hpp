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
    /**
     * @brief Select Save Scene object to handle and display Select Save Scene
     */
    class SelectSaveScene : public AScene {
        public:
            /**
             * @brief Construct a new Select Save Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param gameSettings Shared pointer to Game Settings class
             * @param parallax Vector of unique pointer of Object::Image class
             * @param applyGameSettings Callback function to apply game settings
             */
            SelectSaveScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::unique_ptr<Object::Image>> &parallax, std::function<void(nlohmann::json const &)> applyGameSettings);
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
            /**
             * @brief Change Save file in the previous save file in the save file list
             */
            void previousSave();
            /**
             * @brief Change Save file in the next save file in the save file list
             */
            void nextSave();
            /**
             * @brief redirects to the New Game Scene
             */
            void newGameScene();
            /**
             * @brief Check file extension validity
             *
             * @param filename string file path
             * @param suffix string of the valid extension name
             * @return true if the file extension is the wanted one
             * @return false if the file extension is not the wanted one
             */
            bool isGoodSaveFile(std::string const &filename, std::string const &suffix);
            /**
             * @brief Get the Files List of files with a wanted extension from a Directory
             *
             * @param directory string of the directory path
             * @param suffix string of the valid extension name
             * @return std::vector<std::string> of the Files List of files withthe wanted extension from the Directory
             */
            std::vector<std::string> getFilesListFromDirectory(std::string const &directory, std::string const &suffix);

        private:
            /**
             * @brief actualyse _savesFilesList and _settings infos
             */
            void reset();

            std::shared_ptr<GameSettings> _gameSettings; ///< Shared pointer to game Settings class
            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax
            std::vector<std::string> _savesFilesList; ///< Vector of every saves files list
            int _indexListFiles; ///< Integer representing the index of the list of files
            // std::function<void(std::string const &)> _applyGameSettings; ///< Function to apply the game settings
            std::function<void(nlohmann::json const &)> _applyGameSettings; ///< Function to apply the game settings
            std::string _directory; ///< String representing the directory of the saves files
    };
}

#endif /* !SELECTSAVE_HPP_ */
