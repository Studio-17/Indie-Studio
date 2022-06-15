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
    #include "Settings.hpp"
    #include "Button.hpp"
    #include "Music.hpp"
    #include "Image.hpp"
    #include "Text.hpp"

namespace Scene
{
    /**
     * @brief Abstract class of the scenes of the game
     */
    class AScene : public IScene {
        public:
            /**
             * @brief Construct a new AScene object
             *
             * @param settings Shared pointer to Settings class
             */
            AScene(std::shared_ptr<Settings> settings);
            virtual ~AScene() = default;

            virtual Scenes handleEvent() = 0;
            virtual void draw() = 0;

        protected:
            std::shared_ptr<Settings> _settings; //< Shared pointer of Settings class
            std::vector<std::unique_ptr<Object::IObject>> _objects; //< A vector of every objects of the scene
            // std::vector<std::shared_ptr<IAudio>> _audios; //< A vector of every audios of the game
            Scene::Scenes _nextScene; //< Scenes Enum corresponding of the next scene to display / handle

            std::vector<std::unique_ptr<Object::Button>> _buttons; //< A vector of every Buttons of the scene
            std::unique_ptr<MyMusic> _mainMusic;
            std::vector<std::unique_ptr<Object::Image>> _images; //< A vector of every Images of the scene
            std::vector<std::unique_ptr<Object::Text>> _texts; //< A vector of every Texts of the scene
            std::string _pathToMap;
            std::vector<std::string> _mapsList;

        private:
    };
}

#endif /* !ASCENE_HPP_ */
