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

/**
 * @brief Gamepad class that handles inputs from Xbox 360 Gamepads
 *
 */
class Gamepad {
    public:
        /**
         * @brief Construct a new Gamepad object
         *
         * @param id
         */
        Gamepad();

        /**
         * @brief Destroy the Gamepad object
         *
         */
        ~Gamepad();

        /**
         * @brief
         *
         * @param gamepad
         * @return true
         * @return false
         */
        bool isAvailable(int gamepad) const;
        /**
         * @brief Get the Name object
         *
         * @param gamepad
         * @return std::string
         */
        std::string getName(int gamepad) const;
        /**
         * @brief
         *
         * @param gamepad
         * @param button
         * @return true
         * @return false
         */
        bool isButtonPressed(int gamepad, int button) const;
        /**
         * @brief
         *
         * @param gamepad
         * @param button
         * @return true
         * @return false
         */
        bool isButtonDown(int gamepad, int button) const;
        /**
         * @brief
         *
         * @param gamepad
         * @param button
         * @return true
         * @return false
         */
        bool isButtonReleased(int gamepad, int button) const;
        /**
         * @brief
         *
         * @param gamepad
         * @param button
         * @return true
         * @return false
         */
        bool isButtonUp(int gamepad, int button) const;
        /**
         * @brief Get the Button Pressed object
         *
         * @return int
         */
        int getButtonPressed() const;
        /**
         * @brief Get the Axis Count object
         *
         * @param gamepad
         * @return int
         */
        int getAxisCount(int gamepad) const;
        /**
         * @brief Get the Axis Movement object
         *
         * @param gamepad
         * @param axis
         * @return float
         */
        float getAxisMovement(int gamepad, int axis) const;
        /**
         * @brief Set the Mappings object
         *
         * @param mappings
         * @return int
         */
        int setMappings(const char *mappings);
        /**
         * @brief Get the Keys Pressed object
         *
         * @tparam ENUM
         * @param map
         * @param gamepad
         * @return std::map<ENUM, bool>
         */
        template<typename ENUM>
        std::map<ENUM, bool> getKeysPressed(std::map<ENUM, int> map, int gamepad) const
        {
            std::map<ENUM, bool> actionPressed;
            for (auto &[action, key] : map)
                actionPressed.emplace(action, isButtonDown(gamepad, key));
            return actionPressed;
        };
        /**
         * @brief Get the Movement object
         *
         * @tparam ENUM
         * @param map
         * @param gamepad
         * @param drop
         * @return std::map<ENUM, bool>
         */
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
