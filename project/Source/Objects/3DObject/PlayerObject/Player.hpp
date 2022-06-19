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

    /**
     * @brief An enum for player order
     */
    enum class PLAYER_ORDER {
        PLAYER1 = 0,
        PLAYER2,
        PLAYER3,
        PLAYER4
    };

    /**
     * @brief Player class
     */
    class Player : public AThreeDimensionObject {
        public:
            /**
             * @brief Construct a new Player object
             *
             * @param pathToRessources pair of path to ressources texture and model
             * @param pathToAnimation path to ressource animation
             * @param nbAnimation number of animation
             * @param position 3 dimensional Position
             * @param type map object type
             */
            Player(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position, Object::MAP_OBJECTS type);
            /**
             * @brief Construct a new Player object
             *
             * @param pathToModel path to ressource model
             * @param pathToRessources path to ressource texture
             * @param pathToAnimation path to ressource animation
             * @param numberOfAnimations number of animation
             * @param position 3 dimensional Position
             * @param type map object type
             */
            Player(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToRessources, Object::Render::MyAnimation &pathToAnimation, unsigned int numberOfAnimations, Position const &position, Object::MAP_OBJECTS type);
            /**
             * @brief Construct a new Player object
             *
             * @param jsonData path to JSON file
             */
            Player(nlohmann::json const &jsonData);
            /**
             * @brief Destroy the Player object
             */
            ~Player() override;

            /**
             * @brief draw a three dimensional player object
             *
             */
            void draw() override;
            /**
             * @brief Player Animation
             *
             * @param animNb number of animation
             */
            void animation(std::size_t animNb);
            /**
             * @brief Move player
             *
             * @param position player position
             * @param direction new player position
             */
            void move(Position const &position, Position const &direction);

            /**
             * @brief Set life player
             */
            void die() { _isAlive = false; };
            /**
             * @brief Check if player is dead
             *
             * @return true
             * @return false
             */
            bool isAlive() { return _isAlive; };

            /**
             * @brief Get the default speed
             *
             * @return std::pair<float, float>
             */
            std::pair<float, float> getDefaultSpeed() const { return _defaultSpeed; };
            /**
             * @brief Set the Default Speed object
             *
             * @param defaultSpeed
             */
            void setDefaultSpeed(std::pair<float, float> const &defaultSpeed) { _defaultSpeed = defaultSpeed; };
            /**
             * @brief Get the default range Bomb object
             *
             * @return std::pair<std::size_t, std::size_t>
             */
            std::pair<std::size_t, std::size_t> getDefaultRangeBomb() const { return _defaultRangeBomb; };
            /**
             * @brief Set the Default Range Bomb object
             *
             * @param defaultRangeBomb
             */
            void setDefaultRangeBomb(std::pair<std::size_t, std::size_t> const &defaultRangeBomb) { _defaultRangeBomb = defaultRangeBomb; };
            /**
             * @brief Get the default range bomb explosion
             *
             * @return std::pair<std::size_t, std::size_t>
             */
            std::pair<std::size_t, std::size_t> getDefaultRangeExplosion() const { return _defaultRangeExplosion; };
            /**
             * @brief Set the Default Range Explosion object
             *
             * @param defaultRangeExplosion
             */
            void setDefaultRangeExplosion(std::pair<std::size_t, std::size_t> const &defaultRangeExplosion) { _defaultRangeExplosion = defaultRangeExplosion; };
            /**
             * @brief Get the default kick range
             *
             * @return std::size_t
             */
            std::pair<std::size_t, std::size_t> getDefaultKickRange() const { return _defaultKickRange; };
            /**
             * @brief Set the Default Kick Range object
             *
             * @param defaultKickRange
             */
            void setDefaultKickRange(std::pair<std::size_t, std::size_t> const &defaultKickRange) { _defaultKickRange = defaultKickRange; };

            /**
             * @brief Get player speed
             *
             * @return float
             */
            float getSpeed() const { return _speed; };
            /**
             * @brief Set player speed
             *
             * @param addSpeed add speed
             */
            void setSpeed(bool addSpeed);

            /**
             * @brief Get bomb range
             *
             * @return std::size_t
             */
            std::size_t getRangeBomb() const { return _rangeBomb; };
            /**
             * @brief Set bomb range
             *
             * @param addRangeBomb add bomb range
             */
            void setRangeBomb(bool addRangeBomb);

            /**
             * @brief Get explosion range
             *
             * @return std::size_t
             */
            std::size_t getRangeExplosion() const { return _rangeExplosion; };
            /**
             * @brief Set range explosion
             *
             * @param addrangeExplosion add range explosion
             */
            void setRangeExplosion(bool addrangeExplosion);

            /**
             * @brief Get number of bombes already placed
             *
             * @return std::size_t
             */
            std::size_t getAlreadyPlacedBombs() const { return _alreadyPlacedBombs; };
            /**
             * @brief Set number of bombes already placed
             *
             * @param addBomb add bomb to place
             */
            void setAlreadyPlacedBombs(bool addBomb);

            /**
             * @brief Get number of sets won
             *
             * @return std::size_t
             */
            std::size_t getSetsWon() const { return _setsWon; };
            void setWon(std::size_t nb);


            /**
             * @brief Get the Kick Range object
             *
             * @return std::size_t kickRange value
             */
            std::size_t getKickRange() const { return _kickRange; };
            /**
             * @brief Set the Kick Range object
             *
             * @param kickRange size_t kickRange value
             */
            void setKickRange(std::size_t kickRange) { _kickRange = kickRange; };

            /**
             * @brief Save player data in JSON file
             *
             * @return nlohmann::json
             */
            nlohmann::json save();

            /**
             * @brief Set the Skin object
             *
             * @param texture
             */
            void setSkin(Object::Render::MyTexture &texture);
            /**
             * @brief Reset player data
             */
            void reset();

        private:
            std::pair<float, float> _defaultSpeed = {0.5f, 0.8f};
            std::pair<std::size_t, std::size_t> _defaultRangeBomb = {1, 3};
            std::pair<std::size_t, std::size_t> _defaultRangeExplosion = {1, 4};
            std::pair<std::size_t, std::size_t> _defaultRangeSets = {1, 3};
            std::pair<std::size_t, std::size_t> _defaultKickRange = {1, 3}; ///< Default kick range

            float _speed;
            std::size_t _rangeBomb;
            std::size_t _rangeExplosion;
            std::size_t _kickRange;
            std::size_t _setsWon = 0;

            std::size_t _alreadyPlacedBombs;
            float _scale;
            int _life;
            bool _isAlive = true;
    };
}

#endif /* !PLAYER_HPP_ */
