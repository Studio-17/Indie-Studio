cmake_minimum_required(VERSION 3.17)

# set the project name and version
project(IndieStudio VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include raylib into build
include(cmake/Findraylib.cmake)

# specify the sources
file(GLOB SOURCES
    Source/*.cpp
    Source/Errors/*.cpp
)

# specify the headers
file(GLOB HEADERS
    Source/*.hpp
    Source/Errors/*.hpp
)

add_executable(IndieStudio ${SOURCES} ${HEADERS})
