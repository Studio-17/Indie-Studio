/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** OptionGameMenuScene
*/

#include <functional>

#include "tools.hpp"
#include "OptionGameMenuScene.hpp"

Scene::OptionGameMenuScene::OptionGameMenuScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::unique_ptr<Object::Image>> &parallax) : AScene(settings), _gameSettings(gameSettings),
    _parallax(parallax), _activeButton(0)
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
    _emptyButton = loadObjects<Object::Button>("Conf/Scenes/OptionGameMenuScene/empty_button.json");

    _options.emplace_back(0, loadObjects<Object::Text>("Conf/Scenes/OptionGameMenuScene/Option/player.json"));
    _options.emplace_back(0, loadObjects<Object::Text>("Conf/Scenes/OptionGameMenuScene/Option/sets.json"));
    _options.emplace_back(0, loadObjects<Object::Text>("Conf/Scenes/OptionGameMenuScene/Option/time.json"));
    _options.emplace_back(0, loadObjects<Object::Text>("Conf/Scenes/OptionGameMenuScene/Option/bonus.json"));

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

    _settings->updateMusicStream(MusicsEnum::Menu);
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
    handleAction();
    return _nextScene;
}

void Scene::OptionGameMenuScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &button : _emptyButton)
        button->draw();
    for (auto &button : _buttons)
        button->draw();
    for (auto &[id, option] : _options)
        option.at(id)->draw();
    for (auto &text : _texts)
        text->draw();
}

void Scene::OptionGameMenuScene::handleAction()
{
    std::map<Action, bool> tmp = _settings->getActionPressed();
    if (tmp.at(Action::Down)) {
        _activeButton += 1;
        if (_activeButton >= _emptyButton.size())
            _activeButton = 0;
    } else if (tmp.at(Action::Up)) {
        if (_activeButton == 0)
            _activeButton = _emptyButton.size() - 1;
        else
            _activeButton -= 1;
    } else if (tmp.at(Action::Left)) {
        _buttons.at(2 + _activeButton * 2)->setHover();
        _buttons.at(2 + _activeButton * 2)->click();
    } else if (tmp.at(Action::Right)) {
        _buttons.at(2 + _activeButton * 2 + 1)->setHover();
        _buttons.at(2 + _activeButton * 2 + 1)->click();
    } else if (tmp.at(Action::Next)) {
        _buttons.at(1)->click();
    } else if (tmp.at(Action::Previous)) {
        _buttons.at(0)->click();
    }
    for (auto &button : _emptyButton)
        button->unsetHover();
    _emptyButton.at(_activeButton)->setHover();
}

void Scene::OptionGameMenuScene::back()
{
    _nextScene = Scene::Scenes::START_GAME;
}

void Scene::OptionGameMenuScene::selectMapScene()
{
    _nextScene = Scene::Scenes::SELECT_MAP;
    std::vector<bool> typePlayers;

    _gameSettings->setNbPlayers(std::stoi(_options.at(NBPLAYERS).second.at(_options.at(NBPLAYERS).first)->getText()));
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