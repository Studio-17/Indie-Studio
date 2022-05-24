/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Camera
*/

#include "Camera.hpp"

RayLib::CinematicCamera::CinematicCamera(Position position, Position target, CameraMode cameraMode, CameraProjection projection)
{
    setPosition(position);
    setTarget(position);
    setMode(cameraMode);
    setProjection(projection);
}

RayLib::CinematicCamera::~CinematicCamera()
{
}

void RayLib::CinematicCamera::updateCamera()
{
    UpdateCamera(&_camera);
}

void RayLib::CinematicCamera::setPosition(float x, float y, float z)
{
    _camera.position.x = x;
    _camera.position.y = y;
    _camera.position.z = z;
}

void RayLib::CinematicCamera::setTarget(float x, float y, float z)
{
    _camera.target.x = x;
    _camera.target.y = y;
    _camera.target.z = z;
}

void RayLib::CinematicCamera::setPosition(Position position)
{
    _camera.position.x = position.getX();
    _camera.position.y = position.getY();
    _camera.position.z = position.getZ();
}

void RayLib::CinematicCamera::setTarget(Position target)
{
    _camera.target.x = target.getX();
    _camera.target.y = target.getY();
    _camera.target.z = target.getZ();
}

void RayLib::CinematicCamera::movePosition(float x, float y, float z)
{
    _camera.position.x += x;
    _camera.position.y += y;
    _camera.position.z += z;
}

void RayLib::CinematicCamera::moveTarget(float x, float y, float z)
{
    _camera.target.x += x;
    _camera.target.y += y;
    _camera.target.z += z;
}

void RayLib::CinematicCamera::setUp(float x, float y, float z)
{
    _camera.up.x = x;
    _camera.up.y = y;
    _camera.up.z = z;
}

void RayLib::CinematicCamera::setFieldOfView(float fov)
{
    _camera.fovy = fov;
}

void RayLib::CinematicCamera::setMode(CameraMode mode)
{
    SetCameraMode(_camera, mode);
}

void RayLib::CinematicCamera::setProjection(CameraProjection projection)
{
    _camera.projection = projection;
}