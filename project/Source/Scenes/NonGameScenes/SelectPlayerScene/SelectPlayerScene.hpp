/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectPlayerScene
*/

#ifndef SELECTPLAYERSCENE_HPP_
    #define SELECTPLAYERSCENE_HPP_

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

    class SelectPlayerScene : public AScene {
        public:
            SelectPlayerScene(std::shared_ptr<Settings> settings, std::shared_ptr<GameSettings> gameSettings);
            ~SelectPlayerScene();

            void fadeBlack() override;
            Scenes handelEvent() override;
            void draw() override;

        protected:
            void exitSelectPlayerScene();
            void runGame();
            void leftClick(std::uint8_t index);
            void rightClick(std::uint8_t index);

        private:
            std::vector<std::pair<std::size_t, std::vector<std::unique_ptr<Object::Image>>>> _players;

            std::vector<std::unique_ptr<Object::Image>> _parallax;
    };
}

#endif /* !SELECTPLAYERSCENE_HPP_ */
