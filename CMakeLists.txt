cmake_minimum_required(VERSION 3.20)
project(lorenz)

set(CMAKE_CXX_STANDARD 20)

#Adding kipod graphics engine
add_subdirectory(kipod)
include_directories(kipod/include)
include_directories(kipod/external_libs/)
#BUG Kipod should find the following but it doesn't
set(SPDLOG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/kipod/external_libs/spdlog/include/)
include_directories(${SPDLOG_DIR})

add_executable(lorenz main.cpp src/lorenz_system.h src/runge_kutta.h src/lorenz.cpp src/lorenz.h src/lorenzmodule.cpp src/lorenzmodule.h)

#Linking kipod graphics engine
target_link_libraries(lorenz PUBLIC kipod)
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )