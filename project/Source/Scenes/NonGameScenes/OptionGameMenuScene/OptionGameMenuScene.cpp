/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** OptionGameMenuScene
*/

#include <functional>

#include "tools.hpp"
#include "OptionGameMenuScene.hpp"

#include "FileError.hpp"

void Scene::OptionGameMenuScene::selectGameMenuScene()
{
    _nextScene = Scene::Scenes::GAME;
}

void Scene::OptionGameMenuScene::selectMapScene()
{
    _nextScene = Scene::Scenes::SELECT_MAP;
}

void Scene::OptionGameMenuScene::leftClick(std::uint8_t index)
{
    if (_options.at(index).first == 0)
        _options.at(index).first = _options.at(index).second.size() - 1;
    else
        _options.at(index).first -= 1;
}

void Scene::OptionGameMenuScene::rightClick(std::uint8_t index)
{
    if (_options.at(index).first == (_options.at(index).second.size() - 1))
        _options.at(index).first = 0;
    else
        _options.at(index).first += 1;
}

Scene::OptionGameMenuScene::OptionGameMenuScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    std::vector<std::function<void(void)>> callBacks =
    {
        std::bind(&Scene::OptionGameMenuScene::selectGameMenuScene, this),
        std::bind(&Scene::OptionGameMenuScene::selectMapScene, this),
        std::bind(&Scene::OptionGameMenuScene::leftClick, this, 0),
        std::bind(&Scene::OptionGameMenuScene::rightClick, this, 0),
        std::bind(&Scene::OptionGameMenuScene::leftClick, this, 1),
        std::bind(&Scene::OptionGameMenuScene::rightClick, this, 1),
        std::bind(&Scene::OptionGameMenuScene::leftClick, this, 2),
        std::bind(&Scene::OptionGameMenuScene::rightClick, this, 2),
        std::bind(&Scene::OptionGameMenuScene::leftClick, this, 3),
        std::bind(&Scene::OptionGameMenuScene::rightClick, this, 3)
    };

    _buttons = loadObjects<Object::Button>("Conf/Scenes/OptionGameMenuScene/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/OptionGameMenuScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/OptionGameMenuScene/text.json");

    _options.emplace_back(0, loadObjects<Object::Text>("Conf/Scenes/OptionGameMenuScene/player.json"));
    _options.emplace_back(0, loadObjects<Object::Text>("Conf/Scenes/OptionGameMenuScene/sets.json"));
    _options.emplace_back(0, loadObjects<Object::Text>("Conf/Scenes/OptionGameMenuScene/time.json"));
    _options.emplace_back(0, loadObjects<Object::Text>("Conf/Scenes/OptionGameMenuScene/bonus.json"));

    _nextScene = Scene::Scenes::OPTION_GAME;
}

Scene::OptionGameMenuScene::~OptionGameMenuScene()
{
}

void Scene::OptionGameMenuScene::fadeBlack()
{
}

Scene::Scenes Scene::OptionGameMenuScene::handelEvent()
{
    _nextScene = Scene::Scenes::OPTION_GAME;

    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::OptionGameMenuScene::draw()
{
    std::float_t speed = 0.0;

    for (std::int8_t i = 0; i < 10; i++) {
        if (i % 2 == 0)
            speed += 0.1;

        _images.at(i)->setPosition(_images.at(i)->getPosition().getX() - speed, _images.at(i)->getPosition().getY());

        if (_images.at(i)->getPosition().getX() <= -1930)
            _images.at(i)->setPosition(1928, _images.at(i)->getPosition().getY());
    }

    for (auto &image : _images)
        image->draw();
    for (auto &[id, option] : _options)
        option.at(id)->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}
