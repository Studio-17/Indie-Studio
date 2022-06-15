/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectPlayerScene
*/

#ifndef SELECTPLAYERSCENE_HPP_
    #define SELECTPLAYERSCENE_HPP_

    #include "AScene.hpp"
    #include "GameSettings.hpp"

namespace Scene {
    /**
     * @brief Select Player Scene object to handle and display Option Select Player Scene
     */
    class SelectPlayerScene : public AScene {
        public:
            /**
             * @brief Construct a new Select Player Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param gameSettings Shared pointer to Game Settings class
             */
            SelectPlayerScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings);
            ~SelectPlayerScene();

            Scenes handleEvent() override;
            void draw() override;

        protected:
            void exitSelectPlayerScene();
            void runGame();
            void leftClick(std::uint8_t index);
            void rightClick(std::uint8_t index);

        private:
            std::shared_ptr<GameSettings> _gameSettings; //< Shared pointer to game Settings class
            std::vector<std::pair<std::size_t, std::vector<std::unique_ptr<Object::Image>>>> _players;

            std::vector<std::unique_ptr<Object::Image>> _parallax; //< Vector of every Images of the parallax
    };
}

#endif /* !SELECTPLAYERSCENE_HPP_ */
