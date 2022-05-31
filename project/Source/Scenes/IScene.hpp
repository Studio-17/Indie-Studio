/*
** EPITECH PROJECT, 2022
** project
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
    #define ISCENE_HPP_

namespace Scene
{
    /**
     * @brief An enumeration of every scene of the game
     */
    enum class Scenes {
        QUIT,
        MAIN_MENU,
        GAME,
        SETTINGS,
        SAVE,
        SPLASH_SCREEN,
        END,
        NEW_GAME
    };

    enum SOUNDS {
        RIGHT_CLICK,
        LEFT_CLICK,
        MOUSE_SCROLL,
        MOUSE_HOVER,
        CLICK_ERROR
    };

    /**
     * @brief An interface of every scene of the game
     */
    class IScene {
        public:
            virtual ~IScene() = default;

            /**
             * @brief Fade the end of the scene in black
             */
            virtual void fadeBlack() = 0;

            /**
             * @brief To handle every event in the scene
             */
            virtual Scenes handelEvent() = 0;

            virtual void draw() = 0;


    };
}

#endif /* !ISCENE_HPP_ */
