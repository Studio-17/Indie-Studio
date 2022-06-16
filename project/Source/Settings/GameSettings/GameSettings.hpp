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
    #include <utility>
    #include "Map.hpp"
    #include "Player.hpp"

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
         * @brief Update data game settings from a json file
         *
         * @param filePath std::string path to json file
         */
        void updateSettings(std::string const &filePath);

        /**
         * @brief Set the Map Path
         *
         * @param mapPath path to the .map map
         */
        void setMapPath(std::string const &mapPath);
        /**
         * @brief Set the Map Size
         *
         * @param mapSize std::pair with the new values of the map
         */
        void setMapSize(std::pair<float, float> mapSize);
        /**
         * @brief Set the percentage box drop
         *
         * @param percentage std::size_t new percentage box drop
         */
        void setPercentageBoxDrop(std::size_t percentage);
        /**
         * @brief Set the Player Skins vector
         *
         * @param playerSkins vector of player skins
         */
        void setPlayerSkins(std::vector<std::size_t> const &playerSkins);
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
         * @brief Get the Map Size
         *
         * @return std::pair map height and width size
         */
        std::pair<float, float> getMapSize() const;
        /**
         * @brief Get the Percentage Box Drop
         *
         * @return std::size_t percentage of box drop
         */
        std::size_t getPercentageBoxDrop() const;
        /**
         * @brief Get the Player Skins
         *
         * @return std::vector<std::string> vector of player skins
         */
        std::vector<std::size_t> getPlayerSkins() const;
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

        void setPlayersRank(std::map<std::size_t, Object::PLAYER_ORDER> playerRank) { _playersRank = playerRank; };
        std::map<std::size_t, Object::PLAYER_ORDER> getPlayersRank() { return _playersRank; };

        void setTimeOut(bool timeOut) { _timeOut = timeOut; };
        bool getTimeOut() { return _timeOut; };

    protected:
    private:
        std::string _mapPath; //!< path to the .map map
        std::pair<float, float> _mapSize; //!< size of the map
        std::size_t _percentageBoxDrop; //!< percentage of box drop
        std::vector<std::size_t> _playerSkins; //!< vector of player skins
        std::vector<bool> _iaPlayers; //!< vector of if a player is an IA
        std::size_t _nbPlayers; //!< number of player
        std::size_t _nbSets; //!< nb round
        float _gameTime; //!< game time
        bool _enableBonus; //!< if bonus are enabled
        std::map<std::size_t, Object::PLAYER_ORDER> _playersRank;
        bool _timeOut = false;

        // End game stats
        std::size_t victoriousPlayer;
        std::vector<float> _playersScore;
};

#endif /* !GAMESETTINGS_HPP_ */
