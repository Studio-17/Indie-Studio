/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <memory>

#include "SettingsModules/Audio/Audio.hpp"

#include "SettingsModules/Camera/Camera.hpp"

#include "SettingsModules/Window/Window.hpp"

class Settings {
    public:
        Settings();
        ~Settings();

    protected:
    private:
        std::unique_ptr<RayLib::Audio> _audio;
        std::unique_ptr<RayLib::CinematicCamera> _camera;
        std::unique_ptr<RayLib::Window> _window;
};

#endif /* !SETTINGS_HPP_ */
