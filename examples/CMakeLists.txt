cmake_minimum_required(VERSION 3.10)
project(ofd_examples VERSION 0.1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置cmake模块路径
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

# 添加选项用于指定Qt版本
option(USE_QT6 "Use Qt6 instead of Qt5" OFF)

if(USE_QT6)
    find_package(Qt6 COMPONENTS Core Gui Xml Widgets REQUIRED)
    find_package(QuaZip-Qt6 REQUIRED)  # 修改为正确的包名
    set(QT_VERSION_MAJOR 6)
else()
    find_package(Qt5 COMPONENTS Core Gui Xml Widgets REQUIRED)
    find_package(QuaZip5 REQUIRED)
endif()

# 添加可执行文件
add_executable(simple_example simple_example.cpp)

# 添加包含路径
target_include_directories(simple_example
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# 设置链接
if(USE_QT6)
    target_link_libraries(simple_example
        PRIVATE
            ofdcpp6
            Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Gui
            Qt${QT_VERSION_MAJOR}::Xml
            Qt${QT_VERSION_MAJOR}::Widgets
    )
else()
    # Qt5 链接，使用原来正确的方式
    target_link_libraries(simple_example
        PRIVATE
            ofdcpp
            Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Gui
            Qt${QT_VERSION_MAJOR}::Xml
            Qt${QT_VERSION_MAJOR}::Widgets
    )
endif()
