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
    /**
     * @brief Camera class that handles movement, flags and direction of the camera in the 3D environment
     */
    class CinematicCamera
    {
        public:
            /**
             * @brief Construct a new Cinematic Camera object
             *
             * @param mode
             */
            CinematicCamera(int mode = CAMERA_FREE);
            /**
             * @brief Destroy the Cinematic Camera object
             *
             */
            ~CinematicCamera();

            /**
             * @brief Update the camera
             *
             */
            void updateCamera();

            /**
             * @brief Begin the 3D drawing mode
             *
             */
            void startMode3D();
            /**
             * @brief End the 3D drawing mode
             *
             */
            void endMode3D();

            /**
             * @brief Get the Camera object
             *
             * @return Camera
             */
            Camera getCamera() const;

            /**
             * @brief Set the Position object
             *
             * @param position
             */
            void setPosition(Position const &position);
            /**
             * @brief Set the Target object
             *
             * @param target
             */
            void setTarget(Position const &target);
            /**
             * @brief Set the Up object
             *
             * @param up
             */
            void setUp(Position const &up);
            /**
             * @brief Set the Fovy object
             *
             * @param fovy
             */
            void setFovy(float fovy);
            /**
             * @brief Set the Projection object
             *
             * @param projection
             */
            void setProjection(int projection);

        protected:
        private:
            Camera _camera; ///< Camera object
    };
}

#endif /* !CAMERA_HPP_ */
