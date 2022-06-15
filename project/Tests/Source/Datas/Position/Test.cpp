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
