cmake_minimum_required(VERSION 3.28)

project(Floating_Kingdom)

include(FetchContent)

set(RAYLIB_VERSION 4.2.0)

# Uses the Internet to get Raylib

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

set(
SOURCE_FILES

    main.cpp
    utils.cpp
    App.cpp
    Game.cpp
    Classes/Sprite.cpp
    Classes/Slime.cpp
    Classes/Item.cpp 
    Classes/Player.cpp
    MusicManager/MusicManager.cpp
    LevelManager/LevelManager.cpp
    LevelManager/Tile.cpp
)

add_executable(Floating_Kingdom ${SOURCE_FILES})
target_link_libraries(Floating_Kingdom raylib)

if(WIN32)

    target_sources(Floating_Kingdom PRIVATE Assets/Windows/app.rc)
    target_link_options(Floating_Kingdom PRIVATE $<$<CONFIG:Release>:-mwindows>)
elseif(APPLE)

    target_link_options(Floating_Kingdom PRIVATE $<$<CONFIG:Release>:-MACOSX_BUNDLE>)
endif()

target_compile_definitions(Floating_Kingdom PUBLIC $<$<CONFIG:Debug>:DEBUG_ENABLED>)

if("${PLATFORM}" STREQUAL "Web")

    message(FATAL_ERROR "Do not build in this project in the Web as it doesn't work!")
endif()

if(APPLE)

    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()