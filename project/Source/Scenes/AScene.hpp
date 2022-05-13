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

namespace Scene
{
    class AScene : public IScene {
        public:
            AScene();
            virtual ~AScene() = default;

            virtual void fadeBlack() = 0;

        protected:
            std::vector<std::shared_ptr<Object::IObject>> _objects;

        private:
    };
}

#endif /* !ASCENE_HPP_ */
