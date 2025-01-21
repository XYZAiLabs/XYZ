# Root models CMake configuration
cmake_minimum_required(VERSION 3.12)

# Add source directory
add_subdirectory(src)

# Export package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/XYZModelsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/XYZModelsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/XYZModelsConfig.cmake"
    INSTALL_DESTINATION lib/cmake/xyz_models
)

# Installation
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/XYZModelsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/XYZModelsConfigVersion.cmake"
    DESTINATION lib/cmake/xyz_models
)

# Export targets
install(EXPORT xyz_models_targets
    FILE XYZModelsTargets.cmake
    NAMESPACE XYZ::
    DESTINATION lib/cmake/xyz_models
)

# Install headers
install(DIRECTORY include/
    DESTINATION include/xyz/models
    FILES_MATCHING PATTERN "*.h"
    PATTERN "internal" EXCLUDE
)

# Add tests if enabled
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Export targets for build tree
export(EXPORT xyz_models_targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/XYZModelsTargets.cmake"
    NAMESPACE XYZ::
)

# Register package in user's package registry
export(PACKAGE XYZModels)

# Set version variables for package config
set(CONF_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include")
set(CONF_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CONF_CMAKE_DIR "${CMAKE_CURRENT_BINARY_DIR}")

# Generate the config file for the build tree
configure_file(cmake/XYZModelsConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/XYZModelsConfig.cmake" @ONLY)