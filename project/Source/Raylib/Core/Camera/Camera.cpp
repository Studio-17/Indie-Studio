/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Camera
*/

#include "Camera.hpp"

#include <iostream>

void Raylib::Core::RSetCameraMode(Camera const &camera, int mode)
{
    SetCameraMode(camera, mode);
}

void Raylib::Core::RUpdateCamera(std::shared_ptr<Camera> camera)
{
    UpdateCamera(*std::static_pointer_cast<Camera*>(camera));
}

void Raylib::Core::RSetCameraPanControl(int keyPan)
{
    SetCameraPanControl(keyPan);
}

void Raylib::Core::RSetCameraAltControl(int keyAlt)
{
    SetCameraAltControl(keyAlt);
}

void Raylib::Core::RSetCameraSmoothZoomControl(int keySmoothZoom)
{
    SetCameraSmoothZoomControl(keySmoothZoom);
}

void Raylib::Core::RSetCameraMoveControls(int keyFront, int keyBack, int keyRight, int keyLeft, int keyUp, int keyDown)
{
    SetCameraMoveControls(keyFront, keyBack, keyRight, keyLeft, keyUp, keyDown);
}
