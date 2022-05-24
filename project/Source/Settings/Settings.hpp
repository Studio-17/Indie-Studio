/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
    #define SETTINGS_HPP_

    #include <memory>
    #include <map>
    #include <utility>

    #include "Audio.hpp"
    #include "Camera.hpp"
    #include "Window.hpp"
    #include "SettingsParams.hpp"

class Settings {
    public:
        Settings(SettingsParams const &params);
        ~Settings();

        std::shared_ptr<RayLib::Window> getWindow();
        std::shared_ptr<RayLib::Audio> getAudio();
        std::shared_ptr<RayLib::CinematicCamera> getCamera();

    protected:
    private:
        std::shared_ptr<RayLib::Window> _window;
        std::shared_ptr<RayLib::Audio> _audio;
        std::shared_ptr<RayLib::CinematicCamera> _camera;
        enum class Action {
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,
            Drop
        };
        std::map<Action, std::pair<int, bool>> _actionMap;
};

#endif /* !SETTINGS_HPP_ */
