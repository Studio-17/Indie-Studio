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
};

#endif /* !CORE_HPP_ */
