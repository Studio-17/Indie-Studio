/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectMap
*/

#ifndef SELECTMAP_HPP_
    #define SELECTMAP_HPP_

    #include "AScene.hpp"
    #include "Map.hpp"
    #include "GameSettings.hpp"

namespace Scene {
    /**
     * @brief Select Map Scene object to handle and display Option Select Map Scene
     */
    class SelectMapScene : public AScene {
        public:
            /**
             * @brief Construct a new Select Map Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param gameSettings Shared pointer to Game Settings class
             * @param parallax Vector of unique pointer of Object::Image class
             */
            SelectMapScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::unique_ptr<Object::Image>> &parallax);
            /**
             * @brief Destroy the Select Map Scene object
             */
            ~SelectMapScene();

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
             * @brief Generate random map in a file of defined size and percentage of Box spwaning
             *
             * @param filename string of file path where the map will be generate
             * @param width number of columns in the map
             * @param height number of rows in the map
             * @param percentageDrop percentage of box spwaning in the map
             */
            void generate(std::string const &filename, std::size_t width, std::size_t height, std::size_t percentageDrop);
            /**
             * @brief handle action
             */
            void handleAction();
        protected:
            /**
             * @brief Exit the scene
             */
            void exitSelectMapSceneScene();
            /**
             * @brief Run the Select Player Scene
             */
            void runSelectPlayerScene();
            /**
             * @brief Set display map selection in basic mode
             */
            void basicMode();
            /**
             * @brief Set display map selection in custom mode
             */
            void customMode();
            /**
             * @brief Increase map height and width by 2
             */
            void previousMap();
            /**
             * @brief Reduces map height and width by 2
             */
            void nextMap();
            /**
             * @brief Check if the line is a valid map line
             *
             * @param line string of line to check
             * @param sizeLine good size of line
             * @param nbrLine line index
             * @return true if the line is valid for a map line
             * @return false if the line is not valid for a map line
             */
            bool isGoodLineMap(std::string const &line, std::size_t sizeLine, int nbrLine);
            /**
             * @brief Get the Vector Map From File object
             *
             * @param filename string of file path
             * @return std::vector<std::string> of the map obtained from the file
             */
            std::vector<std::string> getVectorMapFromFile(const std::string &filename);
            /**
             * @brief Check if the spawns of the 4 players are good
             *
             * @param vecMap std::vector<std::string> of the map
             * @return true if the three cases of each spawn are empty
             * @return false if the a case of the three cases of a spawn is not empty
             */
            bool haveGoodSpawn(std::vector<std::string> vecMap);
            /**
             * @brief Check the map in the file validity
             *
             * @param filename string of file path to obtain the map
             * @return true if the map in the file is valid
             * @return false if the map in the file is invalid
             */
            bool isGoodFileMap(const std::string &filename);

        private:
            std::shared_ptr<GameSettings> _gameSettings; ///< Shared pointer to game Settings class
            std::unique_ptr<Object::Map> _gameMap; ///< Unique pointer to game Map object
            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax
            std::string _currentPath; ///< String representing the current path of the map
            int _count; ///< Integer representing the number of the current map
            std::vector<std::unique_ptr<Object::Text>> _noDroppedFilesText; ///< Vector of every Text of the no dropped files
            std::vector<std::unique_ptr<Object::Text>> _droppedFilesText; ///< Vector of every Text of the dropped files
            std::vector<std::unique_ptr<Object::Text>> _mapName; ///< Vector of every Text of the map name
            int _minMapSize; ///< Integer representing the minimum size of the map
            int _maxMapSize; ///< Integer representing the maximum size of the map
            int _mapSize; ///< Integer representing the size of the map
            int _scaleModifier; ///< Integer representing the scale modifier of the map
            int _height; ///< Integer representing the height of the map
            int _width; ///< Integer representing the width of the map
    };
}

#endif /* !SELECTMAP_HPP_ */
