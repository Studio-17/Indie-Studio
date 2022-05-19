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
    enum Scenes {
        QUIT = -1,
        MAIN_MENU,
        GAME,
        SETTINGS,
        SAVE,
        SPLASH_SCREEN,
        END
    };

    enum SOUNDS {
        RIGHT_CLICK,
        LEFT_CLICK,
        MOUSE_SCROLL,
        MOUSE_HOVER,
        CLICK_ERROR
    };

    class IScene {
        public:
            virtual ~IScene() = default;
            virtual Scenes run() = 0;
            virtual void fadeBlack() = 0;
            virtual void handelEvent() = 0;


    };
}

#endif /* !ISCENE_HPP_ */
