/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <unordered_map>
    #include <memory>
    #include <utility>

    #include "IScene.hpp"
    #include "Settings.hpp"
    #include "Keyboard.hpp"
    #include "Gamepad.hpp"
    #include "GameSettings.hpp"
    #include "Image.hpp"
    #include "Text.hpp"

class Core {
    public:
        Core();
        ~Core();

        void loadMenuScenes();
        void loop();

        void getEvent();
        void bindKey(int player, int action, int Key);

        void loadKeyBinding(nlohmann::json const &jsonData);

        void waitingLoad();

        void updateLoadingScreen(Position const &position);
    protected:
    private:
        std::shared_ptr<Settings> _settings;
        std::shared_ptr<GameSettings> _gameSettings;
        bool _isRunning;
        std::unordered_map<Scene::Scenes, std::shared_ptr<Scene::IScene>> _menuScenes;
        Scene::Scenes _activeScene;
        Keyboard _keyboard;
        Gamepad _gamepad;

        std::map<Action, int> _actionPressed;
        std::vector<std::map<PlayerAction, int>> _playerActions;
        std::vector<std::pair<PlayerAction, int>> _gamepadPlayerActions;
        std::map<PlayerAction, int> _gamepadPlayerMovement;

        std::vector<std::unique_ptr<Object::Image>> _images;
        std::vector<std::unique_ptr<Object::Text>> _texts;
};

#endif /* !CORE_HPP_ */
