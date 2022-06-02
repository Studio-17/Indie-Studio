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

    _settings->setNbPlayers((std::size_t) std::stoi(_options.at(0).second.at(_options.at(0).first)->getText()));
    _settings->setNbSets((std::size_t) std::stoi(_options.at(1).second.at(_options.at(1).first)->getText()));
    _settings->setGameTime((std::float_t) std::stoi(_options.at(2).second.at(_options.at(2).first)->getText()));
    if (_options.at(3).second.at(_options.at(2).first)->getText() == "Oui")
        _settings->setEnableBonus(true);
    else
        _settings->setEnableBonus(false);
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
    _parallax = loadObjects<Object::Image>("Conf/Scenes/parallax.json");

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
    std::float_t speed = 0.0;
    int index = 0;

    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }

    _nextScene = Scene::Scenes::OPTION_GAME;

    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::OptionGameMenuScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &[id, option] : _options)
        option.at(id)->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}
