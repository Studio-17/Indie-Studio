/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Test
*/

#include "raylib.h"

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "Tools/tools.hpp"

Test(Tools_CreateColor, toolsTest)
{
    std::array<float, 4> const &array = {40.5f, 50.66f, 10.0f, 0.0f};
    Color color = createColor(array);

    cr_assert_float_eq(color.r, 40.5, 40.5);
    cr_assert_float_eq(color.g, 50.66, 50.66);
    cr_assert_float_eq(color.b, 10.0, 10.5);
    cr_assert_float_eq(color.a, 0.0, 0.0);
}
