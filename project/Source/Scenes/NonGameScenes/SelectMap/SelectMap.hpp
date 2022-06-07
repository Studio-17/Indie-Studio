/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** SelectMap
*/

#ifndef SELECTMAP_HPP_
    #define SELECTMAP_HPP_

    #include "AScene.hpp"
    #include "Music.hpp"
    #include "Image.hpp"

namespace Scene {

    class SelectMap : public AScene {
        public:
            SelectMap(std::shared_ptr<Settings> settings);
            ~SelectMap();

            void fadeBlack() override;
            Scenes handelEvent() override;
            void draw() override;

        protected:
            void smallMap();
            void mediumMap();
            void bigMap();
        private:
    };
}

#endif /* !SELECTMAP_HPP_ */
