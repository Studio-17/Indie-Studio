/*
** EPITECH PROJECT, 2022
** project
** File description:
** AScene
*/

#ifndef ASCENE_HPP_
    #define ASCENE_HPP_

    #include <vector>
    #include <memory>

    #include "IScene.hpp"
    #include "IObject.hpp"
    #include "Settings.hpp"
    #include "Button.hpp"
    #include "Music.hpp"
    #include "Image.hpp"
    #include "Text.hpp"


namespace Scene
{

    enum class BUTTONSNAME {
        NEWGAME,
        LOADGAME,
        EXIT,
        SETTINGS,
        MAIN_MENU
    };

    /**
     * @brief Abstract class of the scenes of the game
     */
    class AScene : public IScene {
        public:
            AScene(std::shared_ptr<Settings> settings);
            virtual ~AScene() = default;

            virtual void fadeBlack() = 0;
            virtual Scenes handelEvent() = 0;

        protected:
            std::shared_ptr<Settings> _settings;
            std::vector<std::unique_ptr<Object::IObject>> _objects; //< A vector of every object of the scene
            // std::vector<std::shared_ptr<IAudio>> _audios; //< A vector of every audio of the game
            Scene::Scenes _nextScene;

            std::vector<std::unique_ptr<Object::Button>> _buttons;
            std::unique_ptr<MyMusic> _mainMusic;
            std::vector<std::unique_ptr<Object::Image>> _images;
            std::vector<std::unique_ptr<Object::Text>> _texts;

        private:
    };
}

#endif /* !ASCENE_HPP_ */
