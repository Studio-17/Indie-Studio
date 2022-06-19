/*
** EPITECH PROJECT, 2022
** project
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
    #define ISCENE_HPP_

/**
 * @brief A namesapce grouping every scene of the game
 */
namespace Scene
{
    /**
     * @brief An enumeration of every scene of the game
     */
    enum class Scenes {
        MAIN_MENU,
        QUIT,
        START_GAME,
        SETTINGS,
        GAME,
        BINDING_MENU,
        SAVE,
        SPLASH_SCREEN,
        END,
        OPTION_GAME,
        SELECT_MAP,
        SELECT_PLAYER,
        END_GAME,
        CREDITS,
        INTRODUCTION,
        HELP,
        INFORMATION
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
            /**
             * @brief Construct a new IScene object
             *
             * @param settings Shared pointer to Settings class
             */
            virtual ~IScene() = default;

            /**
             * @brief To handle every event in the scene
             */
            virtual Scenes handleEvent() = 0;

            /**
             * @brief To draw every object of the Scene
             */
            virtual void draw() = 0;
    };
}

#endif /* !ISCENE_HPP_ */
