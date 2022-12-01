/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** InformationScene
*/

#include "tools.hpp"
#include "InformationScene.hpp"

Scene::InformationScene::InformationScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax) : AScene(settings), _parallax(parallax)
{
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::InformationScene::mainMenuScene, this), std::bind(&Scene::InformationScene::startGameScene, this)};

    _nextScene = Scene::Scenes::INFORMATION;
    _images = loadObjects<Object::Image>("Conf/Scenes/InformationScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/InformationScene/text.json");
    _buttons = loadObjects<Object::Button>("Conf/Scenes/InformationScene/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
}

Scene::InformationScene::~InformationScene()
{
}

Scene::Scenes Scene::InformationScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    _nextScene = Scene::Scenes::INFORMATION;
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

void Scene::InformationScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}

void Scene::InformationScene::handleAction()
{
    std::map<Action, bool> tmp = _settings->getActionPressed();

    if (tmp.at(Action::Next))
        startGameScene();
    else if (tmp.at(Action::Previous))
        mainMenuScene();
}

void Scene::InformationScene::mainMenuScene()
{
    _nextScene = Scene::Scenes::MAIN_MENU;
}

void Scene::InformationScene::startGameScene()
{
    _nextScene = Scene::Scenes::START_GAME;
}
