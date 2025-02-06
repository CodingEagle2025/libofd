cmake_minimum_required(VERSION 3.10)
project(libofdcpp VERSION 0.1.0 LANGUAGES CXX)

# 设置编译选项
option(BUILD_EXAMPLES "Build example applications" OFF)
option(BUILD_TESTS "Build test applications" OFF)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 设置cmake模块路径
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# 查找依赖包 - 只包含实际使用的Qt模块
find_package(Qt5 COMPONENTS Core Gui Xml REQUIRED)  # 移除了 Widgets
# Suppress dev warnings for QuaZip5
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
set(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION OFF CACHE BOOL "" FORCE)
find_package(QuaZip5 REQUIRED)

# Fix linking issues
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed -ldl")


# Add source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
)

# Add header files
file(GLOB_RECURSE HEADERS 
    "include/ofd/*.h"
)

# Library target
add_library(ofdcpp SHARED ${SOURCES} ${HEADERS})
set_target_properties(ofdcpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    PUBLIC_HEADER "${HEADERS}"
)

target_include_directories(ofdcpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${QUAZIP_INCLUDE_DIRS}
)

target_link_libraries(ofdcpp
    PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Xml        # 移除了 Qt5::Widgets
        ${QUAZIP_LIBRARIES}
)

# Installation
include(GNUInstallDirs)
install(TARGETS ofdcpp
    EXPORT ofdcppTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ofd
)

install(DIRECTORY include/ofd
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Generate and install package configuration files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcppConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ofdcppConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcppConfig.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcppConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ofdcpp
)

install(EXPORT ofdcppTargets
    FILE ofdcppTargets.cmake
    NAMESPACE ofdcpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ofdcpp
)

# Optionally build examples and tests
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
