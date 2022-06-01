/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** IRenderding
*/

#ifndef IRENDERDING_HPP_
#define IRENDERDING_HPP_

namespace Object {
    enum class RENDER_TYPE {
        MODEL,
        TEXTURE,
        ANIMATION
    };
}

    enum class ANIMATION_TYPE {
        PLAYER = 0,
    };


    enum class MODEL_TYPE {
        PLAYER_1 = 0,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4,
    };


    enum class TEXTURE_TYPE {
        PLAYER_BLUE = 0,
        PLAYER_CYAN,
        PLAYER_GREEN,
        PLAYER_PURPLE,
        PLAYER_RED,
        PLAYER_YELLOW,
    };

#endif /* !IRENDERDING_HPP_ */
