/*
** EPITECH PROJECT, 2022
** project
** File description:
** PauseScene
*/

#include "tools.hpp"
#include "PauseScene.hpp"

Scene::PauseScene::PauseScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::function<void(void)>> callBacks) : AScene(settings), _gameSettings(gameSettings), _callBacks(callBacks)
{
    std::vector<std::function<void(void)>> callBack = {
        _callBacks.at(0),
        std::bind(&Scene::PauseScene::printSettingsPopUp, this),
        _callBacks.at(1),
        std::bind(&Scene::PauseScene::printExitPopUp, this),
        std::bind(&Scene::PauseScene::save, this),
        std::bind(&Scene::PauseScene::exitGame, this),
        std::bind(&Scene::PauseScene::unPrintExitPopUp, this)
    };
    _shouldPrintExitPopUp = false;

    std::vector<std::function<void(void)>> volumeSettingsCallBacks = {std::bind(&Scene::PauseScene::unPrintSettingsPopUp, this)};

    _buttons = loadObjects<Object::Button>("Conf/Scenes/PauseScene/button.json");
    _images = loadObjects<Object::Image>("Conf/Scenes/PauseScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/PauseScene/text.json");
    _saveFunction = _callBacks.at(2);
    _volumeSettingsScene = std::make_shared<VolumeSettingsScene>(settings, volumeSettingsCallBacks);

    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBack.at(index));
    }
}

Scene::PauseScene::~PauseScene()
{
}

Scene::Scenes Scene::PauseScene::handleEvent()
{
    _nextScene = Scene::Scenes::GAME;
    if (!_shouldPrintExitPopUp && !_shouldPrintSettingsPopUp) {
        for (int index = 0; index < 4; index++)
            _buttons.at(index)->checkHover(GetMousePosition());
    } else if (_shouldPrintSettingsPopUp) {
        _volumeSettingsScene->handleEvent();
    } else {
        for (int cpt = 4; cpt < 7; cpt++)
            _buttons.at(cpt)->checkHover(GetMousePosition());
    }
    _buttons.at(6)->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::PauseScene::draw()
{
    for (auto &image : _images)
        image->draw();
    if (!_shouldPrintExitPopUp && !_shouldPrintSettingsPopUp) {
        for (int index = 0; index < 4; index++)
            _buttons.at(index)->draw();
    } else if (_shouldPrintSettingsPopUp) {
        _volumeSettingsScene->draw();
    } else {
        for (int cpt = 4; cpt < 7; cpt++)
            _buttons.at(cpt)->draw();
        for (auto &text : _texts)
            text->draw();
    }
}

void Scene::PauseScene::save()
{
    _saveFunction();
    _settings->updateSettingsDatas("Conf/Settings/settings.json");
    exitGame();
}

void Scene::PauseScene::printExitPopUp()
{
    _shouldPrintExitPopUp = true;
}

void Scene::PauseScene::unPrintExitPopUp()
{
    _shouldPrintExitPopUp = false;
}

void Scene::PauseScene::printSettingsPopUp()
{
    _shouldPrintSettingsPopUp = true;
}

void Scene::PauseScene::unPrintSettingsPopUp()
{
    _shouldPrintSettingsPopUp = false;
}

void Scene::PauseScene::exitGame()
{
    unPrintExitPopUp();
    _settings->stopMusic(MusicsEnum::Game);
    _settings->playMusic(MusicsEnum::Menu);
    _nextScene = Scene::Scenes::MAIN_MENU;
}

