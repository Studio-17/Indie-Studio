/*
** EPITECH PROJECT, 2022
** project
** File description:
** IMenuScene
*/

#ifndef IMENUSCENE_HPP_
#define IMENUSCENE_HPP_

#include "Scenes/AScene.hpp"

/**
 * @brief Interface to all the menu scenes
 * 
 */
namespace Scene {
    class IMenuScene : public AScene {
        public:
            IMenuScene();
            ~IMenuScene();

        protected:
        private:
    };
}

#endif /* !IMENUSCENE_HPP_ */
