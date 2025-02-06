cmake_minimum_required(VERSION 3.30)

project(ImagePrinter)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SRC_LIST src/*.cpp)

# ImageMagick
find_package(ImageMagick REQUIRED COMPONENTS Magick++)
set(MAGICKCORE_QUANTUM_DEPTH 16)
set(MAGICKCORE_HDRI_ENABLE OFF)

# Main executable
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${ImageMagick_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${ImageMagick_LIBRARIES})