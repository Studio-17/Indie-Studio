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

#include <unistd.h>
#include "Tools/tools.hpp"
#include "Settings/Settings.hpp"
#include "Settings/GameSettings/GameSettings.hpp"
#include "Settings/SettingsModules/Audio/Audio.hpp"
#include "Settings/SettingsModules/Camera/Camera.hpp"
#include "Settings/SettingsModules/Window/Window.hpp"

Test(Settings, settingsTest)
{
    nlohmann::json jsonData = getJsonData("Tests/Conf/Settings/settings.json");
    Settings settings(jsonData);

    if (settings.getWindow() == nullptr || settings.getAudio() == nullptr
    || settings.getCamera() == nullptr || settings.getCamera() == nullptr)
        assert(false);

    assert(true);
}
