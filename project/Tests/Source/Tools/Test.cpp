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

#include <unistd.h>
#include "Tools/clock.hpp"

Test(Tools_Clock, clockTest)
{
    Clock c;

    c.start();

    sleep(3);

    if (c.getElapsedTime() / 1000 < 3)
        assert(true);

    c.restart();

    if (c.getElapsedTime() / 1000 < 1)
        assert(true);
}

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

Test(Tools_Json, jsonTest)
{
    nlohmann::json data;

    try {
        data = getJsonData("Tests/Save/Games/gameSave.json");
    } catch ( ... ) {
        assert(false);
    }
}

Test(Tools_File, fileTest)
{
    try {
        readFile("Tests/Save/Games/gameSave.json", "\n");
    } catch ( ... ) {
        assert(false);
    }
}

Test(Tools_Rectangle, rectangleTest)
{
    Rectangle r;
    std::array<float, 4> const array = {
        0.1f,
        0.1f,
        0.1f,
        0.1f
    };

    r = setRectangle(array);

    if (r.height != 0.1f)
        assert(false);
}

Test(Tools_strToWordArray, strtokTest)
{
    std::vector<std::string> array;
    std::string line = "Hello World";

    array = strToWordArr(line, ' ');

    if (array.at(0) != "Hello")
        assert(false);
}
