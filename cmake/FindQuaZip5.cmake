# FindQuaZip5.cmake
find_package(Qt5 COMPONENTS Core REQUIRED)

find_path(QUAZIP_INCLUDE_DIR quazip.h
    PATHS /usr/include/quazip5
    PATH_SUFFIXES quazip
)

find_library(QUAZIP_LIBRARY
    NAMES quazip5 libquazip5
    PATHS /usr/lib /usr/lib64
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QuaZip5
    REQUIRED_VARS QUAZIP_LIBRARY QUAZIP_INCLUDE_DIR
)

if(QuaZip5_FOUND AND NOT TARGET QuaZip5::QuaZip5)
    set(QUAZIP_INCLUDE_DIRS ${QUAZIP_INCLUDE_DIR})
    set(QUAZIP_LIBRARIES ${QUAZIP_LIBRARY})
    
    add_library(QuaZip5::QuaZip5 UNKNOWN IMPORTED)
    set_target_properties(QuaZip5::QuaZip5 PROPERTIES
        IMPORTED_LOCATION "${QUAZIP_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${QUAZIP_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES Qt5::Core
    )
endif() 