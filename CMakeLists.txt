cmake_minimum_required(VERSION 3.13)
project(kurukshetra)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors -Weffc++")

add_executable(kurukshetra main.cpp Server/src/MainMenu.cpp Server/src/Game.cpp Server/src/Player.cpp Server/src/ResourceHolder.cpp Server/src/Platform.cpp Server/src/Animation.cpp Server/src/Collider.cpp Server/src/GameServer.cpp Server/src/Enemy.cpp)
include_directories(kurukshetra includes)
target_link_libraries(kurukshetra sfml-network sfml-graphics sfml-window sfml-system)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")