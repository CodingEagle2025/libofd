cmake_minimum_required(VERSION 3.10)
project(libofdcpp VERSION 0.1.0 LANGUAGES CXX)

# Build options
option(BUILD_EXAMPLES "Build example applications" OFF)
option(BUILD_TESTS "Build test applications" OFF)
option(BUILD_QT5 "Build Qt5 version" ON)
option(BUILD_QT6 "Build Qt6 version" ON)

# C++ standard settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
)

file(GLOB_RECURSE HEADERS 
    "include/ofd/*.h"
)

# 先构建主库
if(BUILD_QT5)
    add_subdirectory(src/qt5)
endif()

if(BUILD_QT6)
    add_subdirectory(src/qt6)
endif()

# 安装头文件
install(DIRECTORY include/ofd
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# 然后再构建示例
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
