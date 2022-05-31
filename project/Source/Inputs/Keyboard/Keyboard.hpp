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
        template<typename ENUM>
        std::map<ENUM, bool> getKeysPressed(std::map<ENUM, int> map) const
        {
            std::map<ENUM, bool> actionPressed;
            for (auto &[action, key] : map)
                actionPressed.emplace(action, isBeingPressed(key));
            return actionPressed;
        };
    protected:
    private:
};

#endif /* !KEYBOARD_HPP_ */
