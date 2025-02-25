project(ofdcpp-qt5 VERSION ${PROJECT_VERSION})

# Add GNUInstallDirs for installation paths
include(GNUInstallDirs)

find_package(Qt5 COMPONENTS Core Gui Xml REQUIRED)
find_package(QuaZip5 REQUIRED)

file(GLOB SOURCES 
    "*.cpp"
)

add_library(ofdcpp SHARED ${SOURCES})

target_include_directories(ofdcpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${QUAZIP_INCLUDE_DIRS}
)

target_link_libraries(ofdcpp
    PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Xml
        QuaZip5::QuaZip5
)

set_target_properties(ofdcpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
)

# Install library
install(TARGETS ofdcpp
    EXPORT ofdcppTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ofd
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install CMake targets
install(EXPORT ofdcppTargets
    FILE ofdcppTargets.cmake
    NAMESPACE ofdcpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ofdcpp
)

# Generate and install package configuration files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcppConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/ofdcppConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcppConfig.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ofdcppConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ofdcpp
) 