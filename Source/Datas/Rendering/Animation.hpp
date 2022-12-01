/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MyAnimation
*/

#ifndef MYANIMATION_HPP_
#define MYANIMATION_HPP_

#include <string>
#include <memory>

#include "raylib.h"

namespace Object {
    namespace Render {
        /**
         * @brief Class to handle generic loading of animations objects
         *
         */
        class MyAnimation {
            public:
                /**
                 * @brief Construct a new My Animation object
                 *
                 * @param pathToModel
                 * @param numberOfAnimations
                 */
                MyAnimation(std::string const &pathToModel, unsigned int numberOfAnimations): _numberOfAnimations(numberOfAnimations) { _animation = LoadModelAnimations(pathToModel.c_str(), &numberOfAnimations); };

                /**
                 * @brief Destroy the My Animation object
                 *
                 */
                ~MyAnimation() {};

                /**
                 * @brief Get the Animation object
                 *
                 * @return ModelAnimation*
                 */
                ModelAnimation *getAnimation() { return _animation; };

                /**
                 * @brief RAII Unload model animation
                 *
                 */
                void unload() { for (auto i = 0; i != _numberOfAnimations; i++) UnloadModelAnimation(_animation[i]);
                    RL_FREE(_animation); };

            protected:
            private:
                ModelAnimation *_animation; ///< The animation object
                unsigned int _numberOfAnimations; ///< The number of animations
        };
    }
}

#endif /* !MYANIMATION_HPP_ */
