cmake_minimum_required(VERSION 3.8)
 
set(PROJECT snake)
set(SOURCES ../src/main.cpp ../src/functions_of_game.cpp)
 
project(${PROJECT})
include_directories(../include)
 
find_package (SFML REQUIRED window graphics audio)
 
add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} PRIVATE sfml-audio sfml-graphics sfml-network sfml-system)
