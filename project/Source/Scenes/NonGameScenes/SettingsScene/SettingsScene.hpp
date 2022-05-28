/*
** EPITECH PROJECT, 2022
** project
** File description:
** SettingsScene
*/

#ifndef SETTINGSSCENE_HPP_
    #define SETTINGSSCENE_HPP_

    #include <vector>
    #include <map>

    #include "AScene.hpp"
    #include "Music.hpp"
    #include "Map.hpp"
    #include "Player.hpp"
/**
 * @brief The settings scene of the game
 */
namespace Scene {
    class SettingsScene : public AScene {
        public:
            SettingsScene(std::shared_ptr<Settings> settings);
            ~SettingsScene();

            void fadeBlack() override;
            Scenes handelEvent() override;
            void exitScene();
            void settingsScene();
            void newGameScene();
            void mainMenuScene();
            void draw();

            int getMovingKeys();
            bool isColliding(Position margin);

        protected:
        private:
            std::unique_ptr<Object::Map> _gameMap;
            std::unique_ptr<Object::Player> _playerOne;
            std::unique_ptr<Object::Player> _playerTwo;

            std::string _mapFile;

            float _margin;
            float _playerSpeed;

            // bool _isRunning;
            // Scene::Scenes _nextScene;

            // std::map<BUTTONSNAME, std::unique_ptr<Object::Button>> _buttons;
            // std::unique_ptr<MyMusic> _mainMusic;
    };
}

#endif /* !SETTINGSSCENE_HPP_ */
