/*
** EPITECH PROJECT, 2022
** project
** File description:
** SettingsScene
*/

#include "SettingsScene.hpp"

void Scene::SettingsScene::exitScene(void)
{
    _nextScene = Scene::Scenes::QUIT;
}

void Scene::SettingsScene::settingsScene(void)
{
    _nextScene = Scene::Scenes::SETTINGS;
}

void Scene::SettingsScene::newGameScene(void)
{
    _nextScene = Scene::Scenes::GAME;
}

void Scene::SettingsScene::mainMenuScene(void)
{
    _nextScene = Scene::Scenes::MAIN_MENU;
}

Scene::SettingsScene::SettingsScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    _buttons.emplace(Scene::BUTTONSNAME::MAIN_MENU, std::make_unique<Object::Button>("Ressources/buttons/button.png", 3, std::bind(&Scene::SettingsScene::mainMenuScene, this),"Ressources/buttons/click_sound.ogg", Position(700, 800, 0)));
    _nextScene = Scene::Scenes::SETTINGS;
    _gameMap = std::make_unique<Object::Map>();
    // _gameMap->generate("Save/Maps/random.map", 11, 11);
    _gameMap->process("Save/Maps/random.map");
    _playerOne = std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/models/player/player.iqm", "Ressources/models/player/blue.png"), "Ressources/models/player/player.iqm", 1, Position(10, 0, 0));
    // _playerTwo = std::make_unique<Object::Player>(std::make_pair<std::string, std::string>("Ressources/models/player/player.iqm", "Ressources/models/player/red.png"), "Ressources/models/player/player.iqm", 1, Position(0, 0, 0));
}



Scene::SettingsScene::~SettingsScene()
{
}

void Scene::SettingsScene::fadeBlack()
{

}

bool Scene::SettingsScene::collideMap()
{
    for (auto &object : _gameMap->getMapObjects()) {
    //     if (object.getMapObject() != Object::MAP_OBJECTS::GROUND && object.getPosition().getY() == 0) {
            // if (_playerOne->getPosition().getX() == object.getPosition().getX() && _playerOne->getPosition().getZ() ==  object.getPosition().getZ())
            //     return (true);
            // if (_playerOne->getPosition().getX() > object.getPosition().getX() && _playerOne->getPosition().getX() <= (object.getPosition().getX() + 10)) {
        std::cout << "  position of the player and map" << _playerOne->getPosition() << "  "  << object.getPosition() << std::endl;
            //     return true;
            // }
        //     std::cout << "cube is at -> " << object.getPosition() << std::endl;
    //     }
        // _playerOne->getPosition().getZ() >= object.getPosition().getZ() && _playerOne->getPosition().getZ() <= object.getPosition().getZ() + 10
    }
    return false;
    // if (_playerOne->getPosition().getX() ==  object.getPosition().getX() && object.getPosition().getY() == 0)
    //     return ()
}

Scene::Scenes Scene::SettingsScene::handelEvent()
{
    _nextScene = Scene::Scenes::SETTINGS;
    for (auto &[type, button] : _buttons)
        button->checkHover(GetMousePosition());
    if (IsKeyDown(KEY_UP) && !collideMap())
        _playerOne->move((Position){ _playerOne->getPosition().getX(), _playerOne->getPosition().getY(), _playerOne->getPosition().getZ() + 0.2f});
    if (IsKeyDown(KEY_DOWN)  && !collideMap())
        _playerOne->move((Position){ _playerOne->getPosition().getX(), _playerOne->getPosition().getY(), _playerOne->getPosition().getZ() - 0.2f});
    if (IsKeyDown(KEY_LEFT)  && !collideMap())
        _playerOne->move((Position){ _playerOne->getPosition().getX() + 0.2f, _playerOne->getPosition().getY(), _playerOne->getPosition().getZ()});
    if (IsKeyDown(KEY_RIGHT)  && !collideMap())
        _playerOne->move((Position){ _playerOne->getPosition().getX() - 0.2f, _playerOne->getPosition().getY(), _playerOne->getPosition().getZ()});
    return _nextScene;
}

void Scene::SettingsScene::draw()
{
    _settings->getCamera()->startMode3D();

        DrawLine3D((Vector3){-100, 0, 0}, (Vector3){100, 0, 0}, GREEN);     // X
        DrawLine3D((Vector3){0, -100, 0}, (Vector3){0, 100, 0}, RED);       // Y
        DrawLine3D((Vector3){0, 0, -100}, (Vector3){0, 0, 100}, DARKBLUE);  // Z

        _gameMap->draw();
        _playerOne->setScale(5.0f);
        _playerOne->draw();

        // _playerTwo->setScale(5.0f);
        // _playerTwo->setPosition(10, 0, 0);
        // _playerTwo->draw();

    _settings->getCamera()->endMode3D();

    for (auto &[type, button] : _buttons)
        button->draw();
}
