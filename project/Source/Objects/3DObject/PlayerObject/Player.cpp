/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#include "Player.hpp"

Object::Player::Player(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position) : AThreeDimensionObject(pathToRessources, pathToAnimation, nbAnimation, position)
{
}

Object::Player::~Player()
{
    // UnloadTexture(_texture);
    // UnloadModel(_model);
    // for (unsigned int i = 0; i < _animsCount; i++) UnloadModelAnimation(_anims[i]);
}

void Object::Player::moveUp()
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount) _animFrameCounter = 0;

    Position newPosition(_position.getX(), _position.getY(), _position.getZ() + 0.2f);
    setPosition(newPosition);
}

void Object::Player::moveDown()
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount) _animFrameCounter = 0;

    Position newPosition(_position.getX(), _position.getY(), _position.getZ() - 0.2f);
    setPosition(newPosition);
}

void Object::Player::moveRight()
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount) _animFrameCounter = 0;

    Position newPosition(_position.getX() - 0.2f, _position.getY(), _position.getZ());
    setPosition(newPosition);
}

void Object::Player::moveLeft()
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    if (_animFrameCounter >= _anims[0].frameCount) _animFrameCounter = 0;

    Position newPosition(_position.getX() + 0.2f, _position.getY(), _position.getZ());
    setPosition(newPosition);
}

void Object::Player::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };

    DrawModelEx(_model, modelPosition, (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1*_scale, 1*_scale, 1*_scale }, WHITE);
    DrawModelWires(_model, modelPosition, 8, GREEN);
}

/*
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

        Vector3 oldCamPos = { playerPosition.x, playerPosition.y, playerPosition.z };
        Vector2 playerPos = { playerPosition.x, playerPosition.z };

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
*/