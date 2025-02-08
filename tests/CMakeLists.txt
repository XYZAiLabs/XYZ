# Tests CMake configuration
cmake_minimum_required(VERSION 3.12)

# Enable testing
enable_testing()

# Find GTest package
find_package(GTest REQUIRED)

# Test source files
set(TEST_SOURCES
    test_agents.cpp
    test_models.cpp
    test_utils.cpp
)

# Create test executable
add_executable(xyz_tests ${TEST_SOURCES})

# Include directories
target_include_directories(xyz_tests PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${GTEST_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(xyz_tests PRIVATE
    GTest::GTest
    GTest::Main
    xyz_agents_lib
    xyz_models_lib
    xyz_utils
    pthread
)

# Set compile options
target_compile_options(xyz_tests PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:DEBUG>:-g -O0>
    $<$<CONFIG:RELEASE>:-O3>
)

# Add tests to CTest
add_test(NAME xyz_tests COMMAND xyz_tests)

# Copy test files if needed
file(COPY test_config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})