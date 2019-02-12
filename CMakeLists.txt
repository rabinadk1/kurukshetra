cmake_minimum_required(VERSION 3.13)
project(kurukshetra)

#project(SFMLTest)
#project(Thread)
#project(Networkingclient)
#project(Networkingserver)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic-errors")

add_executable(kurukshetra main.cpp Game.cpp Controller/remainTime.cpp Controller/remainTime.h)
#add_executable(SFMLTest main.cpp Animation.cpp)
#add_executable(Thread thread.cpp)

#add_executable(Networkingclient mainclient.cpp)
#add_executable(Networkingserver mainserver.cpp)

target_link_libraries(kurukshetra sfml-graphics sfml-window sfml-system)
#target_link_libraries(Thread pthread)
#target_link_libraries(Networkingclient sfml-network sfml-graphics sfml-window sfml-system)
#target_link_libraries(Networkingserver sfml-network sfml-graphics sfml-window sfml-system)
