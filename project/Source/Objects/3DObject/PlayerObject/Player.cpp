/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#include "Player.hpp"

Object::Player::Player(std::pair<std::string, std::string> const &pathToRessources, Position const &position) : AThreeDimensionObject(pathToRessources, position)
{
}

Object::Player::~Player()
{
}
