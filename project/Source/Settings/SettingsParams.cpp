/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SettingsParams
*/

#include "tools.hpp"
#include "FileError.hpp"
#include "SettingsParams.hpp"

SettingsParams::SettingsParams() :
    _title("Raylib project"), _windowSize({1920, 1080}), _audioVolume(100), _musicVolume(100),
    _cameraMode(CAMERA_FREE), _cameraProjection(CAMERA_PERSPECTIVE)
{
}


SettingsParams::~SettingsParams()
{
}

void SettingsParams::loadFromData(std::string const &filepath)
{
    nlohmann::json jsonData;
    try {
        jsonData = getJsonData(filepath);
    } catch (Error::FileError const &e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    std::cout << "settings: "<< jsonData << std::endl;
    _title = jsonData.value("title", "Raylib project");
    _windowSize = jsonData.value("windowSize", std::pair<float, float>(1920, 1080));
    _audioVolume = jsonData.value("audioVolume", 100);
    _musicVolume = jsonData.value("musicVolume", 100);
    std::array<float, 3> tmpPosition = jsonData.value("cameraPosition", std::array<float, 3>({0,0,0}));
    _cameraPosition.setPosition(tmpPosition.at(0), tmpPosition.at(1), tmpPosition.at(2));

    std::array<float, 3> tmpTarget = jsonData.value("cameraTarget", std::array<float, 3>({0,0,0}));
    _cameraTarget.setPosition(tmpTarget.at(0), tmpTarget.at(1), tmpTarget.at(2));
    _cameraUp.setPosition((Position){0, 100, 0});
    _cameraFovy = 45.0f;
    _cameraMode = jsonData.value("cameraMode", CAMERA_FREE);
    _cameraProjection = jsonData.value("cameraProjection", CAMERA_PERSPECTIVE);
}
