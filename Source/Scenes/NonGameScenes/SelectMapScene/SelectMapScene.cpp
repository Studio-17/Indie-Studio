/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectMapScene
*/

#include <functional>
#include <vector>
#include <dirent.h>
#include <cmath>

#include "tools.hpp"
#include "IThreeDimensionObject.hpp"
#include "SelectMapScene.hpp"

void Scene::SelectMapScene::exitSelectMapSceneScene()
{
    _nextScene = Scenes::OPTION_GAME;
}

void Scene::SelectMapScene::runSelectPlayerScene()
{
    if(_buttons.at(3)->isEnable()) { //basic mode
        _gameSettings->setMapPath("Save/Maps/random.map");
        _gameSettings->setMapSize(std::make_pair(static_cast<float>(_mapSize), static_cast<float>(_mapSize)));
        generate(_gameSettings->getMapPath(), _gameSettings->getMapSize().first,_gameSettings->getMapSize().second, _gameSettings->getPercentageBoxDrop());
    } else { //custom mode
        _gameSettings->setMapPath(_currentPath);
        _gameSettings->setMapSize(std::make_pair(static_cast<float>(_height), static_cast<float>(_width)));
    }
    _settings->stopMusic(MusicsEnum::Menu);
    _settings->playMusic(MusicsEnum::PlayerSelectMenu);
    _nextScene = Scenes::SELECT_PLAYER;
}

void Scene::SelectMapScene::basicMode()
{
    _buttons.at(1)->enable();
    _buttons.at(1)->enableClick();
    _buttons.at(2)->disable();
    _buttons.at(3)->enable();
    _buttons.at(4)->enable();
    _buttons.at(5)->enable();
}

void Scene::SelectMapScene::customMode()
{
    if (_currentPath == "") {
        _buttons.at(1)->disable();
        _buttons.at(1)->disableClick();
    }
    _buttons.at(3)->disable();
    _buttons.at(3)->disableClick();
    _buttons.at(2)->enable();
    _buttons.at(2)->enableClick();
    _buttons.at(4)->disable();
    _buttons.at(4)->disableClick();
    _buttons.at(5)->disable();
    _buttons.at(5)->disableClick();
}

void Scene::SelectMapScene::previousMap()
{
    std::string name;

    if (_mapSize != _minMapSize) {
        _mapSize -= _scaleModifier;
        name = std::to_string(_mapSize) + "x" + std::to_string(_mapSize);
        _mapName.at(1)->setText(name);
    }
}

void Scene::SelectMapScene::nextMap()
{
    std::string name;

    if (_mapSize != _maxMapSize) {
        _mapSize += _scaleModifier;
        name = std::to_string(_mapSize) + "x" + std::to_string(_mapSize);
        _mapName.at(1)->setText(name);
    }
}

