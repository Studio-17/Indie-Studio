/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** main
*/

#include <iostream>
#include <vector>

#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 20.0f, -10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 0.0f, 90.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Define the map used
    Image image = LoadImage("assets/maps/17x15.png");
    Texture2D cubicmap = LoadTextureFromImage(image);

    Mesh mesh = GenMeshCubicmap(image, (Vector3){ 1.0f, 1.0f, 1.0f });
    Model model = LoadModelFromMesh(mesh);

    Texture2D texture = LoadTexture("assets/cubicmap_atlas.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    // Get map image data to be used for collision detection
    Color *mapPixels = LoadImageColors(image);

    Vector3 mapPosition = { float(cubicmap.width / 2) * -1, 0.0f, float(cubicmap.height / 2) * -1 };

    // Define the Player position
    Vector3 playerPosition = { -5.0f, 0.5f, -5.0f };
    float playerRadius = 0.2f;

    // Vector3 enemyPosition = { 5.0f, 0.5f, 5.0f };


    UnloadImage(image);

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        Vector3 oldCamPos = { playerPosition.x, playerPosition.y, playerPosition.z };

        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);          // Update camera

        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_LEFT)) playerPosition.x += 0.08f;
        if (IsKeyDown(KEY_RIGHT)) playerPosition.x -= 0.08f;
        if (IsKeyDown(KEY_UP)) playerPosition.z += 0.08f;
        if (IsKeyDown(KEY_DOWN)) playerPosition.z -= 0.08f;

        // if (IsKeyDown(KEY_A)) enemyPosition.x += 0.08f;
        // if (IsKeyDown(KEY_D)) enemyPosition.x -= 0.08f;
        // if (IsKeyDown(KEY_S)) enemyPosition.z += 0.08f;
        // if (IsKeyDown(KEY_Z)) enemyPosition.z -= 0.08f;

        Vector2 playerPos = { playerPosition.x, playerPosition.z };

        // Out-of-limits security check
        for (int y = 0; y < cubicmap.height; y++)
        {
            for (int x = 0; x < cubicmap.width; x++)
            {
                if ((mapPixels[y*cubicmap.width + x].r == 255) &&       // Collision: white pixel, only check R channel
                    (CheckCollisionCircleRec(playerPos, playerRadius,
                    (Rectangle){ mapPosition.x - 0.5f + x*1.0f, mapPosition.z - 0.5f + y*1.0f, 1.0f, 1.0f })))
                {
                    // Collision detected, reset camera position
                    playerPosition = oldCamPos;
                }
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(DARKGRAY);

            BeginMode3D(camera);

                DrawLine3D((Vector3){-100, 0, 0}, (Vector3){100, 0, 0}, GREEN);     // X
                DrawLine3D((Vector3){0, -100, 0}, (Vector3){0, 100, 0}, RED);       // Y
                DrawLine3D((Vector3){0, 0, -100}, (Vector3){0, 0, 100}, DARKBLUE);  // Z

                DrawModel(model, mapPosition, 1.0f, WHITE);

                DrawCube(playerPosition, 0.5f, 0.5f, 0.5f, DARKBLUE);
                DrawCubeWires(playerPosition, 0.5f, 0.5f, 0.5f, DARKBROWN);

                // DrawCube(enemyPosition, 0.5f, 0.5f, 0.5f, RED);
                // DrawCubeWires(enemyPosition, 0.5f, 0.5f, 0.5f, MAROON);

            EndMode3D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    UnloadTexture(cubicmap);
    UnloadTexture(texture);
    UnloadModel(model);
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
