/*
** EPITECH PROJECT, 2022
** project
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
    #define GAMESCENE_HPP_

    #include "AScene.hpp"

/**
 * @brief Represents the main game scene
 * 
 */
namespace Scene {
    class GameScene : public AScene {
        public:
            GameScene(std::shared_ptr<Settings> settings);
            ~GameScene();

        protected:
        private:
    };
}

#endif /* !GAMESCENE_HPP_ */
