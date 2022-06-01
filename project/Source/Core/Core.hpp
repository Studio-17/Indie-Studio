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

class Core {
    public:
        Core();
        ~Core();

        void loadMenuScenes();
        void loop();

        void getEvent();

        void loadKeyBinding(nlohmann::json const &jsonData);
    protected:
    private:
        std::shared_ptr<Settings> _settings;
        bool _isRunning;
        std::unordered_map<Scene::Scenes, std::shared_ptr<Scene::IScene>> _menuScenes;
        Scene::Scenes _activeScene;
        Keyboard _keyboard;
        Gamepad _gamepad;

        std::map<Action, int> _actionPressed;
        std::vector<std::map<PlayerAction, int>> _playerActions;
        std::vector<std::pair<PlayerAction, int>> _gamepadPlayerActions;
        std::map<PlayerAction, int> _gamepadPlayerMovement;
};

#endif /* !CORE_HPP_ */
