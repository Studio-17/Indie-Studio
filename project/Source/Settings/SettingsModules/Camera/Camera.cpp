/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Camera
*/

#include "Camera.hpp"

RayLib::CinematicCamera::CinematicCamera(int mode)
{
    // Define the camera to look into our 3d world
    _camera.position = {0, 100, 10};
    _camera.target = {0, 0, 0};
    _camera.up = {0, 1, 0};
    _camera.fovy = 45;
    _camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(_camera, mode);
}

RayLib::CinematicCamera::~CinematicCamera()
{
}

void RayLib::CinematicCamera::updateCamera()
{
    UpdateCamera(&_camera);
}

void RayLib::CinematicCamera::startMode3D()
{
    BeginMode3D(_camera);
}

void RayLib::CinematicCamera::endMode3D()
{
    EndMode3D();
}

void RayLib::CinematicCamera::setPosition(Position const &position)
{
    _camera.position = position.getVector3();
}

void RayLib::CinematicCamera::setTarget(Position const &target)
{
    _camera.target = target.getVector3();
}

void RayLib::CinematicCamera::setUp(Position const &up)
{
    _camera.up = up.getVector3();
}

void RayLib::CinematicCamera::setFovy(float fovy)
{
    _camera.fovy = fovy;
}

void RayLib::CinematicCamera::setProjection(int projection)
{
    _camera.projection = projection;
}
