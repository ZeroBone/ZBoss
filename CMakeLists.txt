cmake_minimum_required(VERSION 3.13)
project(zboss C CXX)

set(CMAKE_CXX_STANDARD 17)
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
    include/zboss/entity/constants.hpp include/zboss/components/container.hpp)

set(ZBOSS_SOURCES src/engine.cpp src/entity/entity.cpp src/entity/manager.cpp src/math/vector.cpp src/components/container.cpp)

set(ZBOSS_RI_SOURCES
    ri/main.cpp
    ri/game.cpp
    ri/game.hpp
    ri/scenes/mainscene.hpp)

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