/*
** EPITECH PROJECT, 2022
** project
** File description:
** CameraMode
*/

#ifndef CAMERAMODE_HPP_
    #define CAMERAMODE_HPP_

    #include <memory>

    #include "Camera.hpp"

namespace RayLib {
    class CameraMode {
        public:
            CameraMode(std::shared_ptr<CinematicCamera> camera) {
                BeginMode3D(camera->getCamera());
            };
            ~CameraMode() {
                EndMode3D();
            };

        protected:
        private:
    };
}

#endif /* !CAMERAMODE_HPP_ */