bool Scene::SelectMapScene::isGoodLineMap(std::string const &line, std::size_t sizeLine, int nbrLine)
{
    if (sizeLine != line.size()) {
        return false;
    }
    for (int i = 0; line[i] != '\0'; i++) {
        if (nbrLine % 2 == 0) {
            if (i % 2 == 0 && line[i] != 'X' && line[i] != 'x') {
                return false;
            }
            if (i % 2 == 1 && (line[i] != ' ' && line[i] != 'O')) {
                return false;
            }
        } else {
            if (i == 0 || line[i + 1] == '\0') {
                if (line[i] != 'X') {
                    return false;
                }
            } else if (line[i] != ' ' && line[i] != 'O') {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::string> Scene::SelectMapScene::getVectorMapFromFile(const std::string &filename)
{
    std::string line;
    std::ifstream myfile (filename);
    std::vector<std::string> vecMap;

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            vecMap.push_back(line);
        }
        myfile.close();
        return vecMap;
    }
    return std::vector<std::string>{};
}

bool Scene::SelectMapScene::haveGoodSpawn(std::vector<std::string> vecMap)
{
    if (vecMap.at(1)[1] != ' ' || vecMap.at(1)[2] != ' ' || vecMap.at(2)[1] != ' ') {
        return false;
    }
    if (vecMap.at(1)[vecMap.at(1).size() - 3] != ' ' || vecMap.at(1)[vecMap.at(1).size() - 2] != ' ' || vecMap.at(2)[vecMap.at(1).size() - 2] != ' ') {
        return false;
    }
    if (vecMap.at(vecMap.size() - 2)[1] != ' ' || vecMap.at(vecMap.size() - 2)[2] != ' ' || vecMap.at(vecMap.size() - 3)[1] != ' ') {
        return false;
    }
    if (vecMap.at(vecMap.size() - 2)[vecMap.at(1).size() - 3] != ' ' || vecMap.at(vecMap.size() - 2)[vecMap.at(1).size() - 2] != ' ' || vecMap.at(vecMap.size() - 3)[vecMap.at(1).size() - 2] != ' ') {
        return false;
    }
    return true;
}

bool Scene::SelectMapScene::isGoodFileMap(const std::string &filename)
{
    std::vector<std::string> vecMap = getVectorMapFromFile(filename);
    std::size_t sizeLine = vecMap.at(0).size();

    if (sizeLine % 2 != 1) {
        return false;
    }
    for (std::size_t i = 0; i != vecMap.size(); i++) {
        if (i == 0 || i + 1 == vecMap.size()) {
            if (!(vecMap.at(i).find_first_not_of(vecMap.at(i)[0]) == std::string::npos)) {
                return false;
            }
        } else if (!isGoodLineMap(vecMap.at(i), sizeLine, i)) {
            return false;
        }
    }
    if (haveGoodSpawn(vecMap)) {
        _height = vecMap.size();
        _width = vecMap.at(0).size();
        return true;
    }
    return false;
}

Scene::SelectMapScene::SelectMapScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::unique_ptr<Object::Image>> &parallax) : AScene(settings), _gameSettings(gameSettings), _parallax(parallax)
{
    std::string name;

    std::vector<std::function<void(void)>> callBacks =
    {
        std::bind(&Scene::SelectMapScene::exitSelectMapSceneScene, this),
        std::bind(&Scene::SelectMapScene::runSelectPlayerScene, this),
        std::bind(&Scene::SelectMapScene::basicMode, this),
        std::bind(&Scene::SelectMapScene::customMode, this),
        std::bind(&Scene::SelectMapScene::previousMap, this),
        std::bind(&Scene::SelectMapScene::nextMap, this)
    };

    _buttons = loadObjects<Object::Button>("Conf/Scenes/SelectMapScene/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/SelectMapScene/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/SelectMapScene/text.json");

    _currentPath = "";
    _count = 0;
    _noDroppedFilesText = loadObjects<Object::Text>("Conf/Scenes/SelectMapScene/noDroppedFile.json");
    _droppedFilesText = loadObjects<Object::Text>("Conf/Scenes/SelectMapScene/droppedFile.json");
    _mapName = loadObjects<Object::Text>("Conf/Scenes/SelectMapScene/mapsList.json");
    _minMapSize = 7;
    _maxMapSize = 41;
    _mapSize = 11;
    _scaleModifier = 2;
    name = std::to_string(_mapSize) + "x" + std::to_string(_mapSize);
    _mapName.at(1)->setText(name);
    basicMode();
    _nextScene = Scene::Scenes::SELECT_MAP;
}

Scene::SelectMapScene::~SelectMapScene()
{
}

Scene::Scenes Scene::SelectMapScene::handleEvent()
{
    int index = 0;
    std::float_t speed = 0.0;
    std::string delim = "B-YEP-400-PAR-4-1-indiestudio-martin.vanaud/project/";
    std::string newPath;

    _settings->updateMusicStream(MusicsEnum::Menu);
    for (auto &parallax : _parallax) {
        if (index % 2 == 0)
            speed += 0.15;

        parallax->setPosition(parallax->getPosition().getX() - speed, parallax->getPosition().getY());
        if (parallax->getPosition().getX() <= -1930)
            parallax->setPosition(1928, parallax->getPosition().getY());
        index++;
    }

    _nextScene = Scene::Scenes::SELECT_MAP;

    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());

    if (IsFileDropped()) {
        newPath = GetDroppedFiles(&_count)[0];
        newPath.erase(0, newPath.find(delim.c_str()) + delim.length());
        if (isGoodFileMap(newPath)) {
            _buttons.at(1)->enable();
            _buttons.at(1)->enableClick();
            _currentPath = newPath;
            _droppedFilesText.at(1)->setText(_currentPath);
        } else {
            _count = 0;
        }
    }
    handleAction();
    return _nextScene;
}


void Scene::SelectMapScene::draw()
{
    for (auto &parallax : _parallax)
        parallax->draw();
    DrawRectangle(100, 250, 800, 600, GRAY);
    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
    if (_buttons.at(2)->isEnable()) {
        if (_count == 0) {
            for (auto &text : _noDroppedFilesText)
                text->draw();
        } else {
            for (auto &text : _droppedFilesText)
                text->draw();
        }
    } else {
        for (auto &text : _mapName)
            text->draw();
    }
}

void Scene::SelectMapScene::generate(std::string const &filename, std::size_t width, std::size_t height, std::size_t percentageDrop)
{
    srand(time(NULL));
    std::size_t randomNumber = 1 + (rand() % 100);
    width -= 2;
    height -= 2;

    if ((width % 2) == 0 || (height % 2) == 0)
        throw Error::Errors("Height and Width are not compatible !");
    std::ofstream file;
    file.open(filename, std::ofstream::out);
    if (!file) {
        file.close();
        throw Error::FileError("file failed to open " + filename);
    }
    for (std::size_t one = 0; one < height + 2; one++) {
        file << static_cast<char>(Object::MAP_OBJECTS::WALL_SIDE);
    }
    file << std::endl;
    for (std::size_t x = 0; x < height; x++) {
        file << static_cast<char>(Object::MAP_OBJECTS::WALL_SIDE);
        for (std::size_t y = 0; y < width; y++) {
            if (x % 2 && y % 2)
                file << static_cast<char>(Object::MAP_OBJECTS::WALL_MIDDLE);
            else {
                randomNumber = 1 + (rand() % 100);
                if (randomNumber > percentageDrop || (x <= 1 || x >= height - 2) && (y <= 1 || y >= width - 2))
                    file << static_cast<char>(Object::MAP_OBJECTS::EMPTY);
                else
                    file << static_cast<char>(Object::MAP_OBJECTS::BOX);
            }
        }
        file << static_cast<char>(Object::MAP_OBJECTS::WALL_SIDE);
        file << std::endl;
    }
    for (std::size_t one = 0; one < height + 2; one++) {
        file << static_cast<char>(Object::MAP_OBJECTS::WALL_SIDE);
    }
    file << std::endl;
    file.close();
}

void Scene::SelectMapScene::handleAction()
{
    std::map<Action, bool> tmp = _settings->getActionPressed();

    if (tmp.at(Action::Next))
        _buttons.at(1)->click();
    else if (tmp.at(Action::Previous))
        _buttons.at(0)->click();
}
