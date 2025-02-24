cmake_minimum_required(VERSION 3.10.0)
project(popw VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(popw field.cpp main.cpp matrixc.cpp pop.cpp brain.cpp)
target_link_libraries( popw PUBLIC ${OpenCV_LIBS} )

# field.cpp main.cpp matrixc.cpp pop.cpps