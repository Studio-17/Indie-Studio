/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Gamepad
*/

#ifndef GAMEPAD_HPP_
    #define GAMEPAD_HPP_

    #include <raylib.h>

    #include <string>

class Gamepad {
    public:
        Gamepad();
        ~Gamepad();

        bool isAvailable(int gamepad) const;
        std::string getName(int gamepad) const;
        bool isButtonPressed(int gamepad, int button) const;
        bool isButtonDown(int gamepad, int button) const;
        bool isButtonReleased(int gamepad, int button) const;
        bool isButtonUp(int gamepad, int button) const;
        int getButtonPressed() const;
        int getAxisCount(int gamepad) const;
        float getAxisMovement(int gamepad, int axis) const;
        int setMappings(const char *mappings);

    protected:
    private:
};

#endif /* !GAMEPAD_HPP_ */
