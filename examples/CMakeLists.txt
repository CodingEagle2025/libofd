cmake_minimum_required(VERSION 3.10)
project(ofd_examples VERSION 0.1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置cmake模块路径，使用与主项目相同的cmake模块
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

# 检查是否作为子项目
if(NOT TARGET ofdcpp)
    # 独立编译模式：查找已安装的ofdcpp库
    find_package(QuaZip5 REQUIRED)
    find_package(ofdcpp REQUIRED)
endif()

# 查找Qt依赖
find_package(Qt5 COMPONENTS Core Gui Xml Widgets REQUIRED)

# 添加可执行文件
add_executable(simple_example simple_example.cpp)

# 链接依赖库
target_link_libraries(simple_example
    PRIVATE
        ofdcpp::ofdcpp
        Qt5::Core
        Qt5::Gui
        Qt5::Xml
        Qt5::Widgets
) 