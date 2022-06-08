/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <utility>

    #include "AThreeDimensionObject.hpp"

namespace Object {

    enum class PLAYER_ORDER {
        PLAYER1 = 0,
        PLAYER2,
        PLAYER3,
        PLAYER4
    };

    class Player : public AThreeDimensionObject {
        public:
            Player(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position, Object::MAP_OBJECTS type);
            Player(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToRessources, Object::Render::MyAnimation &pathToAnimation, unsigned int numberOfAnimations, Position const &position, Object::MAP_OBJECTS type);

            Player(nlohmann::json const &jsonData);
            ~Player() override;

            void draw() override;
            void animation(std::size_t animNb);
            void move(Position const &position, Position const &direction);

            void dropBomb(Position const &postion, float timeBeforeExplosion, std::size_t range);
            void die() { _isAlive = false; };
            bool isAlive() { return _isAlive; };

            float getDefaultSpeed() const { return _defaultSpeed; };
            std::pair<std::size_t, std::size_t> getDefaultRangeBomb() const { return _defaultRangeBomb; };
            std::pair<std::size_t, std::size_t> getDefaultRangeExplosion() const { return _defaultRangeExplosion; };
            float getDefaultLifeTimeBombs() const { return _defaultLifeTimeBombs; };
            std::size_t getDefaultKickRange() const { return _defaultKickRange; };

            float getSpeed() const { return _speed; };
            void setSpeed(float speed) { _speed = speed; };

            std::size_t getRangeBomb() const { return _rangeBomb; };
            void setRangeBomb(std::size_t rangeBomb) { _rangeBomb = rangeBomb; };

            std::size_t getRangeExplosion() const { return _rangeExplosion; };
            void setRangeExplosion(std::size_t rangeExplosion) { _rangeExplosion = rangeExplosion; };

            float getLifeTimeBombs() const { return _lifeTimeBombs; };
            void setLifeTimeBombs(float lifeTimeBombs) { _lifeTimeBombs = lifeTimeBombs; };

            std::size_t getKickRange() const { return _kickRange; };
            void setKickRange(std::size_t kickRange) { _kickRange = kickRange; };

        private:

            float _defaultSpeed = 0.6f;
            std::pair<std::size_t, std::size_t> _defaultRangeBomb = {1, 3};
            std::pair<std::size_t, std::size_t> _defaultRangeExplosion = {1, 6};
            float _defaultLifeTimeBombs = 3;
            std::size_t _defaultKickRange = 1;

            float _speed;
            std::size_t _rangeBomb;
            std::size_t _rangeExplosion;
            float _lifeTimeBombs;
            std::size_t _kickRange;

            float _scale;
            int _life;
            bool _isAlive = true;

    };
}

#endif /* !PLAYER_HPP_ */
