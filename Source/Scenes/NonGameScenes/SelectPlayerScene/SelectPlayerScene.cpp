/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectPlayerScene
*/

#include <functional>
#include <algorithm>

#include "tools.hpp"
#include "SelectPlayerScene.hpp"

void Scene::SelectPlayerScene::exitSelectPlayerScene()
{
    _settings->stopMusic(MusicsEnum::PlayerSelectMenu);
    _settings->playMusic(MusicsEnum::Menu);
    _nextScene = Scenes::SELECT_MAP;
}

void Scene::SelectPlayerScene::runGame()
{
    std::vector<std::size_t> playerSkins;

    for (auto &player : _players)
        playerSkins.emplace_back(player.first);
    _gameSettings->setPlayerSkins(playerSkins);
    _applyGameSettings();
    _settings->stopMusic(MusicsEnum::PlayerSelectMenu);
    _settings->playMusic(MusicsEnum::Game);
    _nextScene = Scenes::GAME;
}

void Scene::SelectPlayerScene::leftClick(std::size_t index)
{
    if (_players.at(index).first == 0) {
        _players.at(index).first = _players.at(index).second.size() - 1;
        _playerColors.at(index).first = _playerColors.at(index).second.size() - 1;
    } else {
        _players.at(index).first -= 1;
        _playerColors.at(index).first -= 1;
    }
}

void Scene::SelectPlayerScene::rightClick(std::size_t  index)
{
    if (_players.at(index).first == (_players.at(index).second.size() - 1)) {
        _players.at(index).first = 0;
        _playerColors.at(index).first = 0;
    } else {
        _players.at(index).first += 1;
        _playerColors.at(index).first += 1;
    }
}

Scene::SelectPlayerScene::SelectPlayerScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::unique_ptr<Object::Image>> &parallax, std::function<void(void)> applyGameSettings) : AScene(settings), _gameSettings(gameSettings),
    _parallax(parallax), _applyGameSettings(applyGameSettings)
{
    std::vector<std::function<void(void)>> callBacks =
    {
        std::bind(&Scene::SelectPlayerScene::exitSelectPlayerScene, this),
        std::bind(&Scene::SelectPlayerScene::runGame, this),
        std::bind(&Scene::SelectPlayerScene::leftClick, this, 0),
        std::bind(&Scene::SelectPlayerScene::rightClick, this, 0),
        std::bind(&Scene::SelectPlayerScene::leftClick, this, 1),
        std::bind(&Scene::SelectPlayerScene::rightClick, this, 1),
        std::bind(&Scene::SelectPlayerScene::leftClick, this, 2),
        std::bind(&Scene::SelectPlayerScene::rightClick, this, 2),
        std::bind(&Scene::SelectPlayerScene::leftClick, this, 3),
        std::bind(&Scene::SelectPlayerScene::rightClick, this, 3)
    };

    _buttons = loadObjects<Object::Button>("Conf/Scenes/SelectPlayerScene/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/SelectPlayerScene/image.json");
    _playersInfo = loadObjects<Object::Image>("Conf/Scenes/SelectPlayerScene/icon.json");
    _popPlayerNames = loadObjects<Object::Image>("Conf/Scenes/SelectPlayerScene/pop.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/SelectPlayerScene/text.json");

    for (int i = 0; i < 4; i++) {
        std::string pathToImage = "Conf/Scenes/SelectPlayerScene/icons/player" + std::to_string(i + 1) + ".json";
        std::string pathToText = "Conf/Scenes/SelectPlayerScene/colors/player" + std::to_string(i + 1) + ".json";

        _players.emplace_back(0, loadObjects<Object::Image>(pathToImage));
        _playerColors.emplace_back(0, loadObjects<Object::Text>(pathToText));
    }
    _nextScene = Scene::Scenes::SELECT_PLAYER;
    _colorBar = {
        Position(227, 619),
        Position(627, 619),
        Position(1027, 619),
        Position(1427, 619)
    };
}

Scene::SelectPlayerScene::~SelectPlayerScene()
{
}

Scene::Scenes Scene::SelectPlayerScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    _settings->updateMusicStream(MusicsEnum::PlayerSelectMenu);
    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }

    _nextScene = Scene::Scenes::SELECT_PLAYER;
    handleAction();
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::SelectPlayerScene::SetInfoOfPlayers(std::size_t index)
{
    for (std::size_t i = 0; i < 4; i++) {
        if (i + 1 <= index)
            _playersInfo.at(i)->draw();
        else
            _playersInfo.at(i + 4)->draw();
    }
}

void Scene::SelectPlayerScene::draw()
{
    std::size_t index = 0;

    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &[id, player] : _players)
        player.at(id)->draw();
    for (auto &[id, playerColor] : _playerColors) {
        playerColor.at(id)->draw();
        _images.at(index + 6)->setPosition(_colorBar.at(index).getX() + (37 * id), _colorBar.at(index).getY());
        index++;
    }
    for (auto &pop : _popPlayerNames)
        pop->draw();
    SetInfoOfPlayers(_gameSettings->getNbPlayers());
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}

void Scene::SelectPlayerScene::handleAction()
{
    std::map<Action, bool> tmp = _settings->getActionPressed();

    if (tmp.at(Action::Next))
        _buttons.at(1)->click();
    else if (tmp.at(Action::Previous))
        _buttons.at(0)->click();
}
