/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
    #define SETTINGS_HPP_

    #include <nlohmann/json.hpp>

    #include <memory>
    #include <map>
    #include <utility>
    #include <vector>

    #include "Audio.hpp"
    #include "Camera.hpp"
    #include "Window.hpp"

enum class Action {
    Next,
    Previous,
    Right,
    Left,
    Up,
    Down
};
enum class PlayerAction {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Drop
};
class Settings {
    public:
        // Settings(SettingsParams const &params);
        // Settings(std::string const &confpath);
        Settings(nlohmann::json const &jsonData);
        ~Settings();

        std::shared_ptr<RayLib::Window> getWindow() const;
        std::shared_ptr<RayLib::Audio> getAudio() const;
        std::shared_ptr<RayLib::CinematicCamera> getCamera() const;
        void setActionPressed(std::map<Action, bool> const &actionPressed);
        void setPlayerActionsPressed(std::vector<std::map<PlayerAction, bool>> const &playerAction);
        std::map<Action, bool> getActionPressed() const;
        std::vector<std::map<PlayerAction, bool>> getPlayerActionsPressed() const;

    protected:
    private:
        std::shared_ptr<RayLib::Window> _window;
        std::shared_ptr<RayLib::Audio> _audio;
        std::shared_ptr<RayLib::CinematicCamera> _camera;

        std::map<Action, bool> _actionPressed;
        std::vector<std::map<PlayerAction, bool>> _playerActions;
        std::map<PlayerAction, bool> _playerAction;
};

#endif /* !SETTINGS_HPP_ */
