/*******************************************************************************************
*
*   raylib [core] example - Initialize 3d camera free
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <iostream>
#include <vector>

#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 20.0f, 00.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 100.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = { -30.0f, 0.0f, 30.0f };

    std::vector<Vector3> wallPositions = {
        (Vector3){ -30.0f, 0.0f, 0.0f },
        (Vector3){ -20.0f, 0.0f, 0.0f },
        (Vector3){ -10.0f, 0.0f, 0.0f },
        (Vector3){ 0.0f, 0.0f, 0.0f },
        (Vector3){ 10.0f, 0.0f, 0.0f },
        (Vector3){ 20.0f, 0.0f, 0.0f },
        (Vector3){ 30.0f, 0.0f, 0.0f },

        (Vector3){ -30.0f, 0.0f, -10.0f },
        (Vector3){ -20.0f, 0.0f, -10.0f },
        (Vector3){ -10.0f, 0.0f, -10.0f },
        (Vector3){ 0.0f, 0.0f, -10.0f },
        (Vector3){ 10.0f, 0.0f, -10.0f },
        (Vector3){ 20.0f, 0.0f, -10.0f },
        (Vector3){ 30.0f, 0.0f, -10.0f },

        (Vector3){ -30.0f, 0.0f, 10.0f },
        (Vector3){ -20.0f, 0.0f, 10.0f },
        (Vector3){ -10.0f, 0.0f, 10.0f },
        (Vector3){ 0.0f, 0.0f, 10.0f },
        (Vector3){ 20.0f, 0.0f, 10.0f },
        (Vector3){ 30.0f, 0.0f, 10.0f },
    };

    bool collision = false;

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);          // Update camera

        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) cubePosition.x += 0.25f;
        if (IsKeyDown(KEY_LEFT)) cubePosition.x -= 0.25f;
        if (IsKeyDown(KEY_DOWN)) cubePosition.z += 0.25f;
        if (IsKeyDown(KEY_UP)) cubePosition.z -= 0.25f;

        // Out-of-limits security check
        if (cubePosition.x < -30) cubePosition.x = -30;
        else if (cubePosition.x >= 30) cubePosition.x = 30;

        if (cubePosition.z < -20) cubePosition.z = -20;
        else if (cubePosition.z >= 20) cubePosition.z = 20 ;

        // Collision detection between boxes
        for (auto &wallPosition : wallPositions) {
            if (CheckCollisionRecs((Rectangle){ cubePosition.x, cubePosition.z, 2, 2 },
                                   (Rectangle){ wallPosition.x, wallPosition.z, 2, 2 }))
            {
                if (cubePosition.z <= wallPosition.z - 1 && (cubePosition.x < wallPosition.x + 2 && cubePosition.x > wallPosition.x - 2))
                    cubePosition.z -= cubePosition.z - (wallPosition.z - 2); // VERS LE BAS
                else if (cubePosition.z >= wallPosition.z + 1 && (cubePosition.x < wallPosition.x + 2 && cubePosition.x > wallPosition.x - 2))
                    cubePosition.z -= cubePosition.z - (wallPosition.z + 2); // VERS LE HAUT
                else if (cubePosition.x <= wallPosition.x)
                    cubePosition.x -= cubePosition.x - (wallPosition.x - 2); // VERS LA GAUCHE
                else if (cubePosition.x >= wallPosition.x)
                    cubePosition.x -= cubePosition.x - (wallPosition.x + 2); // VERS LA DROITE
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                for (auto &walls : wallPositions)
                    DrawCube(walls, 2.0f, 2.0f, 2.0f, BLACK);

                DrawGrid(80, 1.0f);

            EndMode3D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
