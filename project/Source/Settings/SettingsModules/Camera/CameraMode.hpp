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
    /**
     * @brief CameraMode class that defines the usage of a camera
     *
     */
    class CameraMode {
        public:
            /**
             * @brief Construct a new Camera Mode object
             *
             * @param camera
             */
            CameraMode(std::shared_ptr<CinematicCamera> camera) {
                BeginMode3D(camera->getCamera());
            };

            /**
             * @brief Destroy the Camera Mode object
             *
             */
            ~CameraMode() {
                EndMode3D();
            };

        protected:
        private:
    };
}

#endif /* !CAMERAMODE_HPP_ */
