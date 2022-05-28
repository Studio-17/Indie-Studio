/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** createColor
*/

#include <raylib.h>

#include <array>

Color createColor(std::array<float, 4> const &array)
{
    Color color;

    color.r = array.at(0);
    color.g = array.at(1);
    color.b = array.at(2);
    color.a = array.at(3);
    return color;
}
