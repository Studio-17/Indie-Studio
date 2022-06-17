/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Settings
*/

#include <fstream>

#include "Position.hpp"
#include "Settings.hpp"
#include "tools.hpp"

Settings::Settings(nlohmann::json const &jsonData) :
    _window(std::make_shared<RayLib::Window>(jsonData.value("windowSize", std::pair<float, float>(1920, 1080)), jsonData.value("title", "Raylib project"))),
    _audio(std::make_shared<RayLib::Audio>(jsonData.value("audioVolume", 50), jsonData.value("musicVolume", 50))),
    _camera(std::make_shared<RayLib::CinematicCamera>(jsonData.value("cameraMode", CAMERA_FREE)))
{
    Position tmpPos;

    _camera->setPosition(tmpPos.setFromArray(jsonData.value("cameraPosition", std::array<float, 3>({65, 200, 100}))));
    _camera->setTarget(tmpPos.setFromArray(jsonData.value("cameraTarget", std::array<float, 3>({65, 0, 65}))));
    _camera->setUp(tmpPos.setFromArray(jsonData.value("cameraUp", std::array<float, 3>({0, 1, 0}))));
    _camera->setFovy(jsonData.value("cameraFovy", 45.0));
    _camera->setProjection(jsonData.value("cameraProjection", CAMERA_PERSPECTIVE));
    _musics = loadObjects<MyMusic>("Conf/Settings/musics.json");
    _sounds = loadObjects<MySound>("Conf/Settings/sounds.json");
    _saveIndex = jsonData.value("saveIndex", 0);

    for (auto &music : _musics)
        music->setVolume(_audio->getAudioVolume());

    for (auto &sound : _sounds)
        sound->setVolume(_audio->getSoundVolume());
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

void Settings::setPlayerActionsPressed(std::vector<std::map<PlayerAction, bool>> const &playerAction)
{
    _playerActions = playerAction;
}

std::map<Action, bool> Settings::getActionPressed() const
{
    return _actionPressed;
}

std::vector<std::map<PlayerAction, bool>> Settings::getPlayerActionsPressed() const
{
    return _playerActions;
}

void Settings::playMusic(const MusicsEnum &music)
{
    _musics.at(music)->play();
}

void Settings::updateMusicStream(const MusicsEnum &music)
{
    _musics.at(music)->updateMusicStream();
}

void Settings::stopMusic(const MusicsEnum &music)
{
    _musics.at(music)->stop();
}

void Settings::playSound(const SoundsEnum &sound)
{
    _sounds.at(sound)->play();
}

void Settings::stopSound(const SoundsEnum &sound)
{
    _sounds.at(sound)->stop();
}

std::size_t Settings::getSaveIndex() const
{
    return _saveIndex;
}

void Settings::incrementSaveIndex()
{
    _saveIndex++;
}

void Settings::resetSaveIndex()
{
    _saveIndex = 0;
}

void Settings::updateSettingsDatas(std::string const &filepath)
{
    nlohmann::json saveData = getJsonData(filepath);
    std::ofstream fileToWrite(filepath);

    if (!fileToWrite.is_open())
        throw Error::FileError("File " + filepath + " failed to open");
    // std::vector<std::string> playerName {"playerOne", "playerTwo", "playerThree", "playerFour"};
    // std::map<Action, std::string> actionName {{Action::Left, "left"}, {Action::Right, "right"}, {Action::Up, "up"}, {Action::Down, "down"}, {Action::Next, "next"}, {Action::Previous, "previous"}};
    // std::map<PlayerAction, std::string> playerActionName {{PlayerAction::MoveLeft, "moveLeft"}, {PlayerAction::MoveRight, "moveRight"}, {PlayerAction::MoveUp, "moveUp"}, {PlayerAction::MoveDown, "moveDown"}, {PlayerAction::Drop, "keyboardDrop"}};
    // nlohmann::json keyData;
    // std::size_t index = 0;

    // for (auto &[action, key] : _actionPressed )
    //     keyData[actionName.at(action)] = key;
    // saveData["basicKeyboard"] = keyData;
    // for (auto &player : _playerAction) {
    //     keyData.clear();
    //     for (auto &[action, key] : player) {
    //         keyData[playerActionName.at(action)] = key;
    //     }
    //     keyData["gamepadDrop"] = _gamepadPlayerActions.at(index).second;
    //     saveData[playerName.at(index)] = keyData;
    //     index++;
    // }
    incrementSaveIndex();
    saveData["saveIndex"] = _saveIndex;
    fileToWrite << saveData.dump(4);
}
