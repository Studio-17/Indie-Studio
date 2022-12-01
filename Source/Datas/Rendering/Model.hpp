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
        /**
         * @brief Class to handle generic loading of models objects
         *
         */
        class MyModel {
            public:
                /**
                 * @brief Construct a new My Model object
                 *
                 * @param pathToModel
                 */
                MyModel(std::string const &pathToModel) { _model = LoadModel(pathToModel.c_str()); };

                /**
                 * @brief Destroy the My Model object
                 *
                 */
                ~MyModel() {};

                /**
                 * @brief Get the Model object
                 *
                 * @return Model
                 */
                Model getModel() { return _model; };

                /**
                 * @brief RAII Unload model
                 *
                 */
                void unload() { UnloadModel(_model); };

            protected:
            private:
                Model _model; ///< The model object
        };
    }
}

#endif /* !MYMODEL_HPP_ */
