/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Window
*/

#include <raylib.h>

#include "WindowError.hpp"
#include "Window.hpp"

Raylib::Window::Window(int size, int height, std::string const &title)
{
    InitWindow(size, height, title.c_str());

    if (!IsWindowReady())
        throw Error::WindowError(std::cerr, "window failed to open");
    // void SetWindowIcon(Image image);
}

Raylib::Window::~Window()
{
    CloseWindow();
}

bool Raylib::Window::shouldClose() const
{
    return shouldClose();
}

void Raylib::Window::setWindowSize(int width, int height)
{
    SetWindowSize(width, height);
}

void Raylib::Window::setWindowSize(std::pair<int, int> const &size)
{
    SetWindowSize(size.first, size.second);
}

std::pair<int, int> Raylib::Window::getWindowSize() const
{
    return {GetScreenWidth(), GetScreenHeight()};
}

void Raylib::Window::setFps(int fps)
{
    SetTargetFPS(fps);
}

int Raylib::Window::getFps() const
{
    return GetFPS();
}

void Raylib::Window::showCursor()
{
    ShowCursor();
}

void Raylib::Window::hideCursor()
{
    HideCursor();
}

bool Raylib::Window::isCursorHidden() const
{
    return IsCursorHidden();
}

void Raylib::Window::enableCursor()
{
    EnableCursor();
}

void Raylib::Window::disableCursor()
{
    DisableCursor();
}

bool Raylib::Window::isCursorOnScreen() const
{
    return IsCursorOnScreen();
}

