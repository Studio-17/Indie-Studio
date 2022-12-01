/*
** EPITECH PROJECT, 2022
** project
** File description:
** EndGameScene
*/

#include "EndGameScene.hpp"

void Scene::EndGameScene::goToMainMenu()
{
    _settings->stopMusic(MusicsEnum::EndGame);
    _settings->playMusic(MusicsEnum::Menu);
    _nextScene = Scene::Scenes::MAIN_MENU;
}

void Scene::EndGameScene::restartGame()
{
    _restartGameCallBack();
    _nextScene = Scene::Scenes::GAME;
}

Scene::EndGameScene::EndGameScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::unique_ptr<Object::Image>> &parallax, std::function<void(void)> restartCallBack) : AScene(settings), _gameSettings(gameSettings), _parallax(parallax)
{
    _buttons = loadObjects<Object::Button>("Conf/Scenes/EndGameScene/button.json");
    _buttons.at(0)->setCallBack(std::bind(&Scene::EndGameScene::goToMainMenu, this));
    _buttons.at(1)->setCallBack(std::bind(&Scene::EndGameScene::restartGame, this));
    _texts = loadObjects<Object::Text>("Conf/Scenes/EndGameScene/text.json");
    _images = loadObjects<Object::Image>("Conf/Scenes/EndGameScene/image.json");
    _winner = loadObjects<Object::Image>("Conf/Scenes/EndGameScene/winner.json");
    _nextScene = Scene::Scenes::END_GAME;
    _restartGameCallBack = restartCallBack;
}

Scene::Scenes Scene::EndGameScene::handleEvent()
{
    std::float_t speed = 0.0;
    int index = 0;

    _nextScene = Scene::Scenes::END_GAME;
    _settings->updateMusicStream(MusicsEnum::EndGame);
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

void Scene::EndGameScene::drawPlayerNameAndScore(Object::PLAYER_ORDER player, std::size_t score, std::size_t nbText)
{
    int resultOfPlayer = static_cast<int>(player) + 1;
    _texts.at(nbText)->setText(std::to_string(resultOfPlayer) + "J");
    _texts.at(nbText + 4)->setText(std::to_string(score));
}

void Scene::EndGameScene::drawScore()
{
    std::vector<std::pair<std::size_t, Object::PLAYER_ORDER>> playerScores = _gameSettings->getPlayersRank();
    _winnerId = static_cast<int>(playerScores.at(3).second);
    drawPlayerNameAndScore(playerScores.at(3).second, playerScores.at(3).first, 6);
    drawPlayerNameAndScore(playerScores.at(2).second, playerScores.at(2).first, 7);
    drawPlayerNameAndScore(playerScores.at(1).second, playerScores.at(1).first, 8);
    drawPlayerNameAndScore(playerScores.at(0).second, playerScores.at(0).first, 9);
}

Scene::EndGameScene::~EndGameScene()
{
}

void Scene::EndGameScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    for (auto &button : _buttons)
        button->draw();
    for (auto &image : _images)
        image->draw();
    drawScore();
    _texts.at(0)->setText(std::to_string(_winnerId + 1) + "J");
    _winner.at(static_cast<int>(_gameSettings->getPlayerSkins().at(static_cast<int>(_winnerId))))->draw();
    for (auto &text : _texts)
        text->draw();
}