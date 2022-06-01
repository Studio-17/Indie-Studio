/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #include <raylib.h>

    #include <string>
    #include <any>
    #include <utility>

    #include "WindowError.hpp"

namespace RayLib
{
    class Window
    {
        public:
            Window(float width, float height, std::string const &title);
            Window(std::pair<float, float> const &size, std::string const &title);
            ~Window();

            // Window-related functions
            bool windowShouldClose() const;                                       // Check if KEY_ESCAPE pressed or Close icon pressed

            bool isWindowReady() const;                                           // Check if window has been initialized successfully

            void startDrawing(void) const;
            void endDrawing(void) const;
            void clearBackground(Color color) const;

            bool isWindowFullscreen() const;                                      // Check if window is currently fullscreen
            bool isWindowHidden() const;                                          // Check if window is currently hidden (only PLATFORM_DESKTOP)
            bool isWindowMinimized() const;                                       // Check if window is currently minimized (only PLATFORM_DESKTOP)
            bool isWindowMaximized() const;                                       // Check if window is currently maximized (only PLATFORM_DESKTOP)
            bool isWindowFocused() const;                                         // Check if window is currently focused (only PLATFORM_DESKTOP)

            bool isWindowState(unsigned int flag) const;                              // Check if one specific window flag is enabled
            void setWindowState(unsigned int flags);                            // Set window configuration state using flags
            void clearWindowState(unsigned int flags);                          // Clear window configuration state flags

            void toggleFullscreen();                                        // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)

            void setWindowIcon(Image const &image);                             // Set icon for window (only PLATFORM_DESKTOP)
            void setWindowTitle(std::string const &title);                      // Set title for window (only PLATFORM_DESKTOP)
            void setWindowMinSize(int width, int height);                       // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
            void setWindowSize(int width, int height);                          // Set window dimensions

            int getScreenWidth() const;                                           // Get current screen width
            int getScreenHeight() const;                                          // Get current screen height

            // Cursor-related functions
            void showCursor();                                              // Shows cursor
            void hideCursor();                                              // Hides cursor
            bool isCursorHidden() const;                                          // Check if cursor is not visible

            void enableCursor();                                            // Enables cursor (unlock cursor)
            void disableCursor();                                           // Disables cursor (lock cursor)

            bool isCursorOnScreen() const;                                        // Check if cursor is on the screen

            // Timing-related functions
            void setTargetFPS(int fps);                                         // Set target FPS (maximum)
            int getFPS() const;                                                   // Get current FPS

            float getFrameTime() const;                                           // Get time in seconds for last frame drawn (delta time)

            double getTime() const;                                               // Get elapsed time in seconds since InitWindow()

        protected:
        private:
    };
}

#endif /* !WINDOW_HPP_ */
