project(Scrambler)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(.. SRC_LIST)
add_definitions(-std=gnu++11)
add_definitions(-O2)
add_definitions(-static)
add_definitions(-lm -s -x c++ -Wl,--stack=268435456)
add_executable(${PROJECT_NAME} ${SRC_LIST})

