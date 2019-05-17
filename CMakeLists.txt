cmake_minimum_required(VERSION 3.13)
project(zboss C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${zboss_SOURCE_DIR}/cmake)

SET(CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG_")
SET(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_gfx REQUIRED)

# include_directories(${SDL2_INCLUDE_DIR})

#include(ExternalProject)
#
#ExternalProject_Add (
#        nanogui
#        SOURCE_DIR "${zboss_SOURCE_DIR}/nanogui/"
#        # GIT_REPOSITORY "<git_repo_url>"
#        # GIT_TAG "<git_tag_commit_or_branch>"
#        #UPDATE_COMMAND ""
#        #INSTALL_COMMAND ""
#)

set(ZBOSS_HEADERS
        include/zboss/engine.hpp
        include/zboss/exceptions.hpp
        include/zboss/scene.hpp
        include/zboss/config.hpp
        include/zboss/entity/entity.hpp
        include/zboss/entity/component.hpp
        include/zboss/entity/manager.hpp
        include/zboss/math/matrix.hpp
        include/zboss/math/vector.hpp
        include/zboss/components/container.hpp
        include/zboss/assets/manager.hpp
        include/zboss/assets/locator.hpp
        include/zboss/assets/loader.hpp
        include/zboss/assets/cache.hpp
        include/zboss/assets/asset.hpp
        include/zboss/assets/loaders/font.hpp
        include/zboss/assets/loaders/texture.hpp
        include/zboss/assets/locators/file.hpp
        include/zboss/components/sprite.hpp
        include/zboss/renderer.hpp
        include/zboss/math/shape.hpp
        include/zboss/components/movement.hpp
        include/zboss/zboss.hpp
        include/zboss/tilemap/tileset.hpp
        include/zboss/tilemap/layers/tilelayer.hpp
        include/zboss/tilemap/tilemap.hpp
        include/zboss/assets/loaders/tilemap.hpp
        include/zboss/components/tilemap.hpp
        include/zboss/tilemap/layers/layer.hpp
        include/zboss/components/transform.hpp
        include/zboss/components/animatedsprite.hpp
        include/zboss/components/camerafollow.hpp
        include/zboss/callback.hpp
        include/zboss/components/life.hpp
        include/zboss/math/collision.hpp include/zboss/components/ui/label.hpp include/zboss/components/click.hpp include/zboss/components/ui/textfield.hpp)

set(ZBOSS_SOURCES
        src/engine.cpp
        src/entity/entity.cpp
        src/entity/manager.cpp
        src/math/vector.cpp
        src/components/container.cpp
        src/assets/asset.cpp
        src/assets/manager.cpp
        src/assets/loaders/font.cpp
        src/assets/loaders/texture.cpp
        src/assets/locators/file.cpp
        src/components/sprite.cpp
        src/math/shape.cpp
        src/renderer.cpp
        src/components/movement.cpp
        src/entity/component.cpp
        src/tilemap/tileset.cpp
        src/tilemap/layers/tilelayer.cpp
        src/tilemap/tilemap.cpp
        src/assets/loaders/tilemap.cpp
        src/components/tilemap.cpp
        src/scene.cpp
        src/tilemap/layers/layer.cpp
        src/components/transform.cpp
        src/components/animatedsprite.cpp
        src/components/camerafollow.cpp
        src/components/life.cpp
        src/math/collision.cpp src/components/ui/label.cpp src/components/click.cpp src/components/ui/textfield.cpp)

set(ZBOSS_RI_SOURCES
    ri/main.cpp
    ri/game.cpp
    ri/game.hpp
    ri/scenes/mainscene.hpp
    ri/components/movementcontroller.hpp
    ri/components/movementcontroller.cpp
    ri/scenes/mainscene.cpp
    ri/components/mytilemap.hpp
    ri/components/mytilemap.hpp
    ri/components/mytilemap.cpp
    ri/components/mapcamerafollow.cpp
    ri/components/mapcamerafollow.hpp
    ri/components/hpbar.cpp
    ri/components/hpbar.hpp
    ri/components/bossai.cpp
    ri/components/bossai.hpp
    ri/components/simplemapcollider.cpp
    ri/components/simplemapcollider.hpp
    ri/components/entitycollider.cpp
    ri/components/entitycollider.hpp
        ri/scenes/menuscene.cpp
        ri/scenes/menuscene.hpp
         ri/scenes/splashscene.cpp ri/scenes/splashscene.hpp ri/scenes/gamerules.cpp ri/scenes/gamerules.hpp ri/scenes/changeplayer.cpp ri/scenes/changeplayer.hpp)

add_library(zboss SHARED ${ZBOSS_HEADERS} ${ZBOSS_SOURCES})

target_include_directories(
    zboss
    PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_GFX_INCLUDE_DIRS}
    # $<BUILD_INTERFACE:${zboss_SOURCE_DIR}/include>
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    zboss
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_GFX_LIBRARIES}
)

target_compile_definitions(zboss PUBLIC SDL_MAIN_HANDLED)

configure_file(
    ${zboss_SOURCE_DIR}/binconfig.hpp
    ${zboss_BINARY_DIR}/binconfig.hpp
)

set_target_properties(zboss PROPERTIES LINKER_LANGUAGE CXX)

# Reference implementation executable

add_executable(zbossri ${ZBOSS_RI_SOURCES})

target_include_directories(
    zbossri
    PUBLIC
    ${zboss_BINARY_DIR}
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${zboss_SOURCE_DIR}/include>
)

#target_link_libraries(zboss ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)
target_link_libraries(zbossri zboss)

install(
    TARGETS zboss
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY ${zboss_SOURCE_DIR}/include/zboss
    DESTINATION include
)