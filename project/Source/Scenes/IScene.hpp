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

    class IScene {
        public:
            virtual ~IScene() = default;
            virtual Scenes run() = 0;

    };
}

#endif /* !ISCENE_HPP_ */
