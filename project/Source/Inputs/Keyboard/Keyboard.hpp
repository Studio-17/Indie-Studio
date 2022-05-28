/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Keyboard
*/

#ifndef KEYBOARD_HPP_
    #define KEYBOARD_HPP_

    #include <raylib.h>

    #include <utility>
    #include <map>

class Keyboard {
    public:
        Keyboard();
        ~Keyboard();

        bool hasBeenPressed(int key) const;
        bool isBeingPressed(int key) const;
        bool hasbeenReleased(int key) const;
        bool isNotBeingPressed(int key) const;
        void setExitKey(int key);
        int getPressedKeycode() const;
        int getPressedCharcode() const;
        std::map<int, std::pair<int, bool>> getKeysPressed(std::map<int, std::pair<int, bool>> map) const;

    protected:
    private:
};

#endif /* !KEYBOARD_HPP_ */
