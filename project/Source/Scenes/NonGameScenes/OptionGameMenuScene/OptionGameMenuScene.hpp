/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** OptionGameMenuScene
*/

#ifndef OPTIONGAMEMENUSCENE_HPP_
    #define OPTIONGAMEMENUSCENE_HPP_

    #include "AScene.hpp"
    #include "GameSettings.hpp"

namespace Scene {
    /**
     * @brief Option Game Menu Scene object to handle and display Option Game Menu Scene
     */
    class OptionGameMenuScene : public AScene {
        public:
            /**
             * @brief Construct a new Option Game Menu Scene object
             *
             * @param settings Shared pointer to Settings class
             * @param gameSettings Shared pointer to Game Settings class
             * @param parallax Vector of unique pointer of Object::Image class
             */
            OptionGameMenuScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings, std::vector<std::unique_ptr<Object::Image>> &parallax);
            /**
             * @brief Destroy the Option Game Menu Scene object
             */
            ~OptionGameMenuScene();

            /**
             * @brief Handle the event of the scene
             *
             * @return Scenes
             */
            Scenes handleEvent() override;
            /**
             * @brief Draw the scene
             */
            void draw() override;

            /**
             * @brief handle action
             */
            void handleAction();

        protected:
        private:
            /**
             * @brief Enum to define the type of option
             */
            enum OPTION {
                NBPLAYERS = 0,
                NBSETS,
                GAMETIME,
                BONUS
            };

            /**
             * @brief Call back function executed when back button is pressed to set next scene to start game scene
             */
            void back();
            /**
             * @brief Call back function executed when next button is pressed to set next scene to select map scene
             */
            void selectMapScene();
            /**
             * @brief Call back function executed when left button of an option is pressed to set option to the previous case
             *
             * @param index Option representing the button
             */
            void leftClick(OPTION index);
            /**
             * @brief Call back function executed when right button of an option is pressed to set option to the next case
             *
             * @param index Option representing the button
             */
            void rightClick(OPTION index);

            std::shared_ptr<GameSettings> _gameSettings; ///< Shared pointer to game Settings class
            std::vector<std::pair<std::size_t, std::vector<std::unique_ptr<Object::Text>>>> _options; ///< Vector of pair of with his Text

            std::vector<std::unique_ptr<Object::Image>> &_parallax; ///< Vector of every Images of the parallax
            std::vector<std::unique_ptr<Object::Button>> _emptyButton; ///< Vector of background unused Buttons
            std::size_t _activeButton; ///< Index of the active button
    };
}

#endif /* !OPTIONGAMEMENUSCENE_HPP_ */
