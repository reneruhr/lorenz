cmake_minimum_required(VERSION 3.20)
project(lorenz)

set(CMAKE_CXX_STANDARD 20)

#Adding kipod graphics engine
add_subdirectory(kipod)
include_directories(kipod/include)
include_directories(kipod/external_libs/)

add_executable(lorenz main.cpp src/lorenz.h src/runge_kutta.h)

#Linking kipod graphics engine
target_link_libraries(lorenz PUBLIC kipod)
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )