/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** GameSettings
*/

#include "GameSettings.hpp"

GameSettings::GameSettings() :
_mapPath("Save/Maps/random.map"), _nbPlayers(4), _nbSets(1), _gameTime(1), _enableBonus(true), _iaPlayers({false, false, false, false})
{
}

GameSettings::~GameSettings()
{
}

void GameSettings::loadFromJson(nlohmann::json const &jsonData)
{
    _mapPath = jsonData.value("mapPath", "Save/Maps/random.map");
    _playerSkins = jsonData.value("playerSkins", std::vector<std::string>({"", "", "", ""}));
    _iaPlayers = jsonData.value("iaPlayers", std::vector<bool>({false, false, false, false}));
    _nbPlayers = jsonData.value("nbPlayers", 4);
    _nbSets = jsonData.value("nbSets", 1);
    _gameTime = jsonData.value("gameTime", 1);
    _enableBonus = jsonData.value("enableBonus", true);
}

void GameSettings::setMapPath(std::string const &mapPath)
{
    _mapPath = mapPath;
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
