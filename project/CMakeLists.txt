cmake_minimum_required(VERSION 3.17)

# set the project name and version
project(IndieStudio VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include raylib into build
include(cmake-modules/Findraylib.cmake)

# specify the sources
file(GLOB SOURCES
    Source/*.cpp
    Source/Errors/Errors.cpp
    Source/Objects/*.cpp
    Source/Objects/UIOject/*.cpp
    Source/Objects/UIOject/Button/*.cpp
    Source/Objects/UIOject/Text/*.cpp
    Source/Core/*.cpp
    Source/Core/Settings/*.cpp
    Source/Core/Settings/SettingsModules/*.cpp
    Source/Core/Settings/SettingsModules/Audio/*.cpp
    Source/Core/Settings/SettingsModules/Camera/*.cpp
    Source/Core/Settings/SettingsModules/Window/*.cpp
    Source/Errors/ErrorsModules/*.cpp
    Source/Inputs/Keyboard/*.cpp
    Source/Inputs/Gamepad/*.cpp
    Source/Map/*.cpp
)

# specify the headers
include_directories(
    Source/
    Source/Errors/
    Source/Errors/ErrorsModules/
    Source/Objects/
    Source/Objects/UIOject/
    Source/Objects/UIOject/Button/
    Source/Objects/UIOject/Text/
    Source/Scenes/
    Source/Core/
    Source/Core/Settings/
    Source/Core/Settings/SettingsModules/
    Source/Core/Settings/SettingsModules/Audio/
    Source/Core/Settings/SettingsModules/Camera/
    Source/Core/Settings/SettingsModules/Window/
    Source/Errors/ErrorsModules/
    Source/Inputs/Keyboard/
    Source/Inputs/Gamepad/
    Source/Map/
)

add_executable(IndieStudio ${SOURCES} ${HEADERS})

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
