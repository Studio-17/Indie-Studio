/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Test
*/

#include "raylib.h"

#include <assert.h>

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "Datas/Rendering/Animation.hpp"

Test(Rendering_Animations, renderingTest)
{
    Object::Render::MyAnimation animation("Tests/Ressources/player/player.iqm", 1);

    assert(animation.getAnimation() != NULL);

    animation.unload();
}

#include "Datas/Rendering/Model.hpp"

// Test(Rendering_Models, renderingTest)
// {
//     Object::Render::MyModel model("Tests/Ressources/block/dirt/box.obj");

//     model.unload();
// }

#include "Datas/Rendering/Texture.hpp"

// Test(Rendering_Texture, renderingTest)
// {
//     Object::Render::MyTexture texture("Tests/Ressources/block/dirt/box.png");

//     texture.unload();
// }
