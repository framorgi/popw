cmake_minimum_required(VERSION 3.10.0)

project(popw VERSION 1.0)

file(GLOB SOURCES_CPP_FILES "src/*.cpp")
file(GLOB SOURCES_CONFIG_CPP_FILES "src/config/*.cpp")


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
# Indica a CMake dove trovare Eigen
include_directories(/usr/include/eigen3)

# Add executable
add_executable(${PROJECT_NAME}  ${SOURCES_CPP_FILES} )

target_link_libraries( ${PROJECT_NAME} 
                        PUBLIC
                        ${OpenCV_LIBS} )

