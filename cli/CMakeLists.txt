# Root CLI CMake configuration
cmake_minimum_required(VERSION 3.12)

# Add source directory
add_subdirectory(src)

# Create CLI library
add_library(xyz_cli_lib STATIC
    src/cli_manager.cpp
)

# Set library properties
set_target_properties(xyz_cli_lib PROPERTIES
    OUTPUT_NAME "xyz_cli"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Include directories
target_include_directories(xyz_cli_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
target_link_libraries(xyz_cli_lib
    PUBLIC
        xyz_utils
    PRIVATE
        xyz_agents_lib
)

# Installation rules
install(TARGETS xyz_cli_lib
    EXPORT xyz_cli_targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Export targets
install(EXPORT xyz_cli_targets
    FILE XYZCLITargets.cmake
    NAMESPACE XYZ::
    DESTINATION lib/cmake/xyz_cli
)