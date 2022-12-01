/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** setRectangle
*/

#include <raylib.h>

#include <array>

Rectangle setRectangle(std::array<float, 4> const &array)
{
    Rectangle rect;

    rect.x = array.at(0);
    rect.y = array.at(1);
    rect.width = array.at(2);
    rect.height = array.at(3);
    return rect;
}
