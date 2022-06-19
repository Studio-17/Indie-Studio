/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** IRenderding
*/

#ifndef IRENDERDING_HPP_
    #define IRENDERDING_HPP_

namespace Object {
    /**
     * @brief Enum to define the type of rendering
     *
     */
    enum class RENDER_TYPE {
        MODEL,
        TEXTURE,
        ANIMATION
    };
}

/**
 * @brief Enum to handle animation types
 *
 */
enum class ANIMATION_TYPE {
    PLAYER = 0,
};

/**
 * @brief Enum to define model types
 *
 */
enum class MODEL_TYPE {
    PLAYER_1 = 0,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
};

/**
 * @brief Enum to define textures type
 *
 */
enum class TEXTURE_TYPE {
    PLAYER_BLUE = 0,
    PLAYER_CYAN,
    PLAYER_GREEN,
    PLAYER_PURPLE,
    PLAYER_RED,
    PLAYER_YELLOW,
    PLAYER_WHITE,
    PLAYER_PINK,
};

#endif /* !IRENDERDING_HPP_ */
