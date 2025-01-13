# Root CMake configuration for agents module
cmake_minimum_required(VERSION 3.12)

# Create agents library
add_library(xyz_agents_lib STATIC
    src/base_agent.cpp
    src/ai_processor.cpp
    src/agent_manager.cpp
    src/utils.cpp
)

# Set library properties
set_target_properties(xyz_agents_lib PROPERTIES
    OUTPUT_NAME "xyz_agents"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Include directories for the library
target_include_directories(xyz_agents_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies for the library
target_link_libraries(xyz_agents_lib
    PUBLIC
        xyz_utils
    PRIVATE
        jsoncpp
        pthread
)

# Add the executable build
add_subdirectory(src)

# Installation rules for the library
install(TARGETS xyz_agents_lib
    EXPORT xyz_agents_targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/
    DESTINATION include/xyz/agents
    FILES_MATCHING PATTERN "*.h"
)

# Export targets
install(EXPORT xyz_agents_targets
    FILE XYZAgentsTargets.cmake
    NAMESPACE XYZ::
    DESTINATION lib/cmake/xyz_agents
)

# Generate and install package config
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/XYZAgentsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/XYZAgentsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/XYZAgentsConfig.cmake"
    INSTALL_DESTINATION lib/cmake/xyz_agents
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/XYZAgentsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/XYZAgentsConfigVersion.cmake"
    DESTINATION lib/cmake/xyz_agents
)

# Add tests if enabled
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Export package for use from build tree
export(EXPORT xyz_agents_targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/XYZAgentsTargets.cmake"
    NAMESPACE XYZ::
)