/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Test
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>

#include "Tools/clock.hpp"

Test(Tools_Clock, clockTest)
{
    Clock clock;

    clock.start();

    clock.getElapsedTime();

    cr_assert(false);
}
