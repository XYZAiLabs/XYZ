cmake_minimum_required(VERSION 3.12)
project(xyz_framework 
    VERSION 1.0.0
    DESCRIPTION "XYZ AI Agent Framework"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
option(BUILD_TESTS "Build test cases" ON)
option(BUILD_EXAMPLES "Build example applications" ON)
option(ENABLE_LOGGING "Enable logging" ON)
option(USE_STATIC_LIBS "Build static libraries" ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find required packages
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
find_package(jsoncpp REQUIRED)

# Set compiler flags
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        $<$<CONFIG:DEBUG>:-g -O0>
        $<$<CONFIG:RELEASE>:-O3>
    )
endif()

# Add subdirectories
add_subdirectory(agents)
add_subdirectory(app)
add_subdirectory(cli)
add_subdirectory(models)
add_subdirectory(utils)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Create configuration header
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/xyz/config.h
)

# Install headers
install(DIRECTORY include/
    DESTINATION include/xyz
    FILES_MATCHING PATTERN "*.hpp"
)

# Install configuration
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/include/xyz/config.h
    DESTINATION include/xyz
)

# Export package configuration
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/XYZConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/XYZConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/XYZConfig.cmake"
    INSTALL_DESTINATION lib/cmake/xyz
)

# Install package configuration
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/XYZConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/XYZConfigVersion.cmake"
    DESTINATION lib/cmake/xyz
)

# Export targets
install(EXPORT xyz-targets
    FILE XYZTargets.cmake
    NAMESPACE XYZ::
    DESTINATION lib/cmake/xyz
)

# Create and install pkg-config file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/xyz.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/xyz.pc
    @ONLY
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/xyz.pc
    DESTINATION lib/pkgconfig
)

# Print configuration summary
message(STATUS "")
message(STATUS "XYZ Framework Configuration:")
message(STATUS "  Version:          ${PROJECT_VERSION}")
message(STATUS "  Build type:       ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard:     ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build tests:      ${BUILD_TESTS}")
message(STATUS "  Build examples:   ${BUILD_EXAMPLES}")
message(STATUS "  Enable logging:   ${ENABLE_LOGGING}")
message(STATUS "  Static libraries: ${USE_STATIC_LIBS}")
message(STATUS "")