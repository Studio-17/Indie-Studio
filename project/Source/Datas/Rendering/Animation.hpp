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
        class MyAnimation {
            public:
                MyAnimation(std::string const &pathToModel, unsigned int numberOfAnimations) { _animation = LoadModelAnimations(pathToModel.c_str(), &numberOfAnimations); };
                ~MyAnimation() { /* UnloadModel(_model) */ };

                ModelAnimation *getAnimation() { return _animation; };

            protected:
            private:
                ModelAnimation *_animation;
        };
    }
}

#endif /* !MYANIMATION_HPP_ */
