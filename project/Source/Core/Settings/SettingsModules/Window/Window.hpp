/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>
#include <any>

#include <utility>

#include "raylib.h"

namespace RayLib
{
    class Window
    {
        public:
            Window();
            ~Window();

            // Window-related functions
            void initWindow(int width, int height, std::string const &title);   // Initialize window and OpenGL context
            bool windowShouldClose(void);                                       // Check if KEY_ESCAPE pressed or Close icon pressed
            void closeWindow(void);                                             // Close window and unload OpenGL context

            bool isWindowReady(void);                                           // Check if window has been initialized successfully

            bool isWindowFullscreen(void);                                      // Check if window is currently fullscreen
            bool isWindowHidden(void);                                          // Check if window is currently hidden (only PLATFORM_DESKTOP)
            bool isWindowMinimized(void);                                       // Check if window is currently minimized (only PLATFORM_DESKTOP)
            bool isWindowMaximized(void);                                       // Check if window is currently maximized (only PLATFORM_DESKTOP)
            bool isWindowFocused(void);                                         // Check if window is currently focused (only PLATFORM_DESKTOP)

            bool isWindowState(unsigned int flag);                              // Check if one specific window flag is enabled
            void setWindowState(unsigned int flags);                            // Set window configuration state using flags
            void clearWindowState(unsigned int flags);                          // Clear window configuration state flags

            void toggleFullscreen(void);                                        // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)

            void setWindowIcon(Image const &image);                             // Set icon for window (only PLATFORM_DESKTOP)
            void setWindowTitle(std::string const &title);                      // Set title for window (only PLATFORM_DESKTOP)
            void setWindowMinSize(int width, int height);                       // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
            void setWindowSize(int width, int height);                          // Set window dimensions

            int getScreenWidth(void);                                           // Get current screen width
            int getScreenHeight(void);                                          // Get current screen height

            // Cursor-related functions
            void showCursor(void);                                              // Shows cursor
            void hideCursor(void);                                              // Hides cursor
            bool isCursorHidden(void);                                          // Check if cursor is not visible

            void enableCursor(void);                                            // Enables cursor (unlock cursor)
            void disableCursor(void);                                           // Disables cursor (lock cursor)

            bool isCursorOnScreen(void);                                        // Check if cursor is on the screen

            // Timing-related functions
            void setTargetFPS(int fps);                                         // Set target FPS (maximum)
            int getFPS(void);                                                   // Get current FPS

            float getFrameTime(void);                                           // Get time in seconds for last frame drawn (delta time)

            double getTime(void);                                               // Get elapsed time in seconds since InitWindow()

        protected:
        private:
    };
}

#endif /* !WINDOW_HPP_ */
