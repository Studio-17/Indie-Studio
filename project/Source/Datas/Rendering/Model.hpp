/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MyModel
*/

#ifndef MYMODEL_HPP_
#define MYMODEL_HPP_

#include <string>
#include <memory>

#include "raylib.h"

namespace Object {
    namespace Render {
        class MyModel {
            public:
                MyModel(std::string const &pathToModel) { _model = LoadModel(pathToModel.c_str()); };
                ~MyModel() { /* UnloadModel(_model) */ };

                Model getModel() { return _model; };

            protected:
            private:
                Model _model;
        };
    }
}

#endif /* !MYMODEL_HPP_ */
