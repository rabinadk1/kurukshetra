cmake_minimum_required(VERSION 3.13)
project(kurukshetra)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors -Weffc++")

add_executable(kurukshetra main.cpp includes/Animation.cpp includes/Animation.h includes/Player.cpp includes/Player.h)
target_link_libraries(kurukshetra sfml-graphics sfml-window sfml-audio sfml-system)
