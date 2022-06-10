/*
** EPITECH PROJECT, 2022
** project
** File description:
** CreditsScene
*/

#ifndef CREDITSSCENE_HPP_
    #define CREDITSSCENE_HPP_

    #include "AScene.hpp"

namespace Scene {
    class CreditsScene : public AScene {
        public:
            CreditsScene(std::shared_ptr<Settings> settings);
            ~CreditsScene();

            Scenes handleEvent() override;
            void draw() override;

        protected:
        private:
            void back();
        private:
            std::vector<std::unique_ptr<Object::Image>> _parallax;

    };
}

#endif /* !CREDITSSCENE_HPP_ */
