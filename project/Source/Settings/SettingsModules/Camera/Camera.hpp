/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include <raylib.h>

    #include <string>
    #include <any>
    #include <utility>

    #include "Position.hpp"

namespace RayLib
{
    // Camera related functions
    class CinematicCamera
    {
        public:
            CinematicCamera();
            ~CinematicCamera();

            void updateCamera();

            void startMode3D();
            void endMode3D();

        protected:
        private:
            Camera _camera;
    };
}

#endif /* !CAMERA_HPP_ */
