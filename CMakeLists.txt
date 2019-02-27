cmake_minimum_required(VERSION 3.13)
project(kurukshetra)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(kurukshetra main.cpp Server/src/GameClient.cpp Server/src/MainMenu.cpp Server/src/Game.cpp Server/src/Player.cpp Server/src/ResourceHolder.cpp Server/src/Platform.cpp Server/src/Camera.cpp Server/src/Animation.cpp Server/src/Collider.cpp Server/src/GameServer.cpp Server/src/Enemy.cpp Server/src/Bullet.cpp)
include_directories(kurukshetra includes)
target_link_libraries(kurukshetra sfml-graphics sfml-window sfml-network sfml-audio sfml-system)
