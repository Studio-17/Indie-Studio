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
        void setNbPlayers(std::size_t const &nbPlayers);
        std::size_t getNbPlayers() const;
        void setNbSets(std::size_t const &nbSets);
        void setGameTime(std::float_t const &gameTime);
        void setEnableBonus(bool const &enableBonus);

    protected:
    private:
        std::shared_ptr<RayLib::Window> _window;
        std::shared_ptr<RayLib::Audio> _audio;
        std::shared_ptr<RayLib::CinematicCamera> _camera;

        std::map<Action, bool> _actionPressed;
        std::vector<std::map<PlayerAction, bool>> _playerActions;
        std::map<PlayerAction, bool> _playerAction;

        std::size_t _nbPlayers;
        std::size_t _nbSets;
        std::float_t _gameTime;
        bool _enableBonus;
};

#endif /* !SETTINGS_HPP_ */
