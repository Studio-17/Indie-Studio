/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** GameSettings
*/

#ifndef GAMESETTINGS_HPP_
    #define GAMESETTINGS_HPP_

    #include <nlohmann/json.hpp>

    #include <string>
    #include <vector>

class GameSettings {
    public:
        /**
         * @brief Construct a new Game Settings object to default values
         */
        GameSettings();
        /**
         * @brief Destroy the Game Settings object
         */
        ~GameSettings();

        /**
         * @brief Load values of Game Settings object from nlohmann::json datas
         *
         * @param jsonData nlohmann::json datas containing all values
         */
        void loadFromJson(nlohmann::json const &jsonData);

        /**
         * @brief Set the Map Path
         *
         * @param mapPath path to the .map map
         */
        void setMapPath(std::string const &mapPath);
        /**
         * @brief Set the Player Skins vector
         *
         * @param playerSkins vector of player skins
         */
        void setPlayerSkins(std::vector<std::string> const &playerSkins);
        /**
         * @brief Set the IA Players vector
         *
         * @param iaPlayers vector of if player is an IA or not
         */
        void setIaPlayers(std::vector<bool> const &iaPlayers);
        /**
         * @brief Set the Nb Players
         *
         * @param nbPlayers number of player
         */
        void setNbPlayers(std::size_t nbPlayers);
        /**
         * @brief Set the Nb Sets
         *
         * @param nbSets number of set
         */
        void setNbSets(std::size_t nbSets);
        /**
         * @brief Set the Game Time
         *
         * @param gameTime game time
         */
        void setGameTime(float gameTime);
        /**
         * @brief set enable Bonus to true
         */
        void enableBonus();
        /**
         * @brief set enable Bonus to false
         */
        void disableBonus();

        /**
         * @brief Get the Map Path
         *
         * @return std::string map Path
         */
        std::string getMapPath() const;
        /**
         * @brief Get the Player Skins
         *
         * @return std::vector<std::string> vector of player skins
         */
        std::vector<std::string> getPlayerSkins() const;
        /**
         * @brief Get the IA Players
         *
         * @return std::vector<bool> vector of if player is an IA
         */
        std::vector<bool> getIaPlayers() const;
        /**
         * @brief Get the Nb Players
         *
         * @return std::size_t number of players
         */
        std::size_t getNbPlayers() const;
        /**
         * @brief Get the Nb Sets
         *
         * @return std::size_t number of sets
         */
        std::size_t getNbSets() const;
        /**
         * @brief Get the Game Time
         *
         * @return float game time
         */
        float getGameTime() const;
        /**
         * @brief get if bonus are enabled
         *
         * @return true bonus are enabled
         * @return false bonus are disabled
         */
        bool IsEnabledBonus() const;

    protected:
    private:
        std::string _mapPath; //!< path to the .map map
        std::vector<std::string> _playerSkins; //!< vector of player skins
        std::vector<bool> _iaPlayers; //!< vector of if a player is an IA
        std::size_t _nbPlayers; //!< number of player
        std::size_t _nbSets; //!< nb round
        float _gameTime; //!< game time
        bool _enableBonus; //!< if bonus are enabled
};

#endif /* !GAMESETTINGS_HPP_ */
