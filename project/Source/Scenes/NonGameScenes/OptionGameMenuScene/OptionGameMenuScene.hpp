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

    #include <vector>
    #include <memory>
    #include <utility>

namespace Scene {

    class OptionGameMenuScene : public AScene {
        public:
            OptionGameMenuScene(std::shared_ptr<Settings> settings);
            ~OptionGameMenuScene();

            void fadeBlack() override;
            Scenes handelEvent() override;
            void draw() override;

        protected:
            void selectGameMenuScene();
            void selectMapScene();
            void leftClick(std::uint8_t index);
            void rightClick(std::uint8_t index);

        private:
            std::vector<std::pair<std::size_t, std::vector<std::unique_ptr<Object::Text>>>> _options;
    };
}

#endif /* !OPTIONGAMEMENUSCENE_HPP_ */
