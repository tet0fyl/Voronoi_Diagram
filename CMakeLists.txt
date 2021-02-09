cmake_minimum_required(VERSION 3.17)
project(Voronoi)

set(CMAKE_CXX_STANDARD 17)

add_executable(Voronoi src/main.cpp src/A_BrutForceVoronoi.cpp src/A_BrutForceVoronoi.h)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Voronoi ${OpenCV_LIBS})
