/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Settings
*/

#include "Position.hpp"
#include "Settings.hpp"

Settings::Settings(SettingsParams const &params):
    _window(std::make_shared<RayLib::Window>(params._windowSize.first, params._windowSize.second, params._title)),
    _audio(std::make_shared<RayLib::Audio>(params._audioVolume, params._musicVolume)),
    _camera(std::make_shared<RayLib::CinematicCamera>())
    // _actionMap({{Action::MoveLeft, {'q', false}}, {Action::MoveRight, {'d', false}}, {Action::MoveUp, {'z', false}}, {Action::MoveDown, {'s', false}}, {Action::Drop, {'e', false}}})
{
}

Settings::Settings(std::string const &confpath)
{
    SettingsParams params;

    params.loadFromData(confpath);
}

Settings::~Settings()
{
}

std::shared_ptr<RayLib::Window> Settings::getWindow() const
{
    return _window;
}

std::shared_ptr<RayLib::Audio> Settings::getAudio() const
{
    return _audio;
}

std::shared_ptr<RayLib::CinematicCamera> Settings::getCamera() const
{
    return _camera;
}

void Settings::setActionPressed(std::map<Action, bool> const &actionPressed)
{
    _actionPressed = actionPressed;
}

// void Settings::setPlayerActionPressed(std::array<std::map<PlayerAction, bool>, 4> const &playerAction)
void Settings::setPlayerActionPressed(std::map<PlayerAction, bool> const &playerAction)
{
    _playerAction = playerAction;
}

std::map<Action, bool> Settings::getActionPressed() const
{
    return _actionPressed;
}

// std::array<std::map<PlayerAction, bool>, 4> Settings::getPlayerActionPressed() const
std::map<PlayerAction, bool> Settings::getPlayerActionPressed() const
{
    return _playerAction;
}

