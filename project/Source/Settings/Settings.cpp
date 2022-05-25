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
    _camera(std::make_shared<RayLib::CinematicCamera>()),
    _actionMap({{Action::MoveLeft, {'q', false}}, {Action::MoveRight, {'d', false}}, {Action::MoveUp, {'z', false}}, {Action::MoveDown, {'s', false}}, {Action::Drop, {'e', false}}})
{
}

Settings::~Settings()
{
}

std::shared_ptr<RayLib::Window> Settings::getWindow()
{
    return _window;
}

std::shared_ptr<RayLib::Audio> Settings::getAudio()
{
    return _audio;
}

std::shared_ptr<RayLib::CinematicCamera> Settings::getCamera()
{
    return _camera;
}
