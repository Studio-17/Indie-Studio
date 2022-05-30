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

    #include "IScene.hpp"
    #include "Settings.hpp"
    #include "Keyboard.hpp"

class Core {
    public:
        Core();
        ~Core();

        void loadMenuScenes();
        void loop();

        void getEvent();

    protected:
    private:
        std::shared_ptr<Settings> _settings;
        bool _isRunning;
        std::unordered_map<Scene::Scenes, std::shared_ptr<Scene::IScene>> _menuScenes;
        Scene::Scenes _activeScene;
        Keyboard _keyboard;

        std::map<Action, int> _actionPressed;
        // std::array<std::map<PlayerAction, int>, 4> _playerAction;
        std::map<PlayerAction, int> _playerAction;

};

#endif /* !CORE_HPP_ */
