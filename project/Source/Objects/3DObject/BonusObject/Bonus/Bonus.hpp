/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Bonus
*/

#ifndef BONUS_HPP_
#define BONUS_HPP_

#include <raylib.h>

#include <memory>
#include <map>

#include "AThreeDimensionObject.hpp"

namespace Object {
    enum class BONUS_OBJECTS {
        BOMB_DOWN = 1,
        BOMB_UP,
        FIRE_DOWN,
        FIRE_UP,
        SPEED_DOWN,
        SPEED_UP
    };

    /**
     * @brief Bonus class
     */
    class Bonus : public AThreeDimensionObject
    {
        public:
            /**
             * @brief Construct a new Bonus object
             *
             * @param pathToRessources pair of path to ressources texture and model
             * @param position 3 dimensional Position
             * @param bonusObject enum of bonus object
             * @param type map object type
             */
            Bonus(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::BONUS_OBJECTS bonusObject, Object::MAP_OBJECTS type);
            /**
             * @brief Destroy the Bonus object
             */
            ~Bonus() override;

            void draw() override;

            /**
             * @brief Get the Map Object object
             *
             * @return Object::BONUS_OBJECTS
             */
            Object::BONUS_OBJECTS getMapObject() { return _bonusObject; };

            /**
             * @brief Set the Block scale
             *
             * @param blockScale float block scale value
             */
            void setBlockScale(float blockScale) { _bonusScale = blockScale; };
            /**
             * @brief Get the Block scale
             *
             * @return float
             */
            float getBlockScale() { return _bonusScale; };

            /**
             * @brief Set the Bonus Object
             *
             * @param bonusObject enum BONUS_OBJECTS value
             */
            void setBonusObject(Object::BONUS_OBJECTS bonusObject) { _bonusObject = bonusObject; };

            /**
             * @brief Get the Status bonus
             *
             * @return true
             * @return false
             */
            bool getStatus() { return _status; };
            /**
             * @brief Set the Status object
             *
             * @param status bool _status value
             */
            void setStatus(bool status) { _status = status; };
            /**
             * @brief Set _status to true
             */
            void enable() { _status = true; };
            /**
             * @brief Set _status to false
             */
            void disable() { _status = false; };

        protected:
        private:
            std::string _type = "bonus"; ///< type of bonus

            Object::BONUS_OBJECTS _bonusObject; ///< enum of bonus object value

            bool _status = true; ///< status
            float _bonusScale; ///< scale
    };
}

#endif /* !BONUS_HPP_ */
