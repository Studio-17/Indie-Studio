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

#include "Errors/Errors.hpp"

Test(Errors, errorsTest)
{
    Error::Errors error("This is an Error");

    assert(error.what() != NULL);
}

#include "Errors/ErrorsModules/Audio/AudioError.hpp"

Test(AudioError, audioerrorsTest)
{
    Error::AudioError audioError("This is an AudioError");

    assert(audioError.what() != NULL);
}

#include "Errors/ErrorsModules/File/FileError.hpp"

Test(FileError, fileerrorsTest)
{
    Error::FileError fileError("This is an FileError");

    assert(fileError.what() != NULL);
}

#include "Errors/ErrorsModules/Position/PositionError.hpp"

Test(PositionError, positionerrorsTest)
{
    Error::PositionError positionError("This is an PositionError");

    assert(positionError.what() != NULL);
}

#include "Errors/ErrorsModules/Window/WindowError.hpp"

Test(WindowError, windowerrorsTest)
{
    Error::WindowError windowError("This is an WindowError");

    assert(windowError.what() != NULL);
}
