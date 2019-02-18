cmake_minimum_required(VERSION 3.13)
project(kurukshetra)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors -Weffc++")

add_executable(kurukshetra main.cpp src/Game.cpp src/Player.cpp src/TextureHolder.cpp src/Platform.cpp src/Animation.cpp src/Collider.cpp src/MainMenu.cpp)
include_directories(kurukshetra includes)
target_link_libraries(kurukshetra sfml-graphics sfml-window sfml-system)
target_link_libraries(kurukshetra sfml-graphics sfml-window sfml-system)
