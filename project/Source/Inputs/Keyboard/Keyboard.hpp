/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Keyboard
*/

#ifndef KEYBOARD_HPP_
    #define KEYBOARD_HPP_

    #include "raylib.h"
    #include <utility>
    #include <map>

class Keyboard {
    public:
        Keyboard() {};
        ~Keyboard() {};

        bool hasBeenPressed(int key);
        bool isBeingPressed(int key);
        bool hasbeenReleased(int key);
        bool isNotBeingPressed(int key);
        void setExitKey(int key);
        int getPressedKeycode(void);
        int getPressedCharcode(void);
        std::map<int, std::pair<int, bool>> getKeysPressed(std::map<int, std::pair<int, bool>> map);

    protected:
    private:
};

#endif /* !KEYBOARD_HPP_ */
