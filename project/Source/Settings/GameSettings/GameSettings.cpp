/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** GameSettings
*/

#include "GameSettings.hpp"

GameSettings::GameSettings() :
_mapPath("Save/Maps/random.map"), _nbPlayers(4), _nbSets(1), _gameTime(1), _enableBonus(true)
{
}

GameSettings::~GameSettings()
{
}

void GameSettings::loadFromJson(nlohmann::json const &jsonData)
{
    _mapPath = jsonData.value("mapPath", "Save/Maps/random.map");
    _playerSkins = jsonData.value("playerSkins", std::vector<std::string>({"", "", "", ""}));
    _iaPlayers = jsonData.value("iaPlayers", std::vector<bool>({true, false, false, false}));
    _nbPlayers = jsonData.value("nbPlayers", 4);
    _nbSets = jsonData.value("nbSets", 1);
    _gameTime = jsonData.value("gameTime", 1);
    _enableBonus = jsonData.value("enableBonus", true);
}

void GameSettings::updateSettings(std::string const &filePath)
{
    std::cout << "Save: " << filePath << std::endl;
}

void GameSettings::setMapPath(std::string const &mapPath)
{
    _mapPath = mapPath;
}

void GameSettings::setMapSize(std::pair<float, float> mapSize)
{
    _mapSize = mapSize;
}

void GameSettings::setGameMap(std::shared_ptr<Object::Map> gameMap)
{
    _gameMap = gameMap;
}

void GameSettings::setPercentageBoxDrop(std::size_t percentage)
{
    _percentageBoxDrop = percentage;
}

void GameSettings::setPlayerSkins(std::vector<std::string> const &playerSkins)
{
    _playerSkins = playerSkins;
}

void GameSettings::setIaPlayers(std::vector<bool> const &iaPlayers)
{
    _iaPlayers = iaPlayers;
}

void GameSettings::setNbPlayers(std::size_t nbPlayers)
{
    _nbPlayers = nbPlayers;
}

void GameSettings::setPlayers(std::map<std::size_t, std::shared_ptr<Object::Player>> players)
{
    _players = players;
}

void GameSettings::setNbSets(std::size_t nbSets)
{
    _nbSets = nbSets;
}

void GameSettings::setGameTime(float gameTime)
{
    _gameTime = gameTime;
}

void GameSettings::enableBonus()
{
    _enableBonus = true;
}

void GameSettings::disableBonus()
{
    _enableBonus = false;
}

std::string GameSettings::getMapPath() const
{
    return _mapPath;
}

std::pair<float, float> GameSettings::getMapSize() const
{
    return _mapSize;
}

std::shared_ptr<Object::Map> GameSettings::getGameMap() const
{
    return _gameMap;
}

std::size_t GameSettings::getPercentageBoxDrop() const
{
    return _percentageBoxDrop;
}

std::vector<std::string> GameSettings::getPlayerSkins() const
{
    return _playerSkins;
}

std::vector<bool> GameSettings::getIaPlayers() const
{
    return _iaPlayers;
}

std::size_t GameSettings::getNbPlayers() const
{
    return _nbPlayers;
}

std::map<std::size_t, std::shared_ptr<Object::Player>> GameSettings::getPlayers() const
{
    return _players;
}

std::size_t GameSettings::getNbSets() const
{
    return _nbSets;
}

float GameSettings::getGameTime() const
{
    return _gameTime;
}

bool GameSettings::IsEnabledBonus() const
{
    return _enableBonus;
}