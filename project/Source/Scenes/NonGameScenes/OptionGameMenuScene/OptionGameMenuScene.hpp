/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** OptionGameMenuScene
*/

#ifndef OPTIONGAMEMENUSCENE_HPP_
    #define OPTIONGAMEMENUSCENE_HPP_

    #include "AScene.hpp"
    #include "Music.hpp"
    #include "Image.hpp"
    #include "Button.hpp"
    #include "Text.hpp"
    #include "GameSettings.hpp"

    #include <vector>
    #include <memory>
    #include <utility>

namespace Scene {

    class OptionGameMenuScene : public AScene {
        public:
            OptionGameMenuScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings);
            ~OptionGameMenuScene();

            void fadeBlack() override;
            Scenes handleEvent() override;
            void draw() override;

        protected:
            void selectGameMenuScene();
            void selectMapScene();
            void leftClick(std::size_t index);
            void rightClick(std::size_t index);

        private:
            std::shared_ptr<GameSettings> _gameSettings;
            std::vector<std::pair<std::size_t, std::vector<std::unique_ptr<Object::Text>>>> _options;

            std::vector<std::unique_ptr<Object::Image>> _parallax;

            enum OPTION {
                NBPLAYERS = 0,
                NBSETS,
                GAMETIME,
                BONUS
            };
    };
}

#endif /* !OPTIONGAMEMENUSCENE_HPP_ */
