/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Window
*/

#include "Window.hpp"

RayLib::Window::Window(float width, float height, std::string const &title)
{
    InitWindow(width, height, title.c_str());
    if (!IsWindowReady())
        throw Error::WindowError("window failed to open");

}
RayLib::Window::Window(std::pair<float, float> const &size, std::string const &title)
{
    InitWindow(size.first, size.second, title.c_str());
    if (!IsWindowReady())
        throw Error::WindowError("window failed to open");
}

RayLib::Window::~Window()
{
    CloseWindow();
}

bool RayLib::Window::windowShouldClose() const
{
    return (WindowShouldClose());
}

bool RayLib::Window::isWindowReady() const
{
    return (IsWindowReady());
}

void RayLib::Window::startDrawing() const
{
    BeginDrawing();
}

void RayLib::Window::endDrawing() const
{
    EndDrawing();
}

void RayLib::Window::clearBackground(Color color) const
{
    ClearBackground(color);
}

bool RayLib::Window::isWindowFullscreen() const
{
    return (IsWindowFullscreen());
}

bool RayLib::Window::isWindowHidden() const
{
    return (IsWindowHidden());
}

bool RayLib::Window::isWindowMinimized() const
{
    return (IsWindowMinimized());
}

bool RayLib::Window::isWindowMaximized() const
{
    return (IsWindowMaximized());
}

bool RayLib::Window::isWindowFocused() const
{
    return (IsWindowFocused());
}

bool RayLib::Window::isWindowState(unsigned int flag) const
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

void RayLib::Window::toggleFullscreen()
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

int RayLib::Window::getScreenWidth() const
{
    return (GetScreenWidth());
}

int RayLib::Window::getScreenHeight() const
{
    return (GetScreenHeight());
}

void RayLib::Window::showCursor()
{
    ShowCursor();
}

void RayLib::Window::hideCursor()
{
    HideCursor();
}

bool RayLib::Window::isCursorHidden() const
{
    return (IsCursorHidden());
}

void RayLib::Window::enableCursor()
{
    EnableCursor();
}

void RayLib::Window::disableCursor()
{
    DisableCursor();
}

bool RayLib::Window::isCursorOnScreen() const
{
    return (IsCursorOnScreen());
}

void RayLib::Window::setTargetFPS(int fps)
{
    SetTargetFPS(fps);
}

int RayLib::Window::getFPS() const
{
    return (GetFPS());
}

float RayLib::Window::getFrameTime() const
{
    return (GetFrameTime());
}

double RayLib::Window::getTime(void) const
{
    return (GetTime());
}
