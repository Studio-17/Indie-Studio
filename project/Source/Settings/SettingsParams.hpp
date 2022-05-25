/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SettingsParams
*/

#ifndef SETTINGSPARAMS_HPP_
    #define SETTINGSPARAMS_HPP_

    #include <raylib.h>

    #include <string>
    #include <utility>

    #include "Position.hpp"

class SettingsParams {
    public:
        SettingsParams();
        ~SettingsParams();

        std::string _title;
        std::pair<float, float> _windowSize;
        float _audioVolume;
        float _musicVolume;
        Position _cameraPosition;
        Position _cameraTarget;
        CameraMode _cameraMode;
        CameraProjection _cameraProjection;
};

#endif /* !SETTINGSPARAMS_HPP_ */
