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
        BOMB_MOVE,
        BOMB_UP,
        BOX_MOVE,
        DEATH_HEAD,
        EMPTY,
        FIRE_DOWN,
        FIRE_UP,
        HEARTH,
        ICE_GLOVE,
        KICK,
        P_BOMB,
        PEAKY_BOMB,
        PUNCH,
        RISE_UP,
        SPEED_DOWN,
        SPEED_UP,
        WATER_BOMB,
        WIZARD
    };

    class Bonus : public AThreeDimensionObject
    {
        public:
            Bonus(std::pair<std::string, std::string> const &pathToRessources, Position const &position, Object::BONUS_OBJECTS bonusObject);
            ~Bonus() override;

            void draw() override;

            Object::BONUS_OBJECTS getMapObject() const;

            void setBlockScale(float blockScale) { _bonusScale = blockScale; };
            float getBlockScale() { return _bonusScale; };

            void setBonusObject(Object::BONUS_OBJECTS bonusObject) { _bonusObject = bonusObject; };

            void setStatus(bool status) { _status = status; };
            void enable() { _status = true; };
            void disable() { _status = false; };
            bool getStatus() { return _status; };

        protected:
        private:
            std::string _type = "bonus";

            Object::BONUS_OBJECTS _bonusObject;

            bool _status = true;
            float _bonusScale;
    };
}

#endif /* !BONUS_HPP_ */
