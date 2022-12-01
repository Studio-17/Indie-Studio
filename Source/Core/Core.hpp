/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <unordered_map>
    #include <memory>
    #include <utility>

    #include "IScene.hpp"
    #include "Settings.hpp"
    #include "Keyboard.hpp"
    #include "Gamepad.hpp"
    #include "GameSettings.hpp"
    #include "Image.hpp"
    #include "Text.hpp"

/**
 * @brief 
 * 
 */
class Core {
    public:
        /**
         * @brief Construct a new Core object
         */
        Core();
        /**
         * @brief Destroy the Core object
         */
        ~Core();

        /**
         * @brief Handle loading of the menu scenes
         */
        void loadMenuScenes();
        /**
         * @brief Core loop that handles the game loop
$         */
        void loop();

        /**
         * @brief Get the Event object, and handle response
$         */
        void getEvent();
        /**
         * @brief Bind the keyboard and gamepad events
         * 
         * @param player 
         * @param action 
         * @param Key 
         */
        void bindKey(int player, int action, int Key);

        /**
         * @brief Load keys bindings and apply them
         * 
         * @param jsonData 
         */
        void loadKeyBinding(nlohmann::json const &jsonData);

        /**
         * @brief Core function to handle the waiting sequence
         * 
         */
        void waitingLoad();

        /**
         * @brief Handle loading screen
         *
         * @param string
         */
        void updateLoadingScreen(std::string const &string);

    protected:
    private:
        std::shared_ptr<Settings> _settings; ///< Settings object
        std::shared_ptr<GameSettings> _gameSettings; ///< Game settings object
        bool _isRunning; ///< Is running
        std::unordered_map<Scene::Scenes, std::shared_ptr<Scene::IScene>> _menuScenes; ///< Menu scenes
        Scene::Scenes _activeScene; ///< Active scene
        Keyboard _keyboard; ///< Keyboard object
        Gamepad _gamepad; ///< Gamepad object

        std::map<Action, int> _actionPressed; ///< Action pressed
        std::vector<std::map<PlayerAction, int>> _playerActions; ///< Player actions
        std::vector<std::pair<PlayerAction, int>> _gamepadPlayerActions; ///< Gamepad player actions
        std::map<PlayerAction, int> _gamepadPlayerMovement; ///< Gamepad player movement

        std::vector<std::unique_ptr<Object::Image>> _images; ///< Images
        std::vector<std::unique_ptr<Object::Text>> _texts; ///< Texts

        std::vector<std::unique_ptr<Object::Image>> _parallax; ///< Vector of every Images of the parallax
};

#endif /* !CORE_HPP_ */
