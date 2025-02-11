cmake_minimum_required(VERSION 3.18)

project(ImagePrinter)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SRC_LIST src/*.cpp)

# ImageMagick
find_package(ImageMagick REQUIRED COMPONENTS Magick++)
if(ImageMagick_VERSION_STRING VERSION_LESS "7.0.0")
    add_compile_definitions(IMAGEMAGICK_VERSION=6)
else()
    add_compile_definitions(IMAGEMAGICK_VERSION=7)
endif()

# xtermcontrol
find_program(XTERMCONTROL_EXECUTABLE xtermcontrol)
if (XTERMCONTROL_EXECUTABLE)
    message(STATUS "xtermcontrol found: ${XTERMCONTROL_EXECUTABLE}")
else()
    message(WARNING "xtermcontrol not found, please install it for alpha-channel support")
endif()

# Main executable
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${ImageMagick_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${ImageMagick_LIBRARIES})

# ImageMagick config
target_compile_definitions(${PROJECT_NAME} PRIVATE MAGICKCORE_QUANTUM_DEPTH=16 MAGICKCORE_HDRI_ENABLE=0)
