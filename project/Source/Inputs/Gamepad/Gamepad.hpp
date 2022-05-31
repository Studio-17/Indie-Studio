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
    #include <map>
        #include <iostream>

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
        template<typename ENUM>
        std::map<ENUM, bool> getKeysPressed(std::map<ENUM, int> map, int gamepad) const
        {
            std::map<ENUM, bool> actionPressed;
            for (auto &[action, key] : map)
                actionPressed.emplace(action, isButtonDown(gamepad, key));
            return actionPressed;
        };
        template<typename ENUM>
        std::map<ENUM, bool> getMovement(std::map<ENUM, int> map, int gamepad, std::pair<ENUM, int> const &drop) const
        {
            std::map<ENUM, bool> actionPressed;
            int index = 0;

            for (auto &[action, axis] : map) {
                bool isMoving = false;
                float value = getAxisMovement(gamepad, axis);
                if (index % 2 == 0) {
                    if (value < 0)
                        isMoving = true;
                } else {
                    if (value > 0)
                        isMoving = true;
                }
                actionPressed.emplace(action, isMoving);
                index++;
            }
            actionPressed.emplace(drop.first, isButtonDown(gamepad, drop.second));
            return actionPressed;
        };
    protected:
    private:
};

#endif /* !GAMEPAD_HPP_ */
