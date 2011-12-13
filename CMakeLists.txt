cmake_minimum_required(VERSION 2.6)
project(eyva)

#There are lots of scripts with cmake
#for finding external libraries. 
#see /usr/share/cmake-*/Modules/Find*.cmake
find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
add_subdirectory(src)
