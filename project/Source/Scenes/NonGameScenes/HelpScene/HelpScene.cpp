/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** HelpScene
*/

#include "HelpScene.hpp"
#include "tools.hpp"

Scene::HelpScene::HelpScene(std::shared_ptr<Settings> settings, std::vector<std::unique_ptr<Object::Image>> &parallax) : AScene(settings),
    _parallax(parallax)
{
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::HelpScene::backScene, this)};

    _nextScene = Scene::Scenes::HELP;
    _images = loadObjects<Object::Image>("Conf/Scenes/HelpScene/image.json");
    _buttons = loadObjects<Object::Button>("Conf/Scenes/HelpScene/button.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/HelpScene/text.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
}

Scene::HelpScene::~HelpScene()
{
}

Scene::Scenes Scene::HelpScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    _nextScene = Scene::Scenes::HELP;
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
    return _nextScene;
}

void Scene::HelpScene::draw()
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

void Scene::HelpScene::backScene()
{
    _nextScene = Scene::Scenes::SETTINGS;
}
