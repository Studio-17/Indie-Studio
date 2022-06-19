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
    /**
     * @brief Window class
     *
     */
    class Window
    {
        public:
            /**
             * @brief Construct a new Window object
             *
             * @param width
             * @param height
             * @param title
             */
            Window(float width, float height, std::string const &title);
            /**
             * @brief Construct a new Window object
             *
             * @param size
             * @param title
             */
            Window(std::pair<float, float> const &size, std::string const &title);

            /**
             * @brief Destroy the Window object
             *
             */
            ~Window();

            /**
             * @brief Check if KEY_ESCAPE pressed or Close icon pressed
             *
             * @return true
             * @return false
             */
            bool windowShouldClose() const;

            /**
             * @brief Check if window has been initialized successfully
             *
             * @return true
             * @return false
             */
            bool isWindowReady() const;

            /**
             * @brief Begin drawing 2D plan
             *
             */
            void startDrawing(void) const;
            /**
             * @brief End drawing 2D plan
             *
             */
            void endDrawing(void) const;
            /**
             * @brief Refresh backgournd with a constant color
             *
             * @param color
             */
            void clearBackground(Color color) const;

            /**
             * @brief Check if window is currently fullscreen
             *
             * @return true if window is fullscreen
             * @return false if window is not fullscreen
             */
            bool isWindowFullscreen() const;
            /**
             * @brief Check if window is currently hidden (only PLATFORM_DESKTOP)
             *
             * @return true if window is hidden
             * @return false if window is not hidden
             */
            bool isWindowHidden() const;
            /**
             * @brief Check if window is currently minimized (only PLATFORM_DESKTOP)
             *
             * @return true if window is minimized
             * @return false if window is not minimized
             */
            bool isWindowMinimized() const;
            /**
             * @brief Check if window is currently maximized (only PLATFORM_DESKTOP)
             *
             * @return true if window is maximized
             * @return false if window is not maximized
             */
            bool isWindowMaximized() const;
            /**
             * @brief Check if window is currently focused (only PLATFORM_DESKTOP)
             *
             * @return true if window is focused
             * @return false if window is not focused
             */
            bool isWindowFocused() const;

            /**
             * @brief Check if one specific window flag is enabled
             *
             * @return true
             * @return false
             */
            bool isWindowState(unsigned int flag) const;
            /**
             * @brief Set window configuration state using flags
             *
             * @return true
             * @return false
             */
            void setWindowState(unsigned int flags);
            /**
             * @brief Clear window configuration state flags
             *
             * @return true
             * @return false
             */
            void clearWindowState(unsigned int flags);

            /**
             * @brief Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
             *
             */
            void toggleFullscreen();

            /**
             * @brief Set icon for window (only PLATFORM_DESKTOP)
             *
             * @param image
             */
            void setWindowIcon(Image const &image);
            /**
             * @brief Set title for window (only PLATFORM_DESKTOP)
             *
             * @param title
             */
            void setWindowTitle(std::string const &title);
            /**
             * @brief Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
             *
             * @param width
             * @param height
             */
            void setWindowMinSize(int width, int height);
            /**
             * @brief Set window dimensions
             *
             * @param width
             * @param height
             */
            void setWindowSize(int width, int height);

            /**
             * @brief Get current screen width
             *
             * @return int
             */
            int getScreenWidth() const;
            /**
             * @brief Get current screen height
             *
             * @return int
             */
            int getScreenHeight() const;

            /**
             * @brief Shows cursor
             *
             */
            void showCursor();
            /**
             * @brief Hides cursor
             *
             */
            void hideCursor();
            /**
             * @brief Check if cursor is not visible
             *
             * @return true
             * @return false
             */
            bool isCursorHidden() const;

            /**
             * @brief Enables cursor (unlock cursor)
             *
             */
            void enableCursor();
            /**
             * @brief Disables cursor (lock cursor)
             *
             */
            void disableCursor();

            /**
             * @brief Check if cursor is enabled
             *
             * @return true
             * @return false
             */
            bool isCursorOnScreen() const;

            /**
             * @brief Set target FPS (maximum)
             *
             * @param x
             * @param y
             */
            void setTargetFPS(int fps);
            /**
             * @brief Get current FPS
             *
             * @return int
             */
            int getFPS() const;

            /**
             * @brief Get time in seconds for last frame drawn (delta time)
             *
             * @param x
             * @param y
             */
            float getFrameTime() const;

            /**
             * @brief Get elapsed time in seconds since InitWindow()
             *
             * @return double
             */
            double getTime() const;

        protected:
        private:
    };
}

#endif /* !WINDOW_HPP_ */
