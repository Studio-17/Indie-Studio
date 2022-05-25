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
            CinematicCamera(Position position, Position target, CameraMode cameraMode, CameraProjection projection);
            ~CinematicCamera();

            void updateCamera();

            void setPosition(float x, float y, float z);
            void setTarget(float x, float y, float z);

            void setPosition(Position position);
            void setTarget(Position target);

            void movePosition(float x, float y, float z);
            void moveTarget(float x, float y, float z);

            void setUp(float x, float y, float z);
            void setFieldOfView(float fov);

            void setMode(CameraMode mode);
            void setProjection(CameraProjection projection);

        protected:
        private:
            Camera _camera;
    };
}

#endif /* !CAMERA_HPP_ */
