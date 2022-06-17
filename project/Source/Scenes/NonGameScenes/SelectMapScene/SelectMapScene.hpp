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
             */
            SelectMapScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings);
            ~SelectMapScene();

            Scenes handleEvent() override;
            void draw() override;

            void generate(std::string const &filename, std::size_t width, std::size_t height, std::size_t percentageDrop);
            // void createFile(std::string const &filename);

        protected:
            void exitSelectMapSceneScene();
            void runSelectPlayerScene();
            void basicMode();
            void customMode();
            void previousMap();
            void nextMap();
            bool isGoodLineMap(std::string const &line, std::size_t sizeLine, int nbrLine);
            std::vector<std::string> getVectorMapFromFile(const std::string &filename);
            bool haveGoodSpawn(std::vector<std::string> vecMap);
            bool isGoodFileMap(const std::string &filename);

        private:
            std::shared_ptr<GameSettings> _gameSettings; ///< Shared pointer to game Settings class
            std::unique_ptr<Object::Map> _gameMap; ///< Unique pointer to game Map object
            std::vector<std::unique_ptr<Object::Image>> _parallax; ///< Vector of every Images of the parallax
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
