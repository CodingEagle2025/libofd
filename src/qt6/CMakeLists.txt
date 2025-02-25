project(ofdcpp-qt6 VERSION ${PROJECT_VERSION})

# Add GNUInstallDirs for installation paths
include(GNUInstallDirs)

find_package(Qt6 COMPONENTS Core Gui Xml REQUIRED)

# 使用 pkg-config 查找 QuaZip
find_package(PkgConfig REQUIRED)
pkg_check_modules(QUAZIP REQUIRED quazip1-qt6)

message(STATUS "QuaZip Include Dirs: ${QUAZIP_INCLUDE_DIRS}")
message(STATUS "QuaZip Libraries: ${QUAZIP_LIBRARIES}")

file(GLOB SOURCES 
    "*.cpp"
)

add_library(ofdcpp6 SHARED ${SOURCES})

target_include_directories(ofdcpp6
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${QUAZIP_INCLUDE_DIRS}
)

target_link_libraries(ofdcpp6
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Xml
        ${QUAZIP_LIBRARIES}
)

set_target_properties(ofdcpp6 PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    OUTPUT_NAME "ofdcpp6"
    DEFINE_SYMBOL "OFDCPP_QT6"
)

target_compile_definitions(ofdcpp6
    PRIVATE
        OFDCPP_QT6
)

install(TARGETS ofdcpp6
    EXPORT ofdcpp6Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT ofdcpp6Targets
    FILE ofdcpp6Targets.cmake
    NAMESPACE ofdcpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ofdcpp6
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcpp6ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/ofdcppConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcpp6Config.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcpp6Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcpp6ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ofdcpp6
)

# 生成并安装 pkg-config 文件
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/libofdcpp6.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/libofdcpp6.pc"
    @ONLY
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libofdcpp6.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
) 