cmake_minimum_required(VERSION 3.13)
project(zboss C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${zboss_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_gfx REQUIRED)

# include_directories(${SDL2_INCLUDE_DIR})

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
        include/zboss/entity/constants.hpp
        include/zboss/components/container.hpp
        include/zboss/assets/manager.hpp
        include/zboss/assets/locator.hpp
        include/zboss/assets/loader.hpp
        include/zboss/assets/cache.hpp
        include/zboss/assets/asset.hpp
        include/zboss/assets/loaders/audio.hpp
        include/zboss/assets/loaders/font.hpp
        include/zboss/assets/loaders/image.hpp
        include/zboss/assets/locators/file.hpp include/zboss/renderer.hpp include/zboss/math/shape.hpp include/zboss/components/movement.hpp)

set(ZBOSS_SOURCES
        src/engine.cpp
        src/entity/entity.cpp
        src/entity/manager.cpp
        src/math/vector.cpp
        src/components/container.cpp
        src/assets/asset.cpp
        src/assets/manager.cpp
        src/assets/loaders/audio.cpp
        src/assets/loaders/font.cpp
        src/assets/loaders/image.cpp
        src/assets/locators/file.cpp
        include/zboss/components/sprite.hpp
        src/components/sprite.cpp
        src/math/shape.cpp
        src/renderer.cpp
        src/entity/constants.cpp
        src/components/movement.cpp
        src/entity/component.cpp)

set(ZBOSS_RI_SOURCES
    ri/main.cpp
    ri/game.cpp
    ri/game.hpp
    ri/scenes/mainscene.hpp
    ri/components/movementcontroller.hpp
    ri/components/movementcontroller.cpp)

add_library(zboss SHARED ${ZBOSS_HEADERS} ${ZBOSS_SOURCES})

target_include_directories(
    zboss
    PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_GFX_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${zboss_SOURCE_DIR}/include>
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