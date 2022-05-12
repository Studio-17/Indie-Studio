/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #include <string>
    #include <utility>

namespace Raylib {
    class Window {
        public:
            Window(int width, int height, std::string const &title);
            ~Window();

            bool shouldClose() const;
            void setWindowSize(int width, int height);
            void setWindowSize(std::pair<int, int> const &size);
            std::pair<int, int> getWindowSize() const;

            void setFps(int fps);
            int getFps() const;

            void showCursor();
            void hideCursor();
            bool isCursorHidden() const;
            void enableCursor();
            void disableCursor();
            bool isCursorOnScreen() const;

        protected:
        private:

    };
}

#endif /* !WINDOW_HPP_ */
