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
    #include "MySound.hpp"
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
            /**
             * @brief Destroy the AScene object
             * 
             */
            virtual ~AScene() = default;

            /**
             * @brief Handle the event of the scene
             * 
             * @return Scenes 
             */
            virtual Scenes handleEvent() = 0;
            /**
             * @brief Draw the scene
             * 
             */
            virtual void draw() = 0;

        protected:
            std::shared_ptr<Settings> _settings; ///< Shared pointer of Settings class
            std::vector<std::unique_ptr<Object::IObject>> _objects; ///< A vector of every objects of the scene
            // std::vector<std::shared_ptr<IAudio>> _audios; ///< A vector of every audios of the game
            Scene::Scenes _nextScene; ///< Scenes Enum corresponding of the next scene to display / handle

            std::vector<std::unique_ptr<Object::Button>> _buttons; ///< A vector of every Buttons of the scene
            std::vector<std::unique_ptr<MyMusic>> _mainMusic; ///< Ptr to main music object
            std::vector<std::unique_ptr<MySound>> _audios; ///< A vector of every audios of the game
            std::vector<std::unique_ptr<Object::Image>> _images; ///< A vector of every Images of the scene
            std::vector<std::unique_ptr<Object::Text>> _texts; ///< A vector of every Texts of the scene
        private:
    };
}

#endif /* !ASCENE_HPP_ */
