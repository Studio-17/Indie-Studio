/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Window
*/

#include "Window.hpp"

RayLib::Window::Window()
{
}

RayLib::Window::~Window()
{
}

void RayLib::Window::initWindow(int width, int height, std::string const &title)
{
    InitWindow(width, height, title.c_str());
}

bool RayLib::Window::windowShouldClose(void)
{
    return (WindowShouldClose());
}

void RayLib::Window::closeWindow(void)
{
    CloseWindow();
}

bool RayLib::Window::isWindowReady(void)
{
    return (IsWindowReady());
}

bool RayLib::Window::isWindowFullscreen(void)
{
    return (IsWindowFullscreen());
}

bool RayLib::Window::isWindowHidden(void)
{
    return (IsWindowHidden());
}

bool RayLib::Window::isWindowMinimized(void)
{
    return (IsWindowMinimized());
}

bool RayLib::Window::isWindowMaximized(void)
{
    return (IsWindowMaximized());
}

bool RayLib::Window::isWindowFocused(void)
{
    return (IsWindowFocused());
}

bool RayLib::Window::isWindowState(unsigned int flag)
{
    return (IsWindowState(flag));
}

void RayLib::Window::setWindowState(unsigned int flags)
{
    SetWindowState(flags);
}

void RayLib::Window::clearWindowState(unsigned int flags)
{
    ClearWindowState(flags);
}

void RayLib::Window::toggleFullscreen(void)
{
    ToggleFullscreen();
}

void RayLib::Window::setWindowIcon(Image const &image)
{
    SetWindowIcon(image);
}

void RayLib::Window::setWindowTitle(std::string const &title)
{
    SetWindowTitle(title.c_str());
}

void RayLib::Window::setWindowMinSize(int width, int height)
{
    SetWindowMinSize(width, height);
}

void RayLib::Window::setWindowSize(int width, int height)
{
    SetWindowSize(width, height);
}

int RayLib::Window::getScreenWidth(void)
{
    return (GetScreenWidth());
}

int RayLib::Window::getScreenHeight(void)
{
    return (GetScreenHeight());
}

void RayLib::Window::showCursor(void)
{
    ShowCursor();
}

void RayLib::Window::hideCursor(void)
{
    HideCursor();
}

bool RayLib::Window::isCursorHidden(void)
{
    return (IsCursorHidden());
}

void RayLib::Window::enableCursor(void)
{
    EnableCursor();
}

void RayLib::Window::disableCursor(void)
{
    DisableCursor();
}

bool RayLib::Window::isCursorOnScreen(void)
{
    return (IsCursorOnScreen());
}

void RayLib::Window::setTargetFPS(int fps)
{
    SetTargetFPS(fps);
}

int RayLib::Window::getFPS(void)
{
    return (GetFPS());
}

float RayLib::Window::getFrameTime(void)
{
    return (GetFrameTime());
}

double RayLib::Window::getTime(void)
{
    return (GetTime());
}
