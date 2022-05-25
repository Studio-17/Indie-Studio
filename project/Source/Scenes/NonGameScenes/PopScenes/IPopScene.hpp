/*
** EPITECH PROJECT, 2022
** project
** File description:
** IPopScene
*/

#ifndef IPOPSCENE_HPP_
    #define IPOPSCENE_HPP_

#include "IMenuScene.hpp"

/**
 * @brief Interface to all the pop scene of the game
 * 
 */
namespace Scene {
    class IPopScene : public IMenuScene {
        public:
            IPopScene();
            ~IPopScene();

        protected:
        private:
    };
}

#endif /* !IPOPSCENE_HPP_ */
