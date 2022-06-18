/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectSaveScene
*/

#include <dirent.h>

#include <functional>
#include <iostream>
#include <vector>
#include <cstdio>

#include "tools.hpp"
#include "SelectSaveScene.hpp"

void Scene::SelectSaveScene::exitSelectSaveScene()
{
    _nextScene = Scenes::START_GAME;
}

void Scene::SelectSaveScene::runGame()
{
    _gameSettings->loadFromJson(getJsonData(_directory + "/" + _savesFilesList.at(_indexListFiles) + ".json"));
    _applyGameSettings();
    _nextScene = Scenes::GAME;
}

void Scene::SelectSaveScene::previousSave()
{
    if (_indexListFiles == 0) {
        _indexListFiles = _savesFilesList.size() - 1;
    } else {
        _indexListFiles--;
    }
    _texts.at(2)->setText(_savesFilesList.at(_indexListFiles));
}

void Scene::SelectSaveScene::nextSave()
{
    if (_indexListFiles == _savesFilesList.size() - 1) {
        _indexListFiles = 0;
    } else {
        _indexListFiles++;
    }
    _texts.at(2)->setText(_savesFilesList.at(_indexListFiles));
}

void Scene::SelectSaveScene::newGameScene()
{
    _nextScene = Scene::Scenes::OPTION_GAME;
}

bool Scene::SelectSaveScene::isGoodSaveFile(std::string const &filename, std::string const &suffix)
{
    if (filename.size() < suffix.size()) {
        return false;
    }
    return filename.compare(filename.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::vector<std::string> Scene::SelectSaveScene::getFilesListFromDirectory(std::string const &directory, std::string const &suffix)
{
    DIR *dir = opendir(directory.c_str());
    struct dirent *diread;
    std::vector<std::string> files;
    std::string file;

    _directory = directory;
    if (dir == nullptr)
        throw Error::FileError("Failed to open " + directory + " directory");
    while ((diread = readdir(dir)) != nullptr) {
        file = diread->d_name;
        if (isGoodSaveFile(file, suffix)) {
            file.erase(file.size() - suffix.size());
            files.push_back(file);
        }
    }
    closedir(dir);
    return files;
}

Scene::SelectSaveScene::SelectSaveScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::function<void(void)> applyGameSettings) : AScene(settings), _gameSettings(gameSettings),
    _applyGameSettings(applyGameSettings)
{
    std::vector<std::function<void(void)>> callBacks =
    {
        std::bind(&Scene::SelectSaveScene::exitSelectSaveScene, this),
        std::bind(&Scene::SelectSaveScene::runGame, this),
        std::bind(&Scene::SelectSaveScene::previousSave, this),
        std::bind(&Scene::SelectSaveScene::nextSave, this),
        std::bind(&Scene::SelectSaveScene::newGameScene, this),
        std::bind(&Scene::SelectSaveScene::reset, this)
    };

    _buttons = loadObjects<Object::Button>("Conf/Scenes/SelectSaveScene/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/SelectSaveScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/SelectSaveScene/text.json");
    _parallax = loadObjects<Object::Image>("Conf/Scenes/parallax.json");
    updateSaveFiles();
    _nextScene = Scene::Scenes::SAVE;
}

Scene::SelectSaveScene::~SelectSaveScene()
{
}

Scene::Scenes Scene::SelectSaveScene::handleEvent()
{
    int index = 0;
    std::float_t speed = 0.0;

    _settings->updateMusicStream(MusicsEnum::Menu);
    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }

    _nextScene = Scene::Scenes::SAVE;

    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}


void Scene::SelectSaveScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    DrawRectangle(100, 250, 800, 600, GRAY);
    for (auto &image : _images)
        image->draw();
    for (auto &button : _buttons)
        button->draw();
    for (auto &text : _texts)
        text->draw();
}

void Scene::SelectSaveScene::reset()
{
    std::vector<std::string> mapFiles = getFilesListFromDirectory("Save/Games/Maps/", ".map");

    _savesFilesList = getFilesListFromDirectory("Save/Games/Params/", ".json");
    _settings->resetSaveIndex();
    _settings->updateSettingsDatas("Conf/Settings/settings.json");
    for (auto &file : _savesFilesList)
        std::remove(("Save/Games/Params/" + file + ".json").c_str());
    for (auto &file : mapFiles)
        std::remove(("Save/Games/Maps/" + file + ".map").c_str());
    updateSaveFiles();
}

void Scene::SelectSaveScene::updateSaveFiles()
{
    _savesFilesList = getFilesListFromDirectory("Save/Games/Params/", ".json");
    _indexListFiles = 0;
    if (!_savesFilesList.empty()) {
        _texts.at(2)->setText(_savesFilesList.at(_indexListFiles));
        _texts.at(2)->setPosition(440, 560);
        _buttons.at(4)->disable();
        _buttons.at(1)->enable();
        _buttons.at(1)->enableClick();
        _buttons.at(2)->enable();
        _buttons.at(2)->enableClick();
        _buttons.at(3)->enable();
        _buttons.at(3)->enableClick();
    } else {
        _buttons.at(4)->enable();
        _texts.at(2)->setText("No save file in Save/Games/Params directory");
        _texts.at(2)->setPosition(150, 560);
        _buttons.at(1)->disable();
        _buttons.at(1)->disableClick();
        _buttons.at(2)->disable();
        _buttons.at(2)->disableClick();
        _buttons.at(3)->disable();
        _buttons.at(3)->disableClick();
    }
}
