/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
    #define SETTINGS_HPP_

    #include <nlohmann/json.hpp>

    #include <memory>
    #include <map>
    #include <utility>
    #include <vector>

    #include "Audio.hpp"
    #include "Camera.hpp"
    #include "Window.hpp"

    #include "Music.hpp"
    #include "MySound.hpp"

/**
 * @brief Enum class that defines the different actions
 *
 */
enum class Action {
    Next,
    Previous,
    Right,
    Left,
    Up,
    Down
};

/**
 * @brief Enum class that defines the different types of player actions
 *
 */
enum class PlayerAction {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Drop
};

/**
 * @brief Enum class that defines the different types of musics
 *
 */
enum MusicsEnum {
    Menu,
    PlayerSelectMenu,
    Game,
    EndGame
};

/**
 * @brief Enum class that defines the different types of sounds
 *
 */
enum SoundsEnum {
    BombExplosion,
    BombDrop,
    Bonus
};

/**
 * @brief Settings class that handles all game settings and parameters
 *
 */
class Settings {
    public:
        /**
         * @brief Construct a new Settings object
         *
         * @param jsonData
         */
        Settings(nlohmann::json const &jsonData);

        /**
         * @brief Destroy the Settings object
         *
         */
        ~Settings();

        /**
         * @brief Get the Window object
         *
         * @return std::shared_ptr<RayLib::Window>
         */
        std::shared_ptr<RayLib::Window> getWindow() const;
        /**
         * @brief Get the Audio object
         *
         * @return std::shared_ptr<RayLib::Audio>
         */
        std::shared_ptr<RayLib::Audio> getAudio() const;
        /**
         * @brief Get the Camera object
         *
         * @return std::shared_ptr<RayLib::CinematicCamera>
         */
        std::shared_ptr<RayLib::CinematicCamera> getCamera() const;
        /**
         * @brief Set the Action Pressed object
         *
         * @param actionPressed
         */
        void setActionPressed(std::map<Action, bool> const &actionPressed);
        /**
         * @brief Set the Player Actions Pressed object
         *
         * @param playerAction
         */
        void setPlayerActionsPressed(std::vector<std::map<PlayerAction, bool>> const &playerAction);
        /**
         * @brief Get the Action Pressed object
         *
         * @return std::map<Action, bool>
         */
        std::map<Action, bool> getActionPressed() const;
        /**
         * @brief Get the Player Actions Pressed object
         *
         * @return std::vector<std::map<PlayerAction, bool>>
         */
        std::vector<std::map<PlayerAction, bool>> getPlayerActionsPressed() const;

        /**
         * @brief Play the Music object
         *
         * @param music
         */
        void playMusic(const MusicsEnum &music);
        /**
         * @brief Update the Music object
         *
         * @param music
         */
        void updateMusicStream(const MusicsEnum &music);
        /**
         * @brief Stop the Music object
         *
         * @param music
         */
        void stopMusic(const MusicsEnum &music);

        /**
         * @brief Play the Sound object
         *
         * @param sound
         */
        void playSound(const SoundsEnum &sound);
        /**
         * @brief Stop the Sound object
         *
         * @param sound
         */
        void stopSound(const SoundsEnum &sound);

        /**
         * @brief Apply the sound effects volume
         *
         * @param volume
         */
        void applySoundVolume(float volume);
        /**
         * @brief Apply the music volume
         *
         * @param volume
         */
        void applyMusicVolume(float volume);

        /**
         * @brief Apply the selected framerates
         *
         * @param framerate
         */
        void applyFramerate(int framerate);

        /**
         * @brief Get the Framerate object
         *
         * @return int
         */
        int getFramerate() const;

        /**
         * @brief Get the Save Index object
         *
         * @return std::size_t
         */
        std::size_t getSaveIndex() const;
        /**
         * @brief Increment the save index value
         *
         */
        void incrementSaveIndex();
        /**
         * @brief Reset the save index value
         *
         */
        void resetSaveIndex();

        /**
         * @brief Update the settings object datas
         *
         * @param filepath
         */
        void updateSettingsDatas(std::string const &filepath);

    protected:
    private:
        std::shared_ptr<RayLib::Window> _window; //!< Window object
        std::shared_ptr<RayLib::Audio> _audio; //!< Audio object
        std::shared_ptr<RayLib::CinematicCamera> _camera; //!< Camera object

        std::vector<std::unique_ptr<MyMusic>> _musics; //!< Musics object
        std::vector<std::unique_ptr<MySound>> _sounds; //!< Sounds object

        std::map<Action, bool> _actionPressed; //!< Action pressed
        std::vector<std::map<PlayerAction, bool>> _playerActions; //!< Player actions pressed
        std::map<PlayerAction, bool> _playerAction; //!< Player action pressed
        std::size_t _saveIndex; //!< Save index
        int _framerate; //!< framerate max
};

#endif /* !SETTINGS_HPP_ */
