cmake_minimum_required(VERSION 3.17)

# set the project name and version
project(IndieStudio VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")

# include raylib into build
include(cmake-modules/Findraylib.cmake)

# specify the sources
file(GLOB SOURCES
    Source/*.cpp
    Source/Errors/*.cpp
    Source/Core/*.cpp
    Source/Core/Settings/*.cpp
    Source/Core/Settings/SettingsModules/*.cpp
    Source/Core/Settings/SettingsModules/Audio/*.cpp
    Source/Core/Settings/SettingsModules/Camera/*.cpp
    Source/Core/Settings/SettingsModules/Window/*.cpp
)

# specify the headers
file(GLOB HEADERS
    Source/*.hpp
    Source/Errors/*.hpp
    Source/Objects/*.hpp
    Source/Scenes/*.hpp
    Source/Core/*.hpp
    Source/Core/Settings/*.hpp
    Source/Core/Settings/SettingsModules/*.hpp
    Source/Core/Settings/SettingsModules/Audio/*.hpp
    Source/Core/Settings/SettingsModules/Camera/*.hpp
    Source/Core/Settings/SettingsModules/Window/*.hpp
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
