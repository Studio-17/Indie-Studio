/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectSave
*/

#ifndef SELECTSAVE_HPP_
#define SELECTSAVE_HPP_

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

    class SelectSaveScene : public AScene {
        public:
            SelectSaveScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings);
            ~SelectSaveScene();

            Scenes handleEvent() override;
            void draw() override;

        protected:
            void exitSelectSaveScene();
            void runGame();
            void previousSave();
            void nextSave();
            void newGameScene();
            bool isGoodSaveFile(const std::string &filename);
            std::vector<std::string> getFilesListFromDirectory(const std::string &directory);

        private:
            std::shared_ptr<GameSettings> _gameSettings;
            std::vector<std::unique_ptr<Object::Image>> _parallax;
            std::vector<std::string> _savesFilesList;
            int _indexListFiles;
    };
}

#endif /* !SELECTSAVE_HPP_ */
