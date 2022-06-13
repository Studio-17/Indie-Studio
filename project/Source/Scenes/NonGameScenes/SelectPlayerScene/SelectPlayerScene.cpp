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

#include "FileError.hpp"

void Scene::SelectPlayerScene::exitSelectPlayerScene()
{
    _nextScene = Scenes::SELECT_MAP;
}

void Scene::SelectPlayerScene::runGame()
{
    std::vector<Position> playerPositions = _gameSettings->getGameMap()->getMapCorners(_gameSettings->getMapSize().first, _gameSettings->getMapSize().second);
    std::map<std::size_t, std::shared_ptr<Object::Player>> players = _gameSettings->getPlayers();

    _gameSettings->getGameMap()->process(_gameSettings->getMapPath());
    players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1))->setPosition(playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER1)));
    players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER2))->setPosition(playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER2)));
    players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER3))->setPosition(playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER3)));
    players.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER4))->setPosition(playerPositions.at(static_cast<char>(Object::PLAYER_ORDER::PLAYER4)));
    _gameSettings->setPlayers(players);
    _nextScene = Scenes::GAME;
}

void Scene::SelectPlayerScene::leftClick(std::uint8_t index)
{
    if (_players.at(index).first == 0)
        _players.at(index).first = _players.at(index).second.size() - 1;
    else
        _players.at(index).first -= 1;
}

void Scene::SelectPlayerScene::rightClick(std::uint8_t  index)
{
    if (_players.at(index).first == (_players.at(index).second.size() - 1))
        _players.at(index).first = 0;
    else
        _players.at(index).first += 1;
}

Scene::SelectPlayerScene::SelectPlayerScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings) : AScene(settings), _gameSettings(gameSettings)
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
    _texts = loadObjects<Object::Text>("Conf/Scenes/SelectPlayerScene/text.json");
    _parallax = loadObjects<Object::Image>("Conf/Scenes/parallax.json");

    for (int i = 0; i < 4; i++) {
        std::string pathtofile = "Conf/Scenes/SelectPlayerScene/icons/player" + std::to_string(i + 1) + ".json";

        _players.emplace_back(0, loadObjects<Object::Image>(pathtofile));
    }

    _nextScene = Scene::Scenes::SELECT_PLAYER;
}

Scene::SelectPlayerScene::~SelectPlayerScene()
{
}

Scene::Scenes Scene::SelectPlayerScene::handleEvent()
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

    _nextScene = Scene::Scenes::SELECT_PLAYER;

    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::SelectPlayerScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &image : _images)
        image->draw();
    for (auto &[id, player] : _players)
        player.at(id)->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}

