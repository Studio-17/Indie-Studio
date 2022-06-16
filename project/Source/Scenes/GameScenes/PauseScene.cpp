/*
** EPITECH PROJECT, 2022
** project
** File description:
** PauseScene
*/

#include "tools.hpp"
#include "PauseScene.hpp"

Scene::PauseScene::PauseScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::function<void(void)>> callBacks) : AScene(settings),
 _shouldPrintExitPopUp(false)
{
    std::vector<std::function<void(void)>> callBack = {callBacks.at(0), callBacks.at(0), callBacks.at(1), std::bind(&Scene::PauseScene::printExitPopUp, this), std::bind(&Scene::PauseScene::save, this), std::bind(&Scene::PauseScene::exitGame, this), std::bind(&Scene::PauseScene::unPrintExitPopUp, this)};

    _buttons = loadObjects<Object::Button>("Conf/Scenes/PauseScene/button.json");
    _images = loadObjects<Object::Image>("Conf/Scenes/PauseScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/PauseScene/text.json");
    _saveFunction = callBacks.at(2);

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
    if (!_shouldPrintExitPopUp) {
        for (int index = 0; index < 4; index++)
            _buttons.at(index)->checkHover(GetMousePosition());
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
    if (!_shouldPrintExitPopUp) {
        for (int index = 0; index < 4; index++)
            _buttons.at(index)->draw();
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

void Scene::PauseScene::exitGame()
{
    _nextScene = Scene::Scenes::MAIN_MENU;
}

