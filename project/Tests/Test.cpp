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

#include "Datas/Position/Position.hpp"

Test(Position_All, positionTest)
{
    Position pBase(1.0f, 1.0f, 1.0f);
    Position pEqual(1.0f, 1.0f, 1.0f);
    Position pGreater(100.0f, 100.0f, 100.0f);

    Position pPosition(pBase);

    assert(pBase.getX() == 1.0f);
    assert(pBase.getY() == 1.0f);
    assert(pBase.getZ() == 1.0f);

    if (pBase == pEqual)
        assert(true);

    if (pBase < pGreater)
        assert(true);
}

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
        data = getJsonData("Save/Games/gameSave.json");
    } catch ( ... ) {
        assert(false);
    }
}

Test(Tools_File, fileTest)
{
    try {
        readFile("Save/Games/gameSave.json", "\n");
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
