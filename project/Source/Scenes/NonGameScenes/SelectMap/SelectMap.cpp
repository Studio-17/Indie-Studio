/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectMap
*/

#include <functional>
#include <vector>
#include <dirent.h>
#include <cmath>

#include "tools.hpp"
#include "SelectMap.hpp"

#include "FileError.hpp"

void Scene::SelectMap::smallMap(void)
{
    _pathToMap = _mapsList.at(0);
}

void Scene::SelectMap::mediumMap(void)
{
    _pathToMap = _mapsList.at(trunc(_mapsList.size() / 2 + 1));
}

void Scene::SelectMap::bigMap(void)
{
    _pathToMap = _mapsList.at(_mapsList.size() - 1);
}


Scene::SelectMap::SelectMap(std::shared_ptr<Settings> settings) : AScene(settings)
{
    DIR *dir;
    struct dirent *diread;
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::SelectMap::smallMap, this), std::bind(&Scene::SelectMap::mediumMap, this), std::bind(&Scene::SelectMap::bigMap, this)};

    _buttons = loadObjects<Object::Button>("Conf/Scenes/SelectMap/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/SelectMap/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/SelectMap/text.json");

    _nextScene = Scene::Scenes::SELECT_MAP;
    dir = opendir("Save/Maps/");
    if (dir == nullptr) {
        perror ("opendir");
    }
    while ((diread = readdir(dir)) != nullptr) {
        if (diread->d_name[0] != '.')
            _mapsList.push_back(diread->d_name);
    }
    closedir (dir);
    bigMap();
}

Scene::SelectMap::~SelectMap()
{
}

void Scene::SelectMap::fadeBlack()
{
}


Scene::Scenes Scene::SelectMap::handelEvent()
{
    _nextScene = Scene::Scenes::SELECT_MAP;

    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}


void Scene::SelectMap::draw()
{
    std::float_t speed = 0.0;

    for (std::int8_t i = 0; i < 10; i++) {
        if (i % 2 == 0)
            speed += 0.15;

        _images.at(i)->setPosition(_images.at(i)->getPosition().getX() - speed, _images.at(i)->getPosition().getY());

        if (_images.at(i)->getPosition().getX() <= -1930)
            _images.at(i)->setPosition(1928, _images.at(i)->getPosition().getY());
    }

    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}