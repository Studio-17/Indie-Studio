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

#include "FileError.hpp"

Scene::OptionGameMenuScene::OptionGameMenuScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings) : AScene(settings), _gameSettings(gameSettings)
{
    std::vector<std::function<void(void)>> callBacks =
    {
        std::bind(&Scene::OptionGameMenuScene::back, this),
        std::bind(&Scene::OptionGameMenuScene::selectMapScene, this),
        std::bind(&Scene::OptionGameMenuScene::leftClick, this, NBPLAYERS),
        std::bind(&Scene::OptionGameMenuScene::rightClick, this, NBPLAYERS),
        std::bind(&Scene::OptionGameMenuScene::leftClick, this, NBSETS),
        std::bind(&Scene::OptionGameMenuScene::rightClick, this, NBSETS),
        std::bind(&Scene::OptionGameMenuScene::leftClick, this, GAMETIME),
        std::bind(&Scene::OptionGameMenuScene::rightClick, this, GAMETIME),
        std::bind(&Scene::OptionGameMenuScene::leftClick, this, BONUS),
        std::bind(&Scene::OptionGameMenuScene::rightClick, this, BONUS)
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
    _gameSettings = gameSettings;
}

Scene::OptionGameMenuScene::~OptionGameMenuScene()
{
}

Scene::Scenes Scene::OptionGameMenuScene::handleEvent()
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

void Scene::OptionGameMenuScene::back()
{
    _nextScene = Scene::Scenes::START_GAME;
}

void Scene::OptionGameMenuScene::selectMapScene()
{
    _nextScene = Scene::Scenes::SELECT_MAP;

    _gameSettings->setNbPlayers(std::stoi(_options.at(NBPLAYERS).second.at(_options.at(NBPLAYERS).first)->getText()));

    std::vector<bool> typePlayers;
    for (std::size_t i = 0; i < 4; i++) {
        if (i < _gameSettings->getNbPlayers())
            typePlayers.emplace_back(false);
        else
            typePlayers.emplace_back(true);
    }
    _gameSettings->setIaPlayers(typePlayers);
    _gameSettings->setNbSets(std::stoi(_options.at(NBSETS).second.at(_options.at(NBSETS).first)->getText()));
    _gameSettings->setGameTime(std::stof(_options.at(GAMETIME).second.at(_options.at(GAMETIME).first)->getText()));
    if (_options.at(BONUS).second.at(_options.at(BONUS).first)->getText() == "Oui")
        _gameSettings->enableBonus();
    else
        _gameSettings->disableBonus();
}

void Scene::OptionGameMenuScene::leftClick(OPTION index)
{
    if (_options.at(index).first == 0)
        _options.at(index).first = _options.at(index).second.size() - 1;
    else
        _options.at(index).first -= 1;
}

void Scene::OptionGameMenuScene::rightClick(OPTION index)
{
    if (_options.at(index).first == (_options.at(index).second.size() - 1))
        _options.at(index).first = 0;
    else
        _options.at(index).first += 1;
}