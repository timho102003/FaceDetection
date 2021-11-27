cmake_minimum_required(VERSION 3.7)
add_definitions(-std=c++17)
project(FaceDetection)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(FaceDetection ${project_SRCS})
target_link_libraries(FaceDetection ${OpenCV_LIBRARIES})