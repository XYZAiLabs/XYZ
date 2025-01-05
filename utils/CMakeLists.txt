# Utils CMake configuration
cmake_minimum_required(VERSION 3.12)

set(UTILS_SOURCES
    logging.cpp
    config_loader.cpp
)

set(UTILS_HEADERS
    logging.h
    config_loader.h
    constants.h
)

# Create utils library
add_library(xyz_utils STATIC ${UTILS_SOURCES} ${UTILS_HEADERS})

# Set library properties
set_target_properties(xyz_utils PROPERTIES
    OUTPUT_NAME "xyz_utils"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Include directories
target_include_directories(xyz_utils
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/xyz/utils>
)

# Compiler options
target_compile_options(xyz_utils PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:DEBUG>:-g -O0>
    $<$<CONFIG:RELEASE>:-O3>
)

# Installation
install(TARGETS xyz_utils
    EXPORT xyz_utils_targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES ${UTILS_HEADERS}
    DESTINATION include/xyz/utils
)

# Export targets
install(EXPORT xyz_utils_targets
    FILE XYZUtilsTargets.cmake
    NAMESPACE XYZ::
    DESTINATION lib/cmake/xyz_utils
)

# Generate and install package config
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/XYZUtilsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/XYZUtilsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/XYZUtilsConfig.cmake"
    INSTALL_DESTINATION lib/cmake/xyz_utils
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/XYZUtilsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/XYZUtilsConfigVersion.cmake"
    DESTINATION lib/cmake/xyz_utils
)