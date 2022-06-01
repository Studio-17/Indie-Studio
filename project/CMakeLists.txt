cmake_minimum_required(VERSION 3.17)

# set the project name and version
project(IndieStudio VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include raylib into build
include(cmake-modules/Findraylib.cmake)

# include json into build
include(cmake-modules/Findjson.cmake)

# specify the sources
file(GLOB SOURCES
    Source/*.cpp

    Source/Audio/*.cpp
    Source/Audio/Music/*.cpp
    Source/Audio/Sound/*.cpp

    Source/Core/*.cpp

    Source/Datas/*.cpp
    Source/Datas/Position/*.cpp
    Source/Datas/Rendering/*.cpp

    Source/Errors/*.cpp
    Source/Errors/ErrorsModules/Audio/*.cpp
    Source/Errors/ErrorsModules/File/*.cpp
    Source/Errors/ErrorsModules/Position/*.cpp
    Source/Errors/ErrorsModules/Window/*.cpp

    Source/Inputs/*.cpp
    Source/Inputs/Gamepad/*.cpp
    Source/Inputs/Keyboard/*.cpp

    Source/Objects/*.cpp
    Source/Objects/2DObject/*.cpp
    Source/Objects/2DObject/Button/*.cpp
    Source/Objects/2DObject/Text/*.cpp
    Source/Objects/2DObject/Image/*.cpp
    Source/Objects/3DObject/*.cpp
    Source/Objects/3DObject/BombObject/Bomb/*.cpp
    Source/Objects/3DObject/BombObject/Explosion/*.cpp
    Source/Objects/3DObject/BonusObject/*.cpp
    Source/Objects/3DObject/BonusObject/Bonus/*.cpp
    Source/Objects/3DObject/BonusObject/Malus/*.cpp
    Source/Objects/3DObject/MapObject/*.cpp
    Source/Objects/3DObject/MapObject/Block/*.cpp
    Source/Objects/3DObject/MapObject/Map/*.cpp
    Source/Objects/3DObject/PlayerObject/*.cpp


    Source/Scenes/*.cpp
    Source/Scenes/GameScenes/*.cpp
    Source/Scenes/NonGameScenes/*.cpp
    Source/Scenes/NonGameScenes/MainMenu/*.cpp
    Source/Scenes/NonGameScenes/SettingsScene/*.cpp
    Source/Scenes/NonGameScenes/PopScenes/*.cpp
    Source/Scenes/NonGameScenes/SelectGameMenu/*.cpp

    Source/Settings/*.cpp
    Source/Settings/SettingsModules/*.cpp
    Source/Settings/SettingsModules/Audio/*.cpp
    Source/Settings/SettingsModules/Camera/*.cpp
    Source/Settings/SettingsModules/Window/*.cpp

    Source/Tools/*.cpp
)

# specify the headers
include_directories(
    Source/

    Source/Audio/
    Source/Audio/Music/
    Source/Audio/Sound/

    Source/Core/

    Source/Datas/
    Source/Datas/Position/
    Source/Datas/Rendering/

    Source/Errors/
    Source/Errors/ErrorsModules/Audio/
    Source/Errors/ErrorsModules/File/
    Source/Errors/ErrorsModules/Position/
    Source/Errors/ErrorsModules/Window/

    Source/Inputs/
    Source/Inputs/Gamepad/
    Source/Inputs/Keyboard/

    Source/Objects/
    Source/Objects/2DObject/
    Source/Objects/2DObject/Button/
    Source/Objects/2DObject/Text/
    Source/Objects/2DObject/Image/
    Source/Objects/3DObject/
    Source/Objects/3DObject/BombObject/Bomb/
    Source/Objects/3DObject/BombObject/Explosion/
    Source/Objects/3DObject/BonusObject/
    Source/Objects/3DObject/BonusObject/Bonus/
    Source/Objects/3DObject/BonusObject/Malus/
    Source/Objects/3DObject/MapObject/
    Source/Objects/3DObject/MapObject/Block/
    Source/Objects/3DObject/MapObject/Map/
    Source/Objects/3DObject/PlayerObject

    Source/Scenes/
    Source/Scenes/GameScenes/
    Source/Scenes/NonGameScenes/
    Source/Scenes/NonGameScenes/MainMenu/
    Source/Scenes/NonGameScenes/SettingsScene/
    Source/Scenes/NonGameScenes/PopScenes/
    Source/Scenes/NonGameScenes/SelectGameMenu/

    Source/Settings/
    Source/Settings/SettingsModules/
    Source/Settings/SettingsModules/Audio/
    Source/Settings/SettingsModules/Camera/
    Source/Settings/SettingsModules/Window/

    Source/Tools/
)

add_executable(IndieStudio ${SOURCES})

target_link_libraries(IndieStudio nlohmann_json::nlohmann_json)
target_link_libraries(IndieStudio raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

#include the Doxygen documentation
option(DOXYGEN "Generate Doxyegn documentation" OFF) #OFF by default
if(DOXYGEN)
    include(cmake-modules/Doxygen.cmake)
else()
    # Do nothing
endif(DOXYGEN)
unset(DOXYGEN CACHE) # Unset the cache variable