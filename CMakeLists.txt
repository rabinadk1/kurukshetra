cmake_minimum_required(VERSION 3.13)
project(kurukshetra)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors -Weffc++")

add_executable(kurukshetra main.cpp Game.cpp Player.cpp TextureHolder.cpp Platform.cpp Animation.cpp Collider.cpp)
include_directories(kurukshetra includes)
target_link_libraries(kurukshetra sfml-graphics sfml-window sfml-system)
target_link_libraries(kurukshetra sfml-graphics sfml-window sfml-system)
