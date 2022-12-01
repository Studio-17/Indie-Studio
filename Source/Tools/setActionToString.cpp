/*
** EPITECH PROJECT, 2022
** project
** File description:
** setActionToString
*/

#include <raylib.h>

#include <string>
#include <map>
#include <stdexcept>

static const std::map<int, std::string> keyToString {
    {KEY_A, "  a"},
    {KEY_B, "  b"},
    {KEY_C, "  c"},
    {KEY_D, "  d"},
    {KEY_E, "  e"},
    {KEY_F, "  f"},
    {KEY_G, "  g"},
    {KEY_H, "  h"},
    {KEY_I, "  i"},
    {KEY_J, "  j"},
    {KEY_K, "  k"},
    {KEY_L, "  l"},
    {KEY_M, "  m"},
    {KEY_N, "  n"},
    {KEY_O, "  o"},
    {KEY_P, "  p"},
    {KEY_Q, "  q"},
    {KEY_R, "  r"},
    {KEY_S, "  s"},
    {KEY_T, "  t"},
    {KEY_U, "  u"},
    {KEY_V, "  v"},
    {KEY_W, "  w"},
    {KEY_X, "  x"},
    {KEY_Y, "  y"},
    {KEY_Z, "  z"},
    {KEY_SPACE, "space"},
    {KEY_ENTER, "enter"},
    {KEY_BACKSPACE, "bckspc"},
    {KEY_COMMA, "  ,"},
    {KEY_SEMICOLON, "  ;"},
    {KEY_SLASH, "  :"},
    {KEY_LEFT, "l arr"},
    {KEY_RIGHT, "r arr"},
    {KEY_UP, "u arr"},
    {KEY_DOWN, "d arr"}
};

std::string setActionToString(int key)
{
    try {
        return keyToString.at(key);
    } catch (std::out_of_range const &e) {
        return std::to_string(key);
    }
}