cmake_minimum_required(VERSION 3.17)
project(Voronoi)

set(CMAKE_CXX_STANDARD 17)

add_executable(Voronoi src/main.cpp src/A_BrutForce.cpp src/A_BrutForce.h src/B_AlgoSequentiel.cpp src/B_AlgoSequentiel.h src/C_Kmeans.cpp src/C_Kmeans.h src/D_AproxImgBrutForce.cpp src/D_AproxImgBrutForce.h src/E_AproxImgAdaptatif.cpp src/E_AproxImgAdaptatif.h)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Voronoi ${OpenCV_LIBS})
