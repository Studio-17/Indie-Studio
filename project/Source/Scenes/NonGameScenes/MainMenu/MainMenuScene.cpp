/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#include <functional>

#include "tools.hpp"
#include "MainMenuScene.hpp"

Scene::MainMenuScene::MainMenuScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax) : AScene(settings),
    _parallax(parallax), _buttonTexture("Ressources/buttons/button2.png"), _activeButton(0)
{
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::MainMenuScene::gameScene, this), std::bind(&Scene::MainMenuScene::settingsScene, this), std::bind(&Scene::MainMenuScene::exitScene, this)};

    _nextScene = Scene::Scenes::MAIN_MENU;
    _buttons = loadObjects<Object::Button>("Conf/Scenes/MainMenu/button.json", _buttonTexture);
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/MainMenu/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/MainMenu/text.json");
}

Scene::MainMenuScene::~MainMenuScene()
{
    _buttonTexture.unload();
}

Scene::Scenes Scene::MainMenuScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;


    _nextScene = Scene::Scenes::MAIN_MENU;
    _settings->updateMusicStream(MusicsEnum::Menu);
    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    handleAction();
    return _nextScene;
}

void Scene::MainMenuScene::draw()
{
    for (auto &parallax: _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}

void Scene::MainMenuScene::handleAction()
{
    std::map<Action, bool> tmp = _settings->getActionPressed();

    if (tmp.at(Action::Down)) {
        _activeButton += 1;
        if (_activeButton >= _buttons.size())
            _activeButton = 0;
    } else if (tmp.at(Action::Up)) {
        if (_activeButton == 0)
            _activeButton = _buttons.size() - 1;
        else
            _activeButton -= 1;
    } else if (tmp.at(Action::Next))
        _buttons.at(_activeButton)->click();
    else if (tmp.at(Action::Previous))
        exitScene();
    for (auto &button : _buttons)
        button->unsetHover();
    _buttons.at(_activeButton)->setHover();
}

void Scene::MainMenuScene::gameScene()
{
    _nextScene = Scene::Scenes::INFORMATION;
}

void Scene::MainMenuScene::settingsScene()
{
    _nextScene = Scene::Scenes::SETTINGS;
}

void Scene::MainMenuScene::exitScene()
{
    _nextScene = Scene::Scenes::QUIT;
}
