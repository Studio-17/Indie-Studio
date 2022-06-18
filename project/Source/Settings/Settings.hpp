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

enum class Action {
    Next,
    Previous,
    Right,
    Left,
    Up,
    Down
};
enum class PlayerAction {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Drop
};

enum MusicsEnum {
    Menu,
    PlayerSelectMenu,
    Game,
    EndGame
};

enum SoundsEnum {
    BombExplosion,
    BombDrop,
    Bonus
};

class Settings {
    public:
        Settings(nlohmann::json const &jsonData);
        ~Settings();

        std::shared_ptr<RayLib::Window> getWindow() const;
        std::shared_ptr<RayLib::Audio> getAudio() const;
        std::shared_ptr<RayLib::CinematicCamera> getCamera() const;
        void setActionPressed(std::map<Action, bool> const &actionPressed);
        void setPlayerActionsPressed(std::vector<std::map<PlayerAction, bool>> const &playerAction);
        std::map<Action, bool> getActionPressed() const;
        std::vector<std::map<PlayerAction, bool>> getPlayerActionsPressed() const;

        void playMusic(const MusicsEnum &music);
        void updateMusicStream(const MusicsEnum &music);
        void stopMusic(const MusicsEnum &music);

        void playSound(const SoundsEnum &sound);
        void stopSound(const SoundsEnum &sound);

        void applySoundVolume(float volume);
        void applyMusicVolume(float volume);

        float getSoundVolume() const;
        float getMusicVolume() const;

        void applyFramerate(int framerate);

        int getFramerate() const;

        std::size_t getSaveIndex() const;
        void incrementSaveIndex();
        void resetSaveIndex();

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
        float _soundVolume; //!< Sound volume
        float _musicVolume; //!< Music volume
        std::size_t _saveIndex; //!< Save index
        int _framerate; //!< framerate max
};

#endif /* !SETTINGS_HPP_ */
