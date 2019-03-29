cmake_minimum_required(VERSION 3.13)
project(zboss)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${zboss_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

# include_directories(${SDL2_INCLUDE_DIR})

set(ZBOSS_HEADERS
    ${zboss_SOURCE_DIR}/include/zboss/zboss.hpp
    ${zboss_SOURCE_DIR}/include/zboss/zbengine.hpp
)

set(ZBOSS_SOURCES
    ${zboss_SOURCE_DIR}/src/zbengine.cpp
)

set(ZBOSS_RI_SOURCES
    ${zboss_SOURCE_DIR}/ri/main.cpp
)

add_library(zboss SHARED ${ZBOSS_HEADERS} ${ZBOSS_SOURCES})

target_include_directories(
    zboss
    PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${zboss_SOURCE_DIR}/include>
)

target_link_libraries(
    zboss
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

add_executable(zbossri ${ZBOSS_RI_SOURCES})

#target_link_libraries(zboss ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)
target_link_libraries(zbossri zboss)