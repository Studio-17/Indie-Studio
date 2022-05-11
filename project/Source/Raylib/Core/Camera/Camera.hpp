/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include <memory>

    #include "raylib.h"

namespace Raylib {
    namespace Core {
            void RSetCameraMode(Camera camera, int mode);
            void RUpdateCamera(std::shared_ptr<Camera> camera);

            void RSetCameraPanControl(int keyPan);
            void RSetCameraAltControl(int keyAlt);
            void RSetCameraSmoothZoomControl(int keySmoothZoom);
            void RSetCameraMoveControls(int keyFront, int keyBack, int keyRight, int keyLeft, int keyUp, int keyDown);
    }
}

#endif /* !CAMERA_HPP_ */
