# Root application CMake configuration
cmake_minimum_required(VERSION 3.12)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(examples)

# Create application library
add_library(xyz_app_lib STATIC
    src/app_manager.cpp
)

# Set library properties
set_target_properties(xyz_app_lib PROPERTIES
    OUTPUT_NAME "xyz_app"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Include directories for the library
target_include_directories(xyz_app_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies for the library
target_link_libraries(xyz_app_lib
    PUBLIC
        xyz_utils
        xyz_agents_lib
    PRIVATE
        pthread
)

# Installation rules for the library
install(TARGETS xyz_app_lib
    EXPORT xyz_app_targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Export targets
install(EXPORT xyz_app_targets
    FILE XYZAppTargets.cmake
    NAMESPACE XYZ::
    DESTINATION lib/cmake/xyz_app
)

# Generate and install package config
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/XYZAppConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)