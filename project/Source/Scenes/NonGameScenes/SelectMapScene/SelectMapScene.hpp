/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectMap
*/

#ifndef SELECTMAP_HPP_
    #define SELECTMAP_HPP_

    #include "AScene.hpp"
    #include "Music.hpp"
    #include "Image.hpp"
    #include "Button.hpp"
    #include "Text.hpp"
    #include "Map.hpp"
    #include "GameSettings.hpp"

    #include <vector>
    #include <memory>
    #include <utility>

namespace Scene {

    class SelectMapScene : public AScene {
        public:
            SelectMapScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings);
            ~SelectMapScene();

            Scenes handleEvent() override;
            void draw() override;

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
            std::shared_ptr<GameSettings> _gameSettings;
            std::unique_ptr<Object::Map> _gameMap;
            std::vector<std::unique_ptr<Object::Image>> _parallax;
            std::string _currentPath;
            int _count;
            std::vector<std::unique_ptr<Object::Text>> _noDroppedFilesText;
            std::vector<std::unique_ptr<Object::Text>> _droppedFilesText;
            std::vector<std::unique_ptr<Object::Text>> _pathFileDropped;
            std::vector<std::unique_ptr<Object::Text>> _mapName;
            int _minMapSize;
            int _maxMapSize;
            int _mapSize;
            int _scaleModifier;
            int _height;
            int _width;
    };
}

#endif /* !SELECTMAP_HPP_ */
