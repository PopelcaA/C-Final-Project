cmake_minimum_required(VERSION 3.15)
project(hangman_modular)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB CORE_SRC
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(hangman_game
        ${CMAKE_SOURCE_DIR}/main_game.cpp
        ${CORE_SRC}
)

add_executable(hangman_admin
        ${CMAKE_SOURCE_DIR}/main_admin.cpp
        ${CORE_SRC}
)
