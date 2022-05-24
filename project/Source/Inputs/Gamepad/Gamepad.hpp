/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Gamepad
*/

#ifndef GAMEPAD_HPP_
    #define GAMEPAD_HPP_

    #include "raylib.h"
    #include <string>

class Gamepad {
    public:
        Gamepad() {};
        ~Gamepad() {};

        bool isAvailable(int gamepad);
        std::string getName(int gamepad);
        bool isButtonPressed(int gamepad, int button);
        bool isButtonDown(int gamepad, int button);
        bool isButtonReleased(int gamepad, int button);
        bool isButtonUp(int gamepad, int button);
        int getButtonPressed(void);
        int getAxisCount(int gamepad);
        float getAxisMovement(int gamepad, int axis);
        int setMappings(const char *mappings);


    protected:
    private:
};

#endif /* !GAMEPAD_HPP_ */
