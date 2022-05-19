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
    #include "Objects/IObject.hpp"
    #include "Audio/IAudio.hpp"

namespace Scene
{
    /**
     * @brief Abstract class of the scenes of the game
     *
     */
    class AScene : public IScene {
        public:
            AScene();
            virtual ~AScene() = default;

        protected:
            std::vector<std::shared_ptr<Object::IObject>> _objects; //< A vector of every object of the scene
            std::vector<std::shared_ptr<Audio::IAudio>> _audios; //< A vector of every audio of the game

        private:
    };
}

#endif /* !ASCENE_HPP_ */
