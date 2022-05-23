/*
** EPITECH PROJECT, 2022
** B-EPI-000-PAR-0-0-projectname-user.email
** File description:
** main
*/

#include "raylib.h"
#include "Keyboard.hpp"
#include <iostream>

int main(void)
{
    Keyboard key;
    std::map<int, std::pair<int, bool>> map = {
        {0, {81, false}},
        {1, {'b', false}},
    };

    InitWindow(800, 450, "raylib [core] example - basic window");
    while (!WindowShouldClose())
    {
        map = key.getKeysPressed(map);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
