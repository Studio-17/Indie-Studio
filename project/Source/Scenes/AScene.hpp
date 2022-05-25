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
    // #include "IAudio.hpp"
    #include "Settings.hpp"

namespace Scene
{
    /**
     * @brief Abstract class of the scenes of the game
     */
    class AScene : public IScene {
        public:
            AScene(std::shared_ptr<Settings> settings);
            virtual ~AScene() = default;

            virtual Scenes run() = 0;
            virtual void fadeBlack() = 0;
            virtual Scenes handelEvent() = 0;

        protected:
            std::shared_ptr<Settings> _settings;
            std::vector<std::shared_ptr<Object::IObject>> _objects; //< A vector of every object of the scene
            // std::vector<std::shared_ptr<IAudio>> _audios; //< A vector of every audio of the game

        private:
    };
}

#endif /* !ASCENE_HPP_ */
